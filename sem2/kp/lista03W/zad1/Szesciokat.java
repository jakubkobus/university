public class Szesciokat extends Figura {
  private double bok;
  
  public Szesciokat(double bok) {
    this.bok = bok;
  }
  
  public double getPole() {
    return (3 * Math.sqrt(3) * bok * bok) / 2;
  }
  
  public double getObwod() {
    return 6 * bok;
  }
  
  public String getNazwa() {
    return "Szesciokat foremny";
  }
}