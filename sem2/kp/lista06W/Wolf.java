import java.awt.Point;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/**
 * @file Wolf.java
 * @brief Klasa reprezentująca wilka w symulacji.
 *
 *        Klasa Wolf dziedziczy po klasie Animal i implementuje logikę
 *        poruszania się wilka po planszy,
 *        wyszukiwania najbliższego królika oraz zjadania królików. Wilk porusza
 *        się w kierunku najbliższego
 *        nie-zawieszonego królika, a po zjedzeniu królika odpoczywa przez kilka
 *        cykli.
 *
 * @author Jakub Kobus 283969
 */
public class Wolf extends Animal {

  /**
   * Konstruktor klasy Wolf.
   *
   * @param x      Początkowa współrzędna wiersza wilka.
   * @param y      Początkowa współrzędna kolumny wilka.
   * @param board  Referencja do planszy.
   * @param k      Parametr sterujący (np. czas odpoczynku).
   * @param random Generator liczb losowych.
   */
  public Wolf(int x, int y, Board board, int k, Random random) {
    super(x, y, board, k, random);
  }

  /**
   * Główna pętla działania wilka. Wilk szuka najbliższego królika i porusza się w
   * jego kierunku.
   * Po zjedzeniu królika odpoczywa przez kilka cykli. Obsługuje również stan
   * zawieszenia.
   */
  @Override
  public void run() {
    while (!isInterrupted()) {
      try {
        if (restCycles > 0) {
          restCycles--;
          Thread.sleep(getDelay());
          continue;
        }

        if (suspended) {
          Thread.sleep(getDelay());
          continue;
        }

        List<Rabbit> rabbits = board.getRabbits();
        if (rabbits.isEmpty()) {
          interrupt();
          break;
        }

        Rabbit closest = findClosestRabbit(rabbits);
        if (closest == null)
          continue;

        List<Point> possibleMoves = generatePossibleMoves();
        Point bestMove = selectBestMove(closest, possibleMoves);

        if (bestMove != null) {
          MoveStatus status = board.moveAnimal(this, bestMove.x, bestMove.y);
          if (status == MoveStatus.CAUGHT_RABBIT) {
            restCycles = 5;
          }
        }

        Thread.sleep(getDelay());
      } catch (InterruptedException e) {
        interrupt();
        break;
      }
    }
  }

  /**
   * Wyszukuje najbliższego nie-zawieszonego królika na planszy.
   *
   * @param rabbits Lista królików na planszy.
   * @return Najbliższy królik lub null, jeśli brak dostępnych królików.
   */
  private Rabbit findClosestRabbit(List<Rabbit> rabbits) {
    Rabbit closest = null;
    double minDist = Double.MAX_VALUE;
    for (Rabbit r : rabbits) {
      if (r.isSuspended())
        continue;
      double dist = distance(r.getX(), r.getY());
      if (dist < minDist) {
        minDist = dist;
        closest = r;
      }
    }
    return closest;
  }

  /**
   * Oblicza odległość euklidesową od obecnej pozycji wilka do wskazanej pozycji.
   *
   * @param x2 Wiersz celu.
   * @param y2 Kolumna celu.
   * @return Odległość euklidesowa.
   */
  private double distance(int x2, int y2) {
    return Math.sqrt(Math.pow(x - x2, 2) + Math.pow(y - y2, 2));
  }

  /**
   * Generuje listę możliwych ruchów wilka (pola sąsiadujące).
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
   * Wybiera najlepszy ruch wilka, aby zbliżyć się do wskazanego królika.
   * Jeśli możliwe jest wejście na pole z królikiem, wybiera ten ruch.
   *
   * @param target        Cel (królik), do którego wilk się zbliża.
   * @param possibleMoves Lista możliwych ruchów.
   * @return Najlepszy ruch (punkt docelowy) lub null, jeśli brak możliwych
   *         ruchów.
   */
  private Point selectBestMove(Rabbit target, List<Point> possibleMoves) {
    double minDist = Double.MAX_VALUE;
    List<Point> bestMoves = new ArrayList<>();

    for (Point move : possibleMoves) {
      Animal animal = board.getAnimalAt(move.x, move.y);
      if (animal instanceof Rabbit) {
        bestMoves.clear();
        bestMoves.add(move);
        minDist = 0;
        break;
      } else if (animal == null) {
        double dist = Math.sqrt(Math.pow(move.x - target.getX(), 2) + Math.pow(move.y - target.getY(), 2));
        if (dist < minDist) {
          minDist = dist;
          bestMoves.clear();
          bestMoves.add(move);
        } else if (dist == minDist) {
          bestMoves.add(move);
        }
      }
    }

    if (bestMoves.isEmpty())
      return null;
    return bestMoves.get(random.nextInt(bestMoves.size()));
  }
}