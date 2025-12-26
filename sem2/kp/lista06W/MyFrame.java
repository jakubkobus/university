import java.awt.Color;
import java.awt.Frame;
import java.awt.GridLayout;
import java.awt.Panel;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.Timer;

/**
 * @file MyFrame.java
 * @brief Klasa reprezentująca główne okno symulacji.
 *
 * Klasa MyFrame dziedziczy po Frame i odpowiada za graficzną prezentację planszy symulacji.
 * Tworzy siatkę paneli odpowiadających komórkom planszy, odświeża ich kolory w zależności od stanu zwierząt
 * oraz umożliwia interakcję użytkownika poprzez kliknięcia myszy (zawieszanie/wznawianie zwierząt).
 *
 * @author Jakub Kobus 283969
 */
public class MyFrame extends Frame {
  private final Board board;
  private final Panel[][] cells;

  /**
   * Konstruktor klasy MyFrame.
   * Tworzy okno symulacji, inicjalizuje siatkę paneli, ustawia timer odświeżający oraz obsługę zamykania okna.
   *
   * @param board Obiekt planszy symulacji.
   * @param n Liczba wierszy planszy.
   * @param m Liczba kolumn planszy.
   */
  public MyFrame(Board board, int n, int m) {
    this.board = board;
    setTitle("Symulacja");
    setLayout(new GridLayout(n, m));

    cells = new Panel[n][m];
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        Panel panel = new Panel();
        cells[i][j] = panel;
        add(panel);
        panel.addMouseListener(new CellMouseListener(i, j));
      }
    }

    setSize(800, 600);
    setVisible(true);

    Timer timer = new Timer(100, _ -> refresh());
    timer.start();

    addWindowListener(new WindowAdapter() {
      @Override
      public void windowClosing(WindowEvent e) {
        System.exit(0);
      }
    });
  }

  /**
   * Odświeża kolory wszystkich paneli w zależności od stanu zwierząt na planszy.
   * Wilk: czerwony (aktywny) lub różowy (zawieszony).
   * Królik: szary (aktywny) lub jasnoszary (zawieszony).
   * Puste pole: biały.
   */
  private void refresh() {
    synchronized (board) {
      for (int i = 0; i < cells.length; i++) {
        for (int j = 0; j < cells[i].length; j++) {
          Animal animal = board.getAnimalAt(i, j);
          Panel panel = cells[i][j];
          if (animal instanceof Wolf) {
            panel.setBackground(animal.isSuspended() ? Color.PINK : Color.RED);
          } else if (animal instanceof Rabbit) {
            panel.setBackground(animal.isSuspended() ? Color.LIGHT_GRAY : Color.GRAY);
          } else {
            panel.setBackground(Color.WHITE);
          }
        }
      }
    }
  }

  /**
   * Prywatna klasa obsługująca kliknięcia myszy na panelach.
   * Kliknięcie powoduje zawieszenie lub wznowienie zwierzęcia w danej komórce.
   */
  private class CellMouseListener extends MouseAdapter {
    private final int x;
    private final int y;

    /**
     * Konstruktor nasłuchiwacza kliknięć dla konkretnej komórki.
     *
     * @param x Wiersz komórki.
     * @param y Kolumna komórki.
     */
    public CellMouseListener(int x, int y) {
      this.x = x;
      this.y = y;
    }

    /**
     * Obsługuje kliknięcie myszy na panelu – zawiesza lub wznawia zwierzę.
     *
     * @param e Zdarzenie kliknięcia myszy.
     */
    @Override
    public void mouseClicked(MouseEvent e) {
      synchronized (board) {
        Animal animal = board.getAnimalAt(x, y);
        if (animal != null) {
          animal.setSuspended(!animal.isSuspended());
        }
      }
    }
  }
}