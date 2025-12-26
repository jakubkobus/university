import java.awt.*;
import java.awt.event.*;
import java.io.*;
import java.util.ArrayList;
import java.util.List;

import javax.swing.JColorChooser;

/**
 * Klasa Surface jest rozszerzeniem klasy Panel i służy do rysowania oraz manipulacji
 * figurami geometrycznymi na powierzchni graficznej.
 * 
 * <p>Klasa obsługuje różne tryby rysowania, takie jak rysowanie prostokątów, kół
 * oraz wielokątów. Umożliwia również interakcję z istniejącymi figurami, w tym
 * przesuwanie, skalowanie, obracanie oraz zmianę koloru.</p>
 * 
 * <p>Powierzchnia obsługuje zdarzenia myszy (kliknięcia, przeciąganie, przewijanie)
 * oraz klawiatury (np. obracanie figury za pomocą klawiszy strzałek z wciśniętym
 * klawiszem Ctrl).</p>
 * 
 * <p>Klasa umożliwia również zapis i odczyt stanu figur do/z pliku za pomocą
 * serializacji.</p>
 * 
 * <p>Główne funkcjonalności klasy Surface:</p>
 * <ul>
 *   <li>Rysowanie figur geometrycznych w różnych trybach.</li>
 *   <li>Interakcja z figurami: przesuwanie, skalowanie, obracanie, zmiana koloru.</li>
 *   <li>Obsługa menu kontekstowego dla zmiany koloru figury.</li>
 *   <li>Zapis i odczyt stanu figur do/z pliku.</li>
 * </ul>
 * 
 * @author Jakub Kobus 283969
 * @version 1.0
 */
public class Surface extends Panel implements MouseListener, MouseMotionListener, MouseWheelListener {
  private Mode drawingMode = Mode.NONE;
  private List<Shape> shapes = new ArrayList<>();
  private List<Point> polygonPoints = new ArrayList<>();
  private Shape activeShape = null;
  private Shape currentShape = null;
  private int startX, startY, offsetX, offsetY;
  private double scaleOffsetX, scaleOffsetY;

  public Surface() {
    setBackground(Color.WHITE);
    addMouseListener(this);
    addMouseMotionListener(this);
    addMouseWheelListener(this);    
    addKeyListener(new KeyAdapter() {
      public void keyPressed(KeyEvent e) {
        if(activeShape != null && e.isControlDown()) {
          switch (e.getKeyCode()) {
            case KeyEvent.VK_LEFT:
              activeShape.rotate(-5);
              repaint();
              break;
            case KeyEvent.VK_RIGHT:
              activeShape.rotate(5);
              repaint();
              break;
          }
        }
      }
    });

    setFocusable(true);
  }

  /**
   * Ustawia tryb rysowania figur.
   * 
   * @param m Nowy tryb rysowania (np. prostokąt, koło, wielokąt, brak).
   */
  public void setDrawingMode(Mode m) {
    this.drawingMode = m;
    if(m == Mode.NONE) {
      currentShape = null;
      polygonPoints.clear();
    }
  
    repaint();
  }

  /**
   * Rysuje wszystkie figury na powierzchni oraz aktualnie rysowaną figurę.
   * 
   * @param g Kontekst graficzny do rysowania.
   */
  @Override
  public void paint(Graphics g) {
    super.paint(g);
    Graphics2D g2d = (Graphics2D) g;

    for(Shape shape : shapes)
      shape.draw(g2d, shape == activeShape);

    if(currentShape != null)
      currentShape.draw(g2d, false);
  }

  /**
   * Obsługuje naciśnięcie przycisku myszy.
   * 
   * @param e Zdarzenie myszy.
   */
  @Override
  public void mousePressed(MouseEvent e) {
    requestFocus();
    int x = e.getX();
    int y = e.getY();

    if(drawingMode != Mode.NONE) {
      if(drawingMode == Mode.POLYGON) {
        if(e.getButton() == MouseEvent.BUTTON1) {
          polygonPoints.add(new Point(x, y));

          if(currentShape == null)
            currentShape = new MyPolygon();
          
          ((MyPolygon) currentShape).addPoint(x, y);
          repaint();
        } else if(e.getButton() == MouseEvent.BUTTON3 && polygonPoints.size() >= 3) {
          shapes.add(currentShape);
          currentShape = null;
          polygonPoints.clear();
          drawingMode = Mode.NONE;
          repaint();
        }
      } else {
        startX = x;
        startY = y;
        if(drawingMode == Mode.CIRCLE)
          currentShape = new Circle(startX, startY, 0);
        else if(drawingMode == Mode.RECTANGLE) 
          currentShape = new Rectangle(startX, startY, 0, 0);
      }
    } else {
      activeShape = null;
      for(Shape shape : shapes) {
        if(shape.wasClicked(x, y)) {
          activeShape = shape;
          Point center = shape.getCenter();
          
          offsetX = x - center.x;
          offsetY = y - center.y;
          
          scaleOffsetX = 1.0;
          scaleOffsetY = 1.0;
          break;
        }
      }

      if(activeShape != null && e.getButton() == MouseEvent.BUTTON3) {
        Color newColor = JColorChooser.showDialog(this, "Wybierz kolor", Color.BLACK);
        if(newColor != null) {
          activeShape.setColor(newColor);
        }
      }
      
      repaint();
    }
  }

  /**
   * Obsługuje zwolnienie przycisku myszy.
   * 
   * @param e Zdarzenie myszy.
   */
  @Override
  public void mouseReleased(MouseEvent e) {
    if(drawingMode == Mode.CIRCLE || drawingMode == Mode.RECTANGLE) {
      if(currentShape != null) {
        shapes.add(currentShape);
        currentShape = null;
        drawingMode = Mode.NONE;
        repaint();
      }
    }
  }

  /**
   * Obsługuje przeciąganie myszy (ruch z wciśniętym przyciskiem).
   * 
   * @param e Zdarzenie myszy.
   */
  @Override
  public void mouseDragged(MouseEvent e) {
    int x = e.getX();
    int y = e.getY();

    if(activeShape != null) {
      Point center = activeShape.getCenter();
      int dx = (int)((x - center.x - offsetX) * scaleOffsetX);
      int dy = (int)((y - center.y - offsetY) * scaleOffsetY);
      activeShape.move(dx, dy);
      repaint();
    } else if(currentShape != null) {
      if(drawingMode == Mode.CIRCLE) {
        int radius = (int) Math.hypot(x - startX, y - startY);
        ((Circle) currentShape).setRadius(radius);
      } else if(drawingMode == Mode.RECTANGLE) {
        int width = x - startX;
        int height = y - startY;
        ((Rectangle) currentShape).setWidth(width);
        ((Rectangle) currentShape).setHeight(height);
      }
      repaint();
    }
  }

  /**
   * Obsługuje przewijanie kółkiem myszy (skalowanie aktywnej figury).
   * 
   * @param e Zdarzenie przewinięcia kółka myszy.
   */
  @Override
  public void mouseWheelMoved(MouseWheelEvent e) {
    if(activeShape != null) {
      double factor = e.getWheelRotation() < 0 ? 1.1 : 0.9;
      
      Point oldPoint = activeShape.getCenter();
      
      activeShape.scale(factor);
      
      scaleOffsetX *= factor;
      scaleOffsetY *= factor;
      
      Point newPoint = activeShape.getCenter();
      activeShape.move(
          oldPoint.x - newPoint.x,
          oldPoint.y - newPoint.y
      );
      
      repaint();
    }
  }

  /**
   * Zapisuje aktualny stan figur do pliku za pomocą serializacji.
   */
  public void save() {
    FileDialog fd = new FileDialog((Frame) getParent(), "Zapisz", FileDialog.SAVE);
    fd.setVisible(true);
    String filename = fd.getFile();
    String directory = fd.getDirectory();
    if(filename != null && directory != null) {
      try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(directory + filename))) {
        oos.writeObject(shapes);
      } catch (IOException ex) {
        ex.printStackTrace();
      }
    }
  }

  /**
   * Wczytuje stan figur z pliku za pomocą serializacji.
   */
  @SuppressWarnings("unchecked")
  public void load() {
    FileDialog fd = new FileDialog((Frame) getParent(), "Wczytaj", FileDialog.LOAD);
    fd.setVisible(true);
    String filename = fd.getFile();
    String directory = fd.getDirectory();
    if(filename != null && directory != null) {
      try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(directory + filename))) {
        shapes = (List<Shape>) ois.readObject();
        activeShape = null;
        repaint();
      } catch (IOException | ClassNotFoundException ex) {
        ex.printStackTrace();
      }
    }
  }

  /**
   * Nieużywana metoda obsługi kliknięcia myszy (wymagana przez interfejs).
   * 
   * @param e Zdarzenie myszy.
   */
  public void mouseClicked(MouseEvent e) {}

  /**
   * Nieużywana metoda obsługi wejścia kursora myszy na komponent (wymagana przez interfejs).
   * 
   * @param e Zdarzenie myszy.
   */
  public void mouseEntered(MouseEvent e) {}

  /**
   * Nieużywana metoda obsługi wyjścia kursora myszy z komponentu (wymagana przez interfejs).
   * 
   * @param e Zdarzenie myszy.
   */
  public void mouseExited(MouseEvent e) {}

  /**
   * Nieużywana metoda obsługi ruchu myszy (wymagana przez interfejs).
   * 
   * @param e Zdarzenie myszy.
   */
  public void mouseMoved(MouseEvent e) {}
}