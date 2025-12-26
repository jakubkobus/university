import java.util.*;

public class Main {
  public static void main(String[] args) {
    List<Object[]> figury = new ArrayList<>();
    int i = 0;

    try {
      while(i < args.length) {
        String typ = args[i++].toLowerCase();

        switch(typ) {
            case "o":
              if(i >= args.length)
                throw new IllegalArgumentException("Brak promienia dla kola");

              double r = Double.parseDouble(args[i++]);
              figury.add(new Object[]{
                Figury.Jednoparametrowe.KOLO,
                r
              });
              break;

            case "p":
              if(i >= args.length)
                throw new IllegalArgumentException("Brak boku");

              double aP = Double.parseDouble(args[i++]);
              figury.add(new Object[]{
                Figury.Jednoparametrowe.PIECIOKAT,
                aP
              });
              break;

            case "s":
              if(i >= args.length) throw new IllegalArgumentException("Brak boku");
              double aS = Double.parseDouble(args[i++]);
              figury.add(new Object[]{
                Figury.Jednoparametrowe.SZESCIOKAT,
                aS
              });
              break;

            case "c":
              List<Double> params = new ArrayList<>();
              while(i < args.length && isNumber(args[i]))
                params.add(Double.parseDouble(args[i++]));

              if(params.size() == 2) {
                double a = params.get(0);
                double kat = params.get(1);
                
                if(kat == 90.0)
                  figury.add(new Object[]{
                    Figury.Jednoparametrowe.KWADRAT,
                    a
                  });
                else 
                  figury.add(new Object[]{
                    Figury.Dwuparametrowe.ROMB,
                    a,
                    kat
                  });
              } else if(params.size() == 5) {
                List<Double> boki = new ArrayList<>(params.subList(0, 4));
                double kat = params.get(4);
                Collections.sort(boki);

                if(boki.get(0).equals(boki.get(3))) {
                  if(kat == 90.0)
                    figury.add(new Object[]{
                      Figury.Jednoparametrowe.KWADRAT,
                      boki.get(0)
                    });
                  else
                    figury.add(new Object[]{
                      Figury.Dwuparametrowe.ROMB,
                      boki.get(0), kat
                    });
                } else if(boki.get(0).equals(boki.get(1)) && 
                          boki.get(2).equals(boki.get(3)) && 
                          kat == 90.0) {
                    figury.add(new Object[]{
                      Figury.Dwuparametrowe.PROSTOKAT,
                      boki.get(0),
                      boki.get(2)
                    });
                } else throw new IllegalArgumentException("Nieprawidlowe parametry czworokata");
              } else throw new IllegalArgumentException("Nieprawidlowa liczba parametrow dla czworokata");

              break;

            default:
              throw new IllegalArgumentException("Nieznany typ figury: " + typ);
        }
      }
    } catch(NumberFormatException e) {
      System.out.println("Bledny format liczby");
      return;
    } catch(IllegalArgumentException e) {
      System.out.println("Blad: " + e.getMessage());
      return;
    }

    for(Object[] f : figury) {
      if(f[0] instanceof Figury.Jednoparametrowe) {
        Figury.Jednoparametrowe fig = (Figury.Jednoparametrowe) f[0];
        double param = (Double) f[1];
        System.out.printf(
          "%s: Obwod = %.2f | Pole = %.2f\n",
          fig.getNazwa(),
          fig.getObwod(param),
          fig.getPole(param)
        );
      } else if(f[0] instanceof Figury.Dwuparametrowe) {
        Figury.Dwuparametrowe fig = (Figury.Dwuparametrowe) f[0];
        double p1 = (Double) f[1];
        double p2 = (Double) f[2];
        System.out.printf(
          "%s: Obwod = %.2f | Pole = %.2f\n",
          fig.getNazwa(),
          fig.getObwod(p1, p2),
          fig.getPole(p1, p2)
        );
      }
    }
  }

  private static boolean isNumber(String s) {
    try {
      Double.parseDouble(s);
      return true;
    } catch(NumberFormatException e) {
      return false;
    }
  }
}