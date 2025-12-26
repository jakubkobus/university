import java.awt.Point;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/**
 * @file Rabbit.java
 * @brief Klasa reprezentująca królika w symulacji.
 *
 *        Klasa Rabbit dziedziczy po klasie Animal i implementuje logikę
 *        poruszania się królika po planszy.
 *        Królik stara się unikać wilka, wybierając ruchy oddalające go od
 *        drapieżnika, jeśli to możliwe.
 *        Obsługuje również stan zawieszenia oraz losowe opóźnienia ruchów.
 *
 * @author Jakub Kobus 283969
 */
public class Rabbit extends Animal {

  /**
   * Konstruktor klasy Rabbit.
   *
   * @param x      Początkowa współrzędna wiersza królika.
   * @param y      Początkowa współrzędna kolumny królika.
   * @param board  Referencja do planszy.
   * @param k      Parametr sterujący (np. czas odpoczynku).
   * @param random Generator liczb losowych.
   */
  public Rabbit(int x, int y, Board board, int k, Random random) {
    super(x, y, board, k, random);
  }

  /**
   * Główna pętla działania królika. Królik unika wilka, wybierając ruchy
   * oddalające go od drapieżnika,
   * jeśli to możliwe. Obsługuje również stan zawieszenia.
   */
  @Override
  public void run() {
    while (!isInterrupted()) {
      try {
        if (suspended) {
          Thread.sleep(getDelay());
          continue;
        }

        Wolf wolf = board.getWolf();
        if (wolf == null)
          continue;

        List<Point> possibleMoves = generatePossibleMoves();
        List<Point> validMoves = filterValidMoves(possibleMoves);
        List<Point> awayMoves = filterAwayMoves(validMoves, wolf.getX(), wolf.getY());

        List<Point> selectedMoves = awayMoves.isEmpty() ? validMoves : awayMoves;
        if (!selectedMoves.isEmpty()) {
          Point move = selectedMoves.get(random.nextInt(selectedMoves.size()));
          board.moveAnimal(this, move.x, move.y);
        }

        Thread.sleep(getDelay());
      } catch (InterruptedException e) {
        interrupt();
        break;
      }
    }
  }

  /**
   * Generuje listę możliwych ruchów królika (pola sąsiadujące).
   *
   * @return Lista możliwych pozycji do ruchu.
   */
  private List<Point> generatePossibleMoves() {
    List<Point> moves = new ArrayList<>();
    for (int dx = -1; dx <= 1; dx++) {
      for (int dy = -1; dy <= 1; dy++) {
        if (dx == 0 && dy == 0)
          continue;
        int newX = x + dx;
        int newY = y + dy;
        if (board.isValidPosition(newX, newY)) {
          moves.add(new Point(newX, newY));
        }
      }
    }
    return moves;
  }

  /**
   * Filtruje ruchy, pozostawiając tylko te prowadzące na wolne pola.
   *
   * @param moves Lista możliwych ruchów.
   * @return Lista ruchów prowadzących na wolne pola.
   */
  private List<Point> filterValidMoves(List<Point> moves) {
    List<Point> valid = new ArrayList<>();
    for (Point move : moves) {
      if (board.isCellEmpty(move.x, move.y)) {
        valid.add(move);
      }
    }
    return valid;
  }

  /**
   * Filtruje ruchy, pozostawiając tylko te, które oddalają królika od wilka.
   *
   * @param moves Lista możliwych ruchów.
   * @param wolfX Wiersz wilka.
   * @param wolfY Kolumna wilka.
   * @return Lista ruchów oddalających od wilka.
   */
  private List<Point> filterAwayMoves(List<Point> moves, int wolfX, int wolfY) {
    List<Point> away = new ArrayList<>();
    double currentDist = Math.sqrt(Math.pow(x - wolfX, 2) + Math.pow(y - wolfY, 2));
    for (Point move : moves) {
      double newDist = Math.sqrt(Math.pow(move.x - wolfX, 2) + Math.pow(move.y - wolfY, 2));
      if (newDist > currentDist) {
        away.add(move);
      }
    }
    return away;
  }
}