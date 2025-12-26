public class Interfaces {
  public interface IFiguraJednoparametrowa {
    double getPole(double parametr);
    double getObwod(double parametr);
    String getNazwa();
  }

  public interface IFiguraDwuparametrowa {
    double getPole(double parametr1, double parametr2);
    double getObwod(double parametr1, double parametr2);
    String getNazwa();
  }
}
