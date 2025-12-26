public class Prostokat extends Czworokat {
  public Prostokat(double bok1, double bok2) {
    super(bok1, bok2, bok1, bok2, 90);
  }
  
  public double getPole() {
    return bok1 * bok2;
  }
  
  public double getObwod() {
    return 2 * (bok1 + bok2);
  }
  
  public String getNazwa() {
    return "Prostokat";
  }
}