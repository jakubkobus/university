import java.io.Serializable;

/**
 * Klasa reprezentująca odpowiedź serwera na żądanie klienta.
 * Zawiera status operacji oraz (opcjonalnie) rysunek drzewa.
 * 
 * @author Jakub Kobus
 */
public class Response implements Serializable {
  /**
   * Status odpowiedzi: SUCCESS (sukces) lub FAILURE (błąd).
   */
  public enum Status {
    SUCCESS, FAILURE
  }

  /** Status operacji */
  public Status status;
  /** Rysunek drzewa (tylko dla draw) */
  public String tree;

  /**
   * Tworzy odpowiedź z podanym statusem.
   * @param status status operacji
   */
  public Response(Status status) {
    this.status = status;
  }

  /**
   * Tworzy odpowiedź z podanym statusem i rysunkiem drzewa.
   * @param status status operacji
   * @param tree rysunek drzewa
   */
  public Response(Status status, String tree) {
    this.status = status;
    this.tree = tree;
  }
}