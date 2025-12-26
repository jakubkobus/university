public class Main {
  public static void main(String[] args) {
    if(args.length < 1) {
      System.out.println("Brak argumentow");
      return;
    }

    for(int i = 0; i < args.length; i++) {
      try {
        int arab = Integer.parseInt(args[i]);
        System.out.println(arab + " - " + ArabRzym.arab2rzym(arab));
      } catch(NumberFormatException e) {
        String rzym = args[i];
        try {
          System.out.println(rzym + " - " + ArabRzym.rzym2arab(rzym));
        } catch(ArabRzymException ex) {
          System.out.println(rzym + " - " + ex.getMessage());
        }
      } catch(ArabRzymException e) {
        System.out.println(args[i] + " - " + e.getMessage());
      }
    }
  }
}