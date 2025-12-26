import java.awt.*;

/**
 * Klasa Circle reprezentuje okrąg jako figurę geometryczną.
 * Dziedziczy po klasie Shape i implementuje jej abstrakcyjne metody.
 * 
 * <p>Okrąg jest definiowany przez współrzędne środka (x, y) oraz promień.</p>
 * 
 * <p>Metody tej klasy pozwalają na rysowanie okręgu, sprawdzanie, czy punkt
 * znajduje się wewnątrz okręgu, przesuwanie, skalowanie oraz obracanie figury.</p>
 * 
 * <p>Klasa obsługuje również wyróżnianie aktywnej figury poprzez rysowanie
 * obramowania.</p>
 * 
 * @author Jakub Kobus 283969
 * @version 1.0
 */
public class Circle extends Shape {
  private int radius;

  /**
   * Tworzy nowy okrąg o zadanych parametrach.
   *
   * @param x Współrzędna X środka okręgu.
   * @param y Współrzędna Y środka okręgu.
   * @param radius Promień okręgu.
   */
  public Circle(int x, int y, int radius) {
    this.x = x;
    this.y = y;
    this.radius = radius;
  }

  /**
   * Zwraca środek okręgu jako punkt.
   *
   * @return Punkt będący środkiem okręgu.
   */
  @Override
  public Point getCenter() {
      return new Point(x, y);
  }

  /**
   * Rysuje okrąg na podanym kontekście graficznym.
   *
   * @param g Kontekst graficzny do rysowania (Graphics2D).
   * @param isActive Określa, czy okrąg jest aktywny (wyróżniony).
   */
  @Override
  public void draw(Graphics2D g, boolean isActive) {
    Graphics2D g2d = (Graphics2D) g.create();
    g2d.rotate(Math.toRadians(rotation), x, y);
    
    g2d.setColor(color);
    g2d.fillOval(x - radius, y - radius, 2 * radius, 2 * radius);
    
    if(isActive) {
      g2d.setStroke(ACTIVE_STROKE);
      g2d.setColor(Color.BLACK);
      g2d.drawOval(x - radius, y - radius, 2 * radius, 2 * radius);
    }

    g2d.dispose();
  }

  /**
   * Sprawdza, czy punkt o podanych współrzędnych znajduje się wewnątrz okręgu.
   *
   * @param x Współrzędna X punktu.
   * @param y Współrzędna Y punktu.
   * @return true jeśli punkt znajduje się w okręgu, w przeciwnym razie false.
   */
  @Override
  public boolean wasClicked(int x, int y) {
    return Math.hypot(x - this.x, y - this.y) <= radius;
  }

  /**
   * Przesuwa okrąg o zadany wektor (dx, dy).
   *
   * @param dx Przesunięcie w osi X.
   * @param dy Przesunięcie w osi Y.
   */
  @Override
  public void move(int dx, int dy) {
    x += dx;
    y += dy;
  }

  /**
   * Skaluje okrąg o podany współczynnik.
   *
   * @param factor Współczynnik skalowania (np. 1.1 powiększa, 0.9 pomniejsza).
   */
  @Override
  public void scale(double factor) {
    radius = (int)(radius * factor);
  }

  /**
   * Obraca okrąg o podany kąt w stopniach.
   *
   * @param degrees Kąt obrotu w stopniach.
   */
  @Override
  public void rotate(double degrees) {
    rotation += degrees;
  }

  /**
   * Ustawia promień okręgu.
   *
   * @param radius Nowy promień okręgu.
   */
  public void setRadius(int radius) {
    this.radius = radius;
  }
}