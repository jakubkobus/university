public class Pieciokat extends Figura {
  private double bok;
  
  public Pieciokat(double bok) {
    this.bok = bok;
  }
  
  public double getPole() {
    return (5 * bok * bok) / (4 * Math.tan(Math.PI / 5));
  }
  
  public double getObwod() {
    return 5 * bok;
  }
  
  public String getNazwa() {
    return "Pieciokat foremny";
  }
}