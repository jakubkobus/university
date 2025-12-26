public class Romb extends Czworokat {
  public Romb(double bok, double kat) {
    super(bok, bok, bok, bok, kat);
  }
  
  public double getPole() {
    return bok1 * bok1 * Math.sin(kat);
  }
  
  public double getObwod() {
    return 4 * bok1;
  }
  
  public String getNazwa() {
    return "Romb";
  }
}
