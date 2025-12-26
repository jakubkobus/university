import java.util.ArrayList;
import java.util.List;

/**
 * @file Board.java
 * @brief Klasa reprezentująca planszę symulacji z zwierzętami.
 *
 *        Klasa Board odpowiada za przechowywanie i zarządzanie stanem planszy,
 *        na której poruszają się zwierzęta (wilk i króliki).
 *        Umożliwia dodawanie zwierząt, sprawdzanie stanu komórek, przesuwanie
 *        zwierząt oraz obsługę kolizji.
 *
 *        Funkcjonalności:
 *        - Przechowywanie referencji do zwierząt na planszy.
 *        - Dodawanie wilka i królików.
 *        - Sprawdzanie zawartości i poprawności pozycji na planszy.
 *        - Przesuwanie zwierząt i obsługa zjadania królików przez wilka.
 *
 * @author Jakub Kobus 283969
 */
public class Board {
  private final int n, m;
  private final Animal[][] grid;
  private Wolf wolf;
  private final List<Rabbit> rabbits = new ArrayList<>();

  /**
   * Tworzy nową planszę o zadanych wymiarach.
   *
   * @param n liczba wierszy planszy
   * @param m liczba kolumn planszy
   */
  public Board(int n, int m) {
    this.n = n;
    this.m = m;
    this.grid = new Animal[n][m];
  }

  /**
   * Dodaje wilka do planszy na jego pozycji początkowej.
   *
   * @param wolf Obiekt wilka do dodania.
   */
  public synchronized void addWolf(Wolf wolf) {
    this.wolf = wolf;
    grid[wolf.getX()][wolf.getY()] = wolf;
  }

  /**
   * Dodaje królika do planszy na jego pozycji początkowej.
   *
   * @param rabbit Obiekt królika do dodania.
   */
  public synchronized void addRabbit(Rabbit rabbit) {
    rabbits.add(rabbit);
    grid[rabbit.getX()][rabbit.getY()] = rabbit;
  }

  /**
   * Zwraca zwierzę znajdujące się na podanej pozycji planszy.
   *
   * @param x Wiersz.
   * @param y Kolumna.
   * @return Zwierzę na danej pozycji lub null, jeśli pole jest puste lub poza
   *         planszą.
   */
  public synchronized Animal getAnimalAt(int x, int y) {
    if (x < 0 || x >= n || y < 0 || y >= m)
      return null;
    return grid[x][y];
  }

  /**
   * Zwraca referencję do wilka na planszy.
   *
   * @return Obiekt wilka.
   */
  public synchronized Wolf getWolf() {
    return wolf;
  }

  /**
   * Zwraca listę wszystkich królików na planszy.
   *
   * @return Nowa lista królików.
   */
  public synchronized List<Rabbit> getRabbits() {
    return new ArrayList<>(rabbits);
  }

  /**
   * Przesuwa zwierzę na nowe pole, obsługuje kolizje i zjadanie królików przez
   * wilka.
   *
   * @param animal Zwierzę do przesunięcia.
   * @param newX   Nowy wiersz.
   * @param newY   Nowa kolumna.
   * @return Status ruchu (np. czy ruch był poprawny, czy wilk złapał królika).
   */
  public MoveStatus moveAnimal(Animal animal, int newX, int newY) {
    int oldX = animal.getX();
    int oldY = animal.getY();

    if (newX < 0 || newX >= n || newY < 0 || newY >= m)
      return MoveStatus.INVALID;

    Animal target = grid[newX][newY];

    if (animal instanceof Wolf) {
      if (target instanceof Rabbit) {
        Rabbit rabbit = (Rabbit) target;
        rabbits.remove(rabbit);
        rabbit.interrupt();
        grid[newX][newY] = null;
      }
    }

    if (target != null && !(animal instanceof Wolf && target instanceof Rabbit))
      return MoveStatus.INVALID;

    grid[oldX][oldY] = null;
    animal.setPosition(newX, newY);
    grid[newX][newY] = animal;

    if (animal instanceof Wolf && target instanceof Rabbit)
      return MoveStatus.CAUGHT_RABBIT;

    return MoveStatus.MOVED;
  }

  /**
   * Sprawdza, czy podana pozycja znajduje się w granicach planszy.
   *
   * @param x Wiersz.
   * @param y Kolumna.
   * @return true jeśli pozycja jest poprawna, false w przeciwnym razie.
   */
  public synchronized boolean isValidPosition(int x, int y) {
    if(x >= 0 && x < n && y >= 0 && y < m)
      if(grid[x][y] instanceof Rabbit)
        if(grid[x][y].isSuspended())
          return false;

    return x >= 0 && x < n && y >= 0 && y < m;
  }

  /**
   * Sprawdza, czy pole o podanych współrzędnych jest puste.
   *
   * @param x Wiersz.
   * @param y Kolumna.
   * @return true jeśli pole jest puste, false w przeciwnym razie.
   */
  public synchronized boolean isCellEmpty(int x, int y) {
    return grid[x][y] == null;
  }
}