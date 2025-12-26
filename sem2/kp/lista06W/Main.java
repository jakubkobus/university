import java.util.*;

/**
 * @file Main.java
 * @brief Klasa uruchamiająca symulację wilka i królików.
 *
 *        Klasa Main odpowiada za inicjalizację planszy, rozmieszczenie zwierząt
 *        (wilka i królików)
 *        oraz uruchomienie graficznego interfejsu użytkownika.
 *
 *        Funkcjonalności:
 *        - Odczyt parametrów symulacji z argumentów wiersza poleceń.
 *        - Losowe rozmieszczenie wilka i królików na planszy.
 *        - Uruchomienie wątków zwierząt.
 *        - Inicjalizacja okna symulacji.
 *
 * @author Jakub Kobus 283969
 */
public class Main {

  /**
   * Metoda główna programu. Inicjalizuje planszę, rozmieszcza zwierzęta i
   * uruchamia GUI.
   *
   * @param args Argumenty wiersza poleceń: n m rabbits k
   *             n - liczba wierszy planszy,
   *             m - liczba kolumn planszy,
   *             rabbits - liczba królików,
   *             k - parametr przekazywany do zwierząt (np. czas życia).
   */
  public static void main(String[] args) {
    if (args.length < 4) {
      System.out.println("Uzycie: java Main n m rabbits k");
      return;
    }
    int n = Integer.parseInt(args[0]);
    int m = Integer.parseInt(args[1]);
    int numRabbits = Integer.parseInt(args[2]);
    int k = Integer.parseInt(args[3]);

    Board board = new Board(n, m);
    Random random = new Random();

    // Umieszcza wilka na losowym, wolnym polu planszy.
    int wolfX, wolfY;
    do {
      wolfX = random.nextInt(n);
      wolfY = random.nextInt(m);
    } while (board.getAnimalAt(wolfX, wolfY) != null);
    Wolf wolf = new Wolf(wolfX, wolfY, board, k, random);
    board.addWolf(wolf);

    // Umieszcza króliki na losowych, wolnych polach planszy.
    for (int i = 0; i < numRabbits; i++) {
      int x, y;
      do {
        x = random.nextInt(n);
        y = random.nextInt(m);
      } while (board.getAnimalAt(x, y) != null);
      Rabbit rabbit = new Rabbit(x, y, board, k, random);
      board.addRabbit(rabbit);
      rabbit.start();
    }

    wolf.start();

    new MyFrame(board, n, m);
  }
}