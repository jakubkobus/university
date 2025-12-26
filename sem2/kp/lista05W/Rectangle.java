import java.awt.*;

/**
 * Klasa Rectangle reprezentuje prostokąt jako figurę geometryczną.
 * Dziedziczy po klasie Shape i implementuje jej abstrakcyjne metody.
 * 
 * <p>Prostokąt jest definiowany przez współrzędne lewego górnego rogu (x, y),
 * szerokość (width) oraz wysokość (height).</p>
 * 
 * <p>Metody tej klasy pozwalają na rysowanie prostokąta, sprawdzanie, czy punkt
 * znajduje się wewnątrz prostokąta, przesuwanie, skalowanie oraz obracanie figury.</p>
 * 
 * <p>Klasa obsługuje również wyróżnianie aktywnej figury poprzez rysowanie
 * obramowania.</p>
 * 
 * @author Jakub Kobus 283969
 * @version 1.0
 */
public class Rectangle extends Shape {
  protected int width, height;

  /**
   * Tworzy nowy prostokąt o zadanych parametrach.
   *
   * @param x Współrzędna X lewego górnego rogu.
   * @param y Współrzędna Y lewego górnego rogu.
   * @param width Szerokość prostokąta.
   * @param height Wysokość prostokąta.
   */
  public Rectangle(int x, int y, int width, int height) {
    this.x = x;
    this.y = y;
    this.width = width;
    this.height = height;
  }

  /**
   * Zwraca środek prostokąta jako punkt.
   *
   * @return Punkt będący środkiem prostokąta.
   */
  @Override
  public Point getCenter() {
    return new Point(x + width / 2, y + height / 2);
  }

  /**
   * Rysuje prostokąt na podanym kontekście graficznym.
   *
   * @param g Kontekst graficzny do rysowania (Graphics2D).
   * @param isActive Określa, czy prostokąt jest aktywny (wyróżniony).
   */
  @Override
  public void draw(Graphics2D g, boolean isActive) {
    Graphics2D g2d = (Graphics2D) g.create();
    g2d.rotate(Math.toRadians(rotation), x + width / 2, y + height / 2);
    
    g2d.setColor(color);
    g2d.fillRect(x, y, width, height);
    
    if(isActive) {
        g2d.setStroke(ACTIVE_STROKE);
        g2d.setColor(Color.BLACK);
        g2d.drawRect(x, y, width, height);
    }

    g2d.dispose();
  }

  /**
   * Sprawdza, czy punkt o podanych współrzędnych znajduje się wewnątrz prostokąta.
   *
   * @param x Współrzędna X punktu.
   * @param y Współrzędna Y punktu.
   * @return true jeśli punkt znajduje się w prostokącie, w przeciwnym razie false.
   */
  @Override
  public boolean wasClicked(int x, int y) {
    return x >= this.x && x <= this.x + width && y >= this.y && y <= this.y + height;
  }

  /**
   * Przesuwa prostokąt o zadany wektor (dx, dy).
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
   * Skaluje prostokąt o podany współczynnik.
   *
   * @param factor Współczynnik skalowania (np. 1.1 powiększa, 0.9 pomniejsza).
   */
  @Override
  public void scale(double factor) {
    width = (int)(width * factor);
    height = (int)(height * factor);
  }

  /**
   * Obraca prostokąt o podany kąt w stopniach.
   *
   * @param degrees Kąt obrotu w stopniach.
   */
  @Override
  public void rotate(double degrees) {
    rotation += degrees;
  }

  /**
   * Ustawia szerokość prostokąta.
   *
   * @param width Nowa szerokość prostokąta.
   */
  public void setWidth(int width) {
    this.width = width;
  }

  /**
   * Ustawia wysokość prostokąta.
   *
   * @param height Nowa wysokość prostokąta.
   */
  public void setHeight(int height) {
    this.height = height;
  }
}