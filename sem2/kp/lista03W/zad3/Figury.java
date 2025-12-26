public class Figury {
  public enum Jednoparametrowe implements Interfaces.IFiguraJednoparametrowa {
    KOLO {
      public double getPole(double r) { 
        return Math.PI * r * r;
      }

      public double getObwod(double r) { 
        return 2 * Math.PI * r;
      }

      public String getNazwa() { 
        return "Kolo";
      }
    },
    KWADRAT {
      public double getPole(double a) {
        return a * a;
      }

      public double getObwod(double a) {
        return 4 * a;
      }

      public String getNazwa() {
        return "Kwadrat";
      }
    },
    PIECIOKAT {
      public double getPole(double a) {
        return (5 * a * a)/(4 * Math.tan(Math.PI/5));
      }

      public double getObwod(double a) {
        return 5 * a;
      }

      public String getNazwa() {
        return "Pieciokat foremny";
      }
    },
    SZESCIOKAT {
      public double getPole(double a) {
        return (3 * Math.sqrt(3) * a * a)/2; 
      }

      public double getObwod(double a) {
        return 6 * a; 
      }

      public String getNazwa() {
        return "Szesciokat foremny";
      }
    };
  }

  public enum Dwuparametrowe implements Interfaces.IFiguraDwuparametrowa {
    PROSTOKAT {
      public double getPole(double a, double b) {
        return a * b;
      }

      public double getObwod(double a, double b) {
        return 2 * (a + b);
      }

      public String getNazwa() {
        return "Prostokat";
      }
    },
    ROMB {
      public double getPole(double a, double kat) {
        return a * a * Math.sin(Math.toRadians(kat));
      }

      public double getObwod(double a, double kat) {
        return 4 * a;
      }

      public String getNazwa() {
        return "Romb";
      }
    };
  }
}