import java.awt.*;
import java.io.Serializable;

/**
 * Klasa Shape jest abstrakcyjną klasą bazową reprezentującą ogólną figurę geometryczną.
 * 
 * <p>Klasa definiuje podstawowe właściwości figury, takie jak kolor, współrzędne
 * (x, y), obrót oraz metody abstrakcyjne, które muszą zostać zaimplementowane
 * przez klasy dziedziczące.</p>
 * 
 * <p>Właściwości i metody tej klasy umożliwiają rysowanie figury, sprawdzanie,
 * czy punkt znajduje się w jej obrębie, przesuwanie, skalowanie oraz obracanie.</p>
 * 
 * <p>Klasa obsługuje również wyróżnianie aktywnej figury poprzez zastosowanie
 * specjalnego stylu obramowania.</p>
 * 
 * @author Jakub Kobus 283969
 * @version 1.0
 */
public abstract class Shape implements Serializable {
  protected static final Stroke ACTIVE_STROKE = new BasicStroke(
    2, 
    BasicStroke.CAP_BUTT, 
    BasicStroke.JOIN_BEVEL, 
    0, 
    new float[]{5}, 
    0 
  );

  protected Color color = Color.BLACK;
  protected int x, y;
  protected double rotation = 0;

  /**
   * Rysuje figurę na podanym kontekście graficznym.
   *
   * @param g Kontekst graficzny do rysowania (Graphics2D).
   * @param isActive Określa, czy figura jest aktywna (wyróżniona).
   */
  public abstract void draw(Graphics2D g, boolean isActive);

  /**
   * Sprawdza, czy punkt o podanych współrzędnych znajduje się wewnątrz figury.
   *
   * @param x Współrzędna X punktu.
   * @param y Współrzędna Y punktu.
   * @return true jeśli punkt znajduje się w figurze, w przeciwnym razie false.
   */
  public abstract boolean wasClicked(int x, int y);

  /**
   * Przesuwa figurę o zadany wektor (dx, dy).
   *
   * @param dx Przesunięcie w osi X.
   * @param dy Przesunięcie w osi Y.
   */
  public abstract void move(int dx, int dy);

  /**
   * Skaluje figurę o podany współczynnik.
   *
   * @param factor Współczynnik skalowania (np. 1.1 powiększa, 0.9 pomniejsza).
   */
  public abstract void scale(double factor);

  /**
   * Obraca figurę o podany kąt w stopniach.
   *
   * @param degrees Kąt obrotu w stopniach.
   */
  public abstract void rotate(double degrees);

  /**
   * Zwraca środek figury jako punkt.
   *
   * @return Punkt będący środkiem figury.
   */
  public abstract Point getCenter();
  
  /**
   * Ustawia kolor figury.
   *
   * @param clr Nowy kolor figury.
   */
  public void setColor(Color clr) {
    this.color = clr;
  }
}