import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.locks.ReentrantLock;

public class Main {
  static final int PHILOSOPHER_COUNT = 5;
  static final int MEAL_COUNT = 3;

  static synchronized void Log(String msg) {
    System.out.println(msg);
  }

  static ReentrantLock[] Forks = new ReentrantLock[PHILOSOPHER_COUNT];

  static class Philosopher extends Thread {
    int id;

    Philosopher(int id) {
      this.id = id;
    }

    void RandomWait() {
      try {
        int time = ThreadLocalRandom.current().nextInt(500);
        Thread.sleep(time);
      } catch (InterruptedException e) {}
    }

    @Override
    public void run() {
      int MealsEaten = 0;
      int Fails = 0;
      int LeftFork = id;
      int RightFork = (id + 1) % PHILOSOPHER_COUNT;

      int displayId = id + 1;

      while(MealsEaten < MEAL_COUNT) {
        Log("Philosopher " + displayId + " thinks...");
        RandomWait();

        if(Forks[LeftFork].tryLock()) {
          if(Forks[RightFork].tryLock()) {
            MealsEaten++;
            Log(
              "--- Philosopher " + displayId + " eats (meal " + MealsEaten + ")"
            );
            RandomWait();

            Forks[RightFork].unlock();
            Forks[LeftFork].unlock();
            Log("Philosopher " + displayId + " dropped both forks");
          } else {
            Forks[LeftFork].unlock();
            Fails++;
            Log(
              "[!] Philosopher " +
                displayId +
                " couldn't get right fork, drops left one"
            );
            RandomWait();
          }
        } else {
          Fails++;
          Log("[!] Philosopher " + displayId + " couldn't get left fork");
          RandomWait();
        }
      }

      Log(
        "\n[SUCCESS] Philosopher " +
          displayId +
          " finished eating, failures: " +
          Fails +
          "\n"
      );
    }
  }

  public static void main(String[] args) throws InterruptedException {
    for(int i = 0; i < PHILOSOPHER_COUNT; i++) {
      Forks[i] = new ReentrantLock();
    }

    Philosopher[] philosophers = new Philosopher[PHILOSOPHER_COUNT];
    for(int i = 0; i < PHILOSOPHER_COUNT; i++) {
      philosophers[i] = new Philosopher(i);
      philosophers[i].start();
    }

    for(int i = 0; i < PHILOSOPHER_COUNT; i++) {
      philosophers[i].join();
    }
  }
}
