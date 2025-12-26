import java.util.*;

public class Main {
  public static void main(String[] args) {
    List<Figura> figury = new ArrayList<>();
    int i = 0;

    try {
      while(i < args.length) {
        String typ = args[i++].toLowerCase();

        switch(typ) {
          case "o":
            if(i >= args.length)
              throw new IllegalArgumentException("Brak promienia dla kola");

            figury.add(new Kolo(Double.parseDouble(args[i])));
            i += 1;
            break;

          case "p":
          case "s":
            if(i >= args.length)
              throw new IllegalArgumentException("Brak boku");
              
            double bok = Double.parseDouble(args[i]);
            if(typ.equals("p")) 
              figury.add(new Pieciokat(bok));
            else 
              figury.add(new Szesciokat(bok));
            i += 1;
            break;

          case "c":
            List<Double> params = new ArrayList<>();
            while(i < args.length && isNumber(args[i])) {
              params.add(Double.parseDouble(args[i]));
              i++;
            }

            if(params.size() == 2) {
              double a = params.get(0);
              double kat = params.get(1);

              if(kat == 90.0) {
                figury.add(new Kwadrat(a));
              } else {
                figury.add(new Romb(a, kat));
              }
            } 
            else if(params.size() == 5) {
              List<Double> boki = new ArrayList<>(params.subList(0, 4));
              double kat = params.get(4);
              Collections.sort(boki);

              if(boki.get(0).equals(boki.get(3))) {
                if(kat == 90.0) {
                  figury.add(new Kwadrat(boki.get(0)));
                } else {
                  figury.add(new Romb(boki.get(0), kat));
                }
              } 
              else if(boki.get(0).equals(boki.get(1)) && 
                     boki.get(2).equals(boki.get(3)) && 
                     kat == 90.0) {
                figury.add(new Prostokat(boki.get(0), boki.get(2)));
              }
              else {
                throw new IllegalArgumentException("Nieprawidlowe parametry czworokata");
              }
            } 
            else {
              throw new IllegalArgumentException("Nieprawidlowa liczba parametrow dla czworokata");
            }
            break;

          default:
            throw new IllegalArgumentException("Nieznany typ figury: " + typ);
        }
      }
    } 
    catch(NumberFormatException e) {
      System.out.println("Bledny format liczby");
      return;
    } 
    catch(IllegalArgumentException e) {
      System.out.println("Blad: " + e.getMessage());
      return;
    }

    for(Figura f : figury) {
      System.out.printf(
        "%s: Obwod = %.2f | Pole = %.2f\n", 
        f.getNazwa(),
        f.getObwod(),
        f.getPole()
      );
    }
  }

  private static boolean isNumber(String s) {
    try {
      Double.parseDouble(s);
      return true;
    } 
    catch(NumberFormatException e) {
      return false;
    }
  }
}