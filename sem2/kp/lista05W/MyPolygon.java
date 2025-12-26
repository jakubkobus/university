import java.awt.*;
import java.util.ArrayList;
import java.util.List;

/**
 * Klasa MyPolygon reprezentuje wielokąt jako figurę geometryczną.
 * Dziedziczy po klasie Shape i implementuje jej abstrakcyjne metody.
 * 
 * <p>Wielokąt jest definiowany przez listę punktów (wierzchołków).</p>
 * 
 * <p>Metody tej klasy pozwalają na dodawanie punktów do wielokąta, rysowanie
 * wielokąta, sprawdzanie, czy punkt znajduje się wewnątrz wielokąta, przesuwanie,
 * skalowanie oraz obracanie figury.</p>
 * 
 * <p>Klasa obsługuje również wyróżnianie aktywnej figury poprzez rysowanie
 * obramowania.</p>
 * 
 * @author Jakub Kobus 283969
 * @version 1.0
 */
public class MyPolygon extends Shape {
  private List<Point> points = new ArrayList<>();

  /**
   * Dodaje nowy punkt (wierzchołek) do wielokąta.
   *
   * @param x Współrzędna X punktu.
   * @param y Współrzędna Y punktu.
   */
  public void addPoint(int x, int y) {
    points.add(new Point(x, y));
  }

  /**
   * Zwraca środek wielokąta jako punkt.
   *
   * @return Punkt będący środkiem wielokąta.
   */
  @Override
  public Point getCenter() {
    int sumX = 0, sumY = 0;
    for(Point p : points) {
      sumX += p.x;
      sumY += p.y;
    }
    return new Point(sumX / points.size(), sumY / points.size());
  }

  /**
   * Rysuje wielokąt na podanym kontekście graficznym.
   *
   * @param g Kontekst graficzny do rysowania (Graphics2D).
   * @param isActive Określa, czy wielokąt jest aktywny (wyróżniony).
   */
  @Override
  public void draw(Graphics2D g, boolean isActive) {
    if(points.size() < 2) return;
    
    Polygon poly = new Polygon();
    for(Point p : points) poly.addPoint(p.x, p.y);
    
    Graphics2D g2d = (Graphics2D) g.create();
    Point center = getCenter();
    g2d.rotate(Math.toRadians(rotation), center.x, center.y);
    
    g2d.setColor(color);
    g2d.fillPolygon(poly);
    
    if(isActive) {
      g2d.setStroke(ACTIVE_STROKE);
      g2d.setColor(Color.BLACK);
      g2d.drawPolygon(poly);
    }

    g2d.dispose();
  }

  /**
   * Sprawdza, czy punkt o podanych współrzędnych znajduje się wewnątrz wielokąta.
   *
   * @param x Współrzędna X punktu.
   * @param y Współrzędna Y punktu.
   * @return true jeśli punkt znajduje się w wielokącie, w przeciwnym razie false.
   */
  @Override
  public boolean wasClicked(int x, int y) {
    Polygon poly = new Polygon();
    for(Point p : points) poly.addPoint(p.x, p.y);
    return poly.contains(x, y);
  }

  /**
   * Przesuwa wielokąt o zadany wektor (dx, dy).
   *
   * @param dx Przesunięcie w osi X.
   * @param dy Przesunięcie w osi Y.
   */
  @Override
  public void move(int dx, int dy) {
    for(Point p : points) {
      p.x += dx;
      p.y += dy;
    }
  }

  /**
   * Skaluje wielokąt o podany współczynnik względem jego środka.
   *
   * @param factor Współczynnik skalowania (np. 1.1 powiększa, 0.9 pomniejsza).
   */
  @Override
  public void scale(double factor) {
    int centerX = 0, centerY = 0;
    for(Point p : points) {
      centerX += p.x;
      centerY += p.y;
    }

    centerX /= points.size();
    centerY /= points.size();
    
    for(Point p : points) {
      p.x = centerX + (int)((p.x - centerX) * factor);
      p.y = centerY + (int)((p.y - centerY) * factor);
    }
  }

  /**
   * Obraca wielokąt o podany kąt w stopniach względem środka prostokąta otaczającego.
   *
   * @param degrees Kąt obrotu w stopniach.
   */
  @Override
  public void rotate(double degrees) {
    Rectangle bounds = getBounds();
    int centerX = bounds.x + bounds.width/2;
    int centerY = bounds.y + bounds.height/2;
    
    double radians = Math.toRadians(degrees);
    for(Point p : points) {
      int x = p.x - centerX;
      int y = p.y - centerY;
      
      int newX = (int)(x * Math.cos(radians) - y * Math.sin(radians));
      int newY = (int)(x * Math.sin(radians) + y * Math.cos(radians));
      
      p.x = newX + centerX;
      p.y = newY + centerY;
    }
  }

  /**
   * Zwraca prostokąt otaczający wielokąt.
   *
   * @return Prostokąt otaczający wszystkie wierzchołki wielokąta.
   */
  private Rectangle getBounds() {
    int minX = Integer.MAX_VALUE;
    int minY = Integer.MAX_VALUE;
    int maxX = Integer.MIN_VALUE;
    int maxY = Integer.MIN_VALUE;
    
    for(Point p : points) {
      if(p.x < minX) minX = p.x;
      if(p.y < minY) minY = p.y;
      if(p.x > maxX) maxX = p.x;
      if(p.y > maxY) maxY = p.y;
    }
    
    return new Rectangle(minX, minY, maxX - minX, maxY - minY);
  }
}