import java.awt.*;
import java.awt.event.*;

/**
 * Klasa Main reprezentuje główne okno aplikacji "Edytor kształtów".
 * Dziedziczy po klasie Frame i implementuje interfejsy ActionListener oraz WindowListener.
 * 
 * Funkcjonalności:
 * - Obsługa menu z opcjami zapisu, wczytywania, wyboru figur oraz pomocy.
 * - Obsługa rysowania figur: okręgów, prostokątów i wielokątów.
 * - Wyświetlanie informacji o aplikacji oraz instrukcji obsługi.
 * 
 * Elementy interfejsu:
 * - Menu główne z trzema kategoriami: "Plik", "Figury", "Pomoc".
 * - Przycisk "Informacje" w dolnej części okna.
 * - Obszar rysowania (klasa Surface) w centralnej części okna.
 * 
 * Obsługiwane zdarzenia:
 * - Kliknięcia w elementy menu i przycisk "Informacje".
 * - Zamykanie okna aplikacji.
 * 
 * Metody:
 * - actionPerformed(ActionEvent e): Obsługuje akcje użytkownika, takie jak wybór opcji z menu lub kliknięcie przycisku.
 * - showInfo(): Wyświetla okno dialogowe z informacjami o aplikacji.
 * - showTutorial(): Wyświetla okno dialogowe z instrukcją obsługi aplikacji.
 * - windowClosing(WindowEvent e): Obsługuje zamykanie okna aplikacji.
 * - Pozostałe metody z interfejsu WindowListener są zaimplementowane, ale nie zawierają logiki.
 * 
 * @author Jakub Kobus 283969
 * @version 1.0
 */
public class Main extends Frame implements ActionListener, WindowListener {
  private Surface surface;
  private MenuBar menuBar;
  private Menu fileMenu, shapesMenu, helpMenu;
  private MenuItem saveItem, loadItem, circleItem, rectangleItem, polygonItem, infoItem, instructItem;
  private Button infoButton;

  /**
   * Konstruktor klasy Main. Inicjalizuje główne okno aplikacji, menu, przyciski oraz obszar rysowania.
   */
  public Main() {
    super("Edytor kształtów");
    setSize(1600, 800);
    addWindowListener(this);

    menuBar = new MenuBar();

    fileMenu = new Menu("Plik");
    saveItem = new MenuItem("Zapisz");
    loadItem = new MenuItem("Wczytaj");
    fileMenu.add(saveItem);
    fileMenu.add(loadItem);
    menuBar.add(fileMenu);

    shapesMenu = new Menu("Figury");
    circleItem = new MenuItem("Okrąg");
    rectangleItem = new MenuItem("Prostokąt");
    polygonItem = new MenuItem("Wielokąt");
    shapesMenu.add(circleItem);
    shapesMenu.add(rectangleItem);
    shapesMenu.add(polygonItem);
    menuBar.add(shapesMenu);

    helpMenu = new Menu("Pomoc");
    instructItem = new MenuItem("Instrukcja");
    infoItem = new MenuItem("Informacje");
    helpMenu.add(instructItem);
    helpMenu.add(infoItem);
    menuBar.add(helpMenu);

    setMenuBar(menuBar);

    saveItem.addActionListener(this);
    loadItem.addActionListener(this);
    circleItem.addActionListener(this);
    rectangleItem.addActionListener(this);
    polygonItem.addActionListener(this);
    instructItem.addActionListener(this);
    infoItem.addActionListener(this);

    infoButton = new Button("Informacje");
    infoButton.addActionListener(this);
    add(infoButton, BorderLayout.SOUTH);

    surface = new Surface();
    add(surface, BorderLayout.CENTER);

    setVisible(true);
  }

  /**
   * Obsługuje akcje użytkownika, takie jak wybór opcji z menu lub kliknięcie przycisku.
   *
   * @param e Zdarzenie akcji.
   */
  @Override
  public void actionPerformed(ActionEvent e) {
    Object source = e.getSource();
    if(source == saveItem) {
      surface.save();
    } else if(source == loadItem) {
      surface.load();
    } else if(source == circleItem) {
      surface.setDrawingMode(Mode.CIRCLE);
    } else if(source == rectangleItem) {
      surface.setDrawingMode(Mode.RECTANGLE);
    } else if(source == polygonItem) {
      surface.setDrawingMode(Mode.POLYGON);
    } else if(source == infoItem || source == infoButton) {
      showInfo();
    } else if(source == instructItem) {
      showTutorial();
    }
  }

  /**
   * Wyświetla okno dialogowe z informacjami o aplikacji.
   */
  private void showInfo() {
    Dialog infoDialog = new Dialog(this, "Informacje", true);
    infoDialog.setLayout(new FlowLayout());
    infoDialog.add(new Label("Edytor kształtów"));
    infoDialog.add(new Label("Jakub Kobus 283969"));
    infoDialog.add(new Label("Informacje o użyciu w instrukcji"));
    Button okButton = new Button("OK");
    okButton.addActionListener(ev -> infoDialog.dispose());
    infoDialog.add(okButton);
    infoDialog.setSize(300, 210);
    infoDialog.setResizable(false);
    infoDialog.setVisible(true);
  }

  /**
   * Wyświetla okno dialogowe z instrukcją obsługi aplikacji.
   */
  private void showTutorial() {
    Dialog tutorialDialog = new Dialog(this, "Instrukcja", true);
    tutorialDialog.setLayout(new FlowLayout());
    tutorialDialog.add(new Label("1. Wybierz figurę z menu."));
    tutorialDialog.add(new Label("2. Kliknij i przeciągnij, aby narysować."));
    tutorialDialog.add(new Label("3. Kliknij prawym przyciskiem, aby zmienić kolor."));
    tutorialDialog.add(new Label("4. Użyj Ctrl + strzałek (prawo / lewo) do obracania."));
    tutorialDialog.add(new Label("5. Scroll do skalowania."));
    tutorialDialog.add(new Label("Aby zatwierdzić wielokąt wystarczy wcisnąć prawy przycisk myszy."));
    Button okButton = new Button("OK");
    okButton.addActionListener(ev -> tutorialDialog.dispose());
    tutorialDialog.add(okButton);
    tutorialDialog.setSize(500, 260);
    tutorialDialog.setResizable(false);
    tutorialDialog.setVisible(true);
  }

  /**
   * Obsługuje zamykanie okna aplikacji.
   *
   * @param e Zdarzenie zamknięcia okna.
   */
  @Override
  public void windowClosing(WindowEvent e) { dispose(); }

  /**
   * Metoda wywoływana po otwarciu okna. (Brak implementacji)
   *
   * @param e Zdarzenie otwarcia okna.
   */
  @Override
  public void windowOpened(WindowEvent e) {}

  /**
   * Metoda wywoływana po zamknięciu okna. (Brak implementacji)
   *
   * @param e Zdarzenie zamknięcia okna.
   */
  @Override
  public void windowClosed(WindowEvent e) {}

  /**
   * Metoda wywoływana po zminimalizowaniu okna. (Brak implementacji)
   *
   * @param e Zdarzenie zminimalizowania okna.
   */
  @Override
  public void windowIconified(WindowEvent e) {}

  /**
   * Metoda wywoływana po przywróceniu okna z minimalizacji. (Brak implementacji)
   *
   * @param e Zdarzenie przywrócenia okna.
   */
  @Override
  public void windowDeiconified(WindowEvent e) {}

  /**
   * Metoda wywoływana po aktywacji okna. (Brak implementacji)
   *
   * @param e Zdarzenie aktywacji okna.
   */
  @Override
  public void windowActivated(WindowEvent e) {}

  /**
   * Metoda wywoływana po dezaktywacji okna. (Brak implementacji)
   *
   * @param e Zdarzenie dezaktywacji okna.
   */
  @Override
  public void windowDeactivated(WindowEvent e) {}

  /**
   * Metoda główna uruchamiająca aplikację.
   *
   * @param args Argumenty wiersza poleceń (nieużywane).
   */
  public static void main(String[] args) {
    new Main();
  }
}