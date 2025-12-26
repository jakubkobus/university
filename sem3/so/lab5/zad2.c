#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <time.h>

#define SHM_NAME "/shm_demo_zad2"
#define SEM_EMPTY "/sem_empty_zad2"
#define SEM_FULL "/sem_full_zad2"
#define BUF_SIZE 10
#define ITEMS_TO_PROCESS 20

// Struktura w pamięci współdzielonej
typedef struct
{
  int buffer[BUF_SIZE];
  int head;
  int tail;
} SharedMemory;

// Funkcja Producenta
void run_producer()
{
  // Otwieranie zasobów (zauważ, że są już utworzone w main, tu je tylko otwieramy lub używamy dziedziczone)
  // Dla pewności otwieramy deskryptory "czysto" jak w osobnym procesie
  int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
  SharedMemory *shm = mmap(0, sizeof(SharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

  sem_t *sem_empty = sem_open(SEM_EMPTY, 0);
  sem_t *sem_full = sem_open(SEM_FULL, 0);

  printf("[Producent] Start. PID: %d\n", getpid());

  for (int i = 0; i < ITEMS_TO_PROCESS; i++)
  {
    sem_wait(sem_empty); // Czekaj na miejsce

    shm->buffer[shm->head] = i;
    printf("[Producent] Wyprodukował: %d (poz: %d)\n", i, shm->head);
    shm->head = (shm->head + 1) % BUF_SIZE;

    sem_post(sem_full); // Zgłoś, że jest nowy element
    usleep(100000);     // Małe opóźnienie dla czytelności (0.1s)
  }

  printf("[Producent] Koniec pracy.\n");
  munmap(shm, sizeof(SharedMemory));
  close(shm_fd);
  sem_close(sem_empty);
  sem_close(sem_full);
}

// Funkcja Konsumenta
void run_consumer()
{
  int shm_fd = shm_open(SHM_NAME, O_RDWR, 0666);
  SharedMemory *shm = mmap(0, sizeof(SharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

  sem_t *sem_empty = sem_open(SEM_EMPTY, 0);
  sem_t *sem_full = sem_open(SEM_FULL, 0);

  printf("[Konsument] Start. PID: %d\n", getpid());

  for (int i = 0; i < ITEMS_TO_PROCESS; i++)
  {
    sem_wait(sem_full); // Czekaj na element

    int item = shm->buffer[shm->tail];
    printf("\t\t[Konsument] Pobrał: %d (poz: %d)\n", item, shm->tail);
    shm->tail = (shm->tail + 1) % BUF_SIZE;

    sem_post(sem_empty); // Zwolnij miejsce
    usleep(150000);      // Konsument nieco wolniejszy
  }

  printf("[Konsument] Koniec pracy.\n");
  munmap(shm, sizeof(SharedMemory));
  close(shm_fd);
  sem_close(sem_empty);
  sem_close(sem_full);
}

int main()
{
  // 1. INICJALIZACJA ZASOBÓW (Robi to proces główny przed forkiem)
  // Usuń stare śmieci jeśli program był przerwany
  shm_unlink(SHM_NAME);
  sem_unlink(SEM_EMPTY);
  sem_unlink(SEM_FULL);

  // Utwórz pamięć współdzieloną
  int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
  ftruncate(shm_fd, sizeof(SharedMemory));

  // Wstępne zmapowanie, by ustawić head/tail na 0
  SharedMemory *shm = mmap(0, sizeof(SharedMemory), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  shm->head = 0;
  shm->tail = 0;
  munmap(shm, sizeof(SharedMemory)); // O mapujemy ponownie w procesach

  // Utwórz semafory
  sem_open(SEM_EMPTY, O_CREAT, 0666, BUF_SIZE);
  sem_open(SEM_FULL, O_CREAT, 0666, 0);

  // 2. ROZDZIELENIE PROCESÓW
  pid_t pid = fork();

  if (pid < 0)
  {
    perror("Fork failed");
    return 1;
  }

  if (pid == 0)
  {
    // --- PROCES POTOMNY (DZIECKO) ---
    // Niech dziecko będzie konsumentem
    run_consumer();
    exit(0); // Dziecko kończy działanie tutaj
  }
  else
  {
    // --- PROCES MACIERZYSTY (RODZIC) ---
    // Rodzic będzie producentem
    run_producer();

    // Czekaj na zakończenie dziecka
    wait(NULL);

    // 3. SPRZĄTANIE (Tylko rodzic na samym końcu)
    printf("Czyszczenie zasobów systemowych...\n");
    shm_unlink(SHM_NAME);
    sem_unlink(SEM_EMPTY);
    sem_unlink(SEM_FULL);
  }

  return 0;
}