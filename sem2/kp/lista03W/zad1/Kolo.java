public class Kolo extends Figura {
  private double promien;
  
  public Kolo(double promien) {
    this.promien = promien;
  }
  
  public double getPole() {
    return Math.PI * promien * promien;
  }
  
  public double getObwod() {
    return 2 * Math.PI * promien;
  }
  
  public String getNazwa() {
    return "Kolo";
  }
}