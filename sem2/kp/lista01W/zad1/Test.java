public class Test {
  public static void main(String[] args) {
    if(args.length < 1) {
      System.out.println("Brak argumentow");
      return;
    }

    int n;
    WierszTrojkataPascala wiersz;

    try {
      // Maksymalny wiersz jaki mozna policzyc to 33, ktorego najwieksza wartosc wynosi 1_166_803_110
      // W przypadku n = 34 najwieksza wartosc przekracza limit typu int (2^31 - 1) o okolo 150 milionow
      n = Integer.parseInt(args[0]);

      if(n < 0)
        throw new NumberFormatException();

      wiersz = new WierszTrojkataPascala(n);
      wiersz.wygenerujWiersz();
    } catch(NumberFormatException e) {
      System.out.println(args[0] + " - Nieprawidlowy numer wiersza");
      return;
    }

    for(int i = 1; i < args.length; i++) {
      try {
        int m = Integer.parseInt(args[i]);

        if(m < 0 || m > n)
          throw new IllegalArgumentException(args[i] + " - licza spoza zakresu");

        System.out.println(args[i] + " - " + wiersz.m_tyElementWiersza(m));
      } catch(NumberFormatException e) {
        System.out.println(args[i] + " - nieprawidlowa dana");
      } catch(IllegalArgumentException e) {
        System.out.println(e.getMessage());
      }
    }
  }
}

