public class Kwadrat extends Czworokat {
  public Kwadrat(double bok) {
    super(bok, bok, bok, bok, 90);
  }
  
  public double getPole() {
    return bok1 * bok1;
  }
  
  public double getObwod() {
    return 4 * bok1;
  }
  
  public String getNazwa() {
    return "Kwadrat";
  }
}