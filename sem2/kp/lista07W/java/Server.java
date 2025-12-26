import java.io.*;
import java.net.*;
import java.util.concurrent.*;

/**
 * Serwer obsługujący operacje na trzech drzewach binarnych (int, double, string) przez sieć.
 * Odpowiada obiektami klasy Response na żądania klientów.
 * 
 * Obsługiwane operacje: insert, delete, search, draw.
 * Obsługiwane typy: int, double, string.
 * 
 * @author Jakub Kobus
 */
public class Server {
  /** Port nasłuchiwania serwera */
  private final int PORT = 1234;

  /** Drzewo binarne dla typu int */
  private BinaryTree<Integer> intTree   = new BinaryTree<>();
  /** Drzewo binarne dla typu double */
  private BinaryTree<Double> doubleTree = new BinaryTree<>();
  /** Drzewo binarne dla typu string */
  private BinaryTree<String> stringTree = new BinaryTree<>();

  /**
   * Punkt wejścia serwera.
   */
  public static void main(String[] args) {
    new Server().run();
  }

  /**
   * Uruchamia serwer i obsługuje klientów w osobnych wątkach.
   */
  public void run() {
    ExecutorService pool = Executors.newCachedThreadPool();
    try (ServerSocket serverSocket = new ServerSocket(PORT)) {
      System.out.println("Server listening on localhost:" + PORT);
      while (true) {
        Socket clientSocket = serverSocket.accept();
        pool.execute(() -> handleClient(clientSocket));
      }
    } catch (IOException e) {
      e.printStackTrace();
    }
  }

  /**
   * Obsługuje pojedynczego klienta: odbiera żądania, wysyła odpowiedzi.
   * @param clientSocket gniazdo klienta
   */
  private void handleClient(Socket clientSocket) {
    try (
        ObjectOutputStream out = new ObjectOutputStream(clientSocket.getOutputStream());
        BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()))) {
      String inputLine;
      while ((inputLine = in.readLine()) != null) {
        Response response = handleRequest(inputLine.trim());
        out.writeObject(response);
        out.flush();
      }
    } catch (IOException e) {
      e.printStackTrace();
    } finally {
      try {
        clientSocket.close();
      } catch (IOException e) {
        e.printStackTrace();
      }
    }
  }

  /**
   * Przetwarza żądanie klienta i zwraca odpowiedni obiekt Response.
   * @param request żądanie tekstowe
   * @return odpowiedź Response
   */
  private Response handleRequest(String request) {
    String[] parts = request.split("\\s+", 3);
    if (parts.length < 2)
      return new Response(Response.Status.FAILURE);
    String command = parts[0].toLowerCase();
    String type = parts[1].toLowerCase();
    String value = parts.length == 3 ? parts[2] : null;

    switch (command) {
      case "insert":
        if (value == null)
          return new Response(Response.Status.FAILURE);
        return handleInsert(type, value);
      case "delete":
        if (value == null)
          return new Response(Response.Status.FAILURE);
        return handleDelete(type, value);
      case "search":
        if (value == null)
          return new Response(Response.Status.FAILURE);
        return handleSearch(type, value);
      case "draw":
        return handleDraw(type);
      default:
        return new Response(Response.Status.FAILURE);
    }
  }

  /**
   * Obsługuje operację insert dla danego typu.
   */
  private Response handleInsert(String type, String value) {
    try {
      switch (type) {
        case "int":
          intTree.insert(Integer.parseInt(value));
          return new Response(Response.Status.SUCCESS);
        case "double":
          doubleTree.insert(Double.parseDouble(value));
          return new Response(Response.Status.SUCCESS);
        case "string":
          stringTree.insert(value);
          return new Response(Response.Status.SUCCESS);
        default:
          return new Response(Response.Status.FAILURE);
      }
    } catch (Exception e) {
      return new Response(Response.Status.FAILURE);
    }
  }

  /**
   * Obsługuje operację delete dla danego typu.
   */
  private Response handleDelete(String type, String value) {
    try {
      switch (type) {
        case "int":
          return intTree.delete(Integer.parseInt(value))
              ? new Response(Response.Status.SUCCESS)
              : new Response(Response.Status.FAILURE);
        case "double":
          return doubleTree.delete(Double.parseDouble(value))
              ? new Response(Response.Status.SUCCESS)
              : new Response(Response.Status.FAILURE);
        case "string":
          return stringTree.delete(value)
              ? new Response(Response.Status.SUCCESS)
              : new Response(Response.Status.FAILURE);
        default:
          return new Response(Response.Status.FAILURE);
      }
    } catch (Exception e) {
      return new Response(Response.Status.FAILURE);
    }
  }

  /**
   * Obsługuje operację search dla danego typu.
   */
  private Response handleSearch(String type, String value) {
    try {
      switch (type) {
        case "int":
          return intTree.search(Integer.parseInt(value))
              ? new Response(Response.Status.SUCCESS)
              : new Response(Response.Status.FAILURE);
        case "double":
          return doubleTree.search(Double.parseDouble(value))
              ? new Response(Response.Status.SUCCESS)
              : new Response(Response.Status.FAILURE);
        case "string":
          return stringTree.search(value)
              ? new Response(Response.Status.SUCCESS)
              : new Response(Response.Status.FAILURE);
        default:
          return new Response(Response.Status.FAILURE);
      }
    } catch (Exception e) {
      return new Response(Response.Status.FAILURE);
    }
  }

  /**
   * Obsługuje operację draw dla danego typu.
   */
  private Response handleDraw(String type) {
    switch (type) {
      case "int":
        return new Response(Response.Status.SUCCESS, intTree.draw());
      case "double":
        return new Response(Response.Status.SUCCESS, doubleTree.draw());
      case "string":
        return new Response(Response.Status.SUCCESS, stringTree.draw());
      default:
        return new Response(Response.Status.FAILURE);
    }
  }
}