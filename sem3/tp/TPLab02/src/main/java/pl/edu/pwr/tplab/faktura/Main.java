package pl.edu.pwr.tplab.faktura;

import pl.edu.pwr.tplab.faktura.repository.ItemRepository;
import pl.edu.pwr.tplab.faktura.repository.InvoiceRepository;
import pl.edu.pwr.tplab.faktura.repository.CustomerRepository;
import pl.edu.pwr.tplab.faktura.repository.impl.MySqlItemRepository;
import pl.edu.pwr.tplab.faktura.repository.impl.MySqlInvoiceRepository;
import pl.edu.pwr.tplab.faktura.repository.impl.MySqlCustomerRepository;
import pl.edu.pwr.tplab.faktura.service.CustomerService;
import pl.edu.pwr.tplab.faktura.service.InvoiceService;
import pl.edu.pwr.tplab.faktura.service.ItemService;
import pl.edu.pwr.tplab.faktura.util.DatabaseConnector;
import pl.edu.pwr.tplab.faktura.model.Customer;
import pl.edu.pwr.tplab.faktura.model.Item;
import pl.edu.pwr.tplab.faktura.model.Invoice;
import pl.edu.pwr.tplab.faktura.model.InvoiceLine;
import pl.edu.pwr.tplab.faktura.service.dto.LineItemDTO;

import java.sql.Connection;
import java.util.Scanner;
import java.util.List;
import java.util.ArrayList;
import java.util.Optional;

public class Main {
  private static final int MENU_ISSUE = 1;
  private static final int MENU_ADD_CUSTOMER = 2;
  private static final int MENU_ADD_ITEM = 3;
  private static final int MENU_DISPLAY_CUSTOMERS = 4;
  private static final int MENU_DISPLAY_ITEMS = 5;
  private static final int MENU_DISPLAY_CUSTOMER_INVOICES = 6;
  private static final int MENU_DISPLAY_INVOICE = 7;
  private static final int MENU_EXIT = 0;

  public static void main(String[] args) {
    try {
      Connection connection = DatabaseConnector.getConnection();

      CustomerRepository customerRepo = new MySqlCustomerRepository(connection);
      ItemRepository itemRepo = new MySqlItemRepository(connection);
      InvoiceRepository invoiceRepo = new MySqlInvoiceRepository(connection);

      InvoiceService invoiceService = new InvoiceService(invoiceRepo, customerRepo, itemRepo);
      CustomerService customerService = new CustomerService(customerRepo);
      ItemService itemService = new ItemService(itemRepo);

      Scanner scanner = new Scanner(System.in);
      try {
        while (true) {
          displayMainMenu();
          try {
            int choice = Integer.parseInt(scanner.nextLine());
            switch (choice) {
              case MENU_ISSUE:
                handleIssueInvoice(invoiceService, customerService, itemService, scanner);
                break;
              case MENU_ADD_CUSTOMER:
                handleAddCustomer(customerService, scanner);
                break;
              case MENU_ADD_ITEM:
                handleAddItem(itemService, scanner);
                break;
              case MENU_DISPLAY_CUSTOMERS:
                handleDisplayCustomers(customerService);
                break;
              case MENU_DISPLAY_ITEMS:
                handleDisplayItems(itemService);
                break;
              case MENU_DISPLAY_CUSTOMER_INVOICES:
                handleDisplayCustomerInvoices(invoiceService, customerService, scanner);
                break;
              case MENU_DISPLAY_INVOICE:
                handleDisplayInvoiceDetails(invoiceService, scanner);
                break;
              case MENU_EXIT:
                DatabaseConnector.closeConnection();
                scanner.close();
                return;
              default:
                System.out.println("Nieznana opcja, spróbuj ponownie.");
            }
          } catch (NumberFormatException e) {
            System.out.println("Błąd: Wprowadź poprawną liczbę.");
          } catch (Exception e) {
            System.out.println("Wystąpił błąd: " + e.getMessage());
          }
          System.out.println("\nNaciśnij Enter, aby kontynuować...");
          scanner.nextLine();
        }
      } finally {
          try { DatabaseConnector.closeConnection(); } catch (Exception ignored) { }
          try { scanner.close(); } catch (Exception ignored) { }
        }

    } catch (Exception e) {
      e.printStackTrace();
    }
  }

  private static void displayMainMenu() {
    System.out.println("\n--------- Faktury ---------");
    System.out.println("1. Wystaw nową fakturę");
    System.out.println("2. Dodaj nowego klienta");
    System.out.println("3. Dodaj nowy artykuł");
    System.out.println("4. Wyświetl wszystkich klientów");
    System.out.println("5. Wyświetl wszystkie artykuły");
    System.out.println("6. Wyświetl faktury klienta");
    System.out.println("7. Wyświetl szczegóły faktury");
    System.out.println("-----------------------------");
    System.out.println("0. Wyjdź");
    System.out.print("Wybierz opcję: ");
  }

  private static void handleAddCustomer(CustomerService customerService, Scanner scanner) {
    System.out.println("--- Dodawanie Klienta ---");
    System.out.print("Podaj nazwę klienta: ");
    String name = scanner.nextLine();
    System.out.print("Podaj NIP klienta: ");
    String taxId = scanner.nextLine();

    if (name.trim().isEmpty() || taxId.trim().isEmpty()) {
      System.out.println("Błąd: Nazwa i NIP nie mogą być puste.");
      return;
    }

    customerService.addCustomer(name, taxId);
    System.out.println("Pomyślnie dodano klienta.");
  }

  private static void handleAddItem(ItemService itemService, Scanner scanner) {
    System.out.println("--- Dodawanie Artykułu ---");
    System.out.print("Podaj nazwę artykułu/usługi: ");
    String name = scanner.nextLine();

    if (name.trim().isEmpty()) {
      System.out.println("Błąd: Nazwa nie może być pusta.");
      return;
    }

    itemService.addItem(name);
    System.out.println("Pomyślnie dodano artykuł.");
  }

  private static void handleIssueInvoice(InvoiceService invoiceService, CustomerService customerService, ItemService itemService, Scanner scanner) {
    System.out.println("--- Wystawianie Faktury ---");

    List<Customer> customers = customerService.getAllCustomers();
    if (customers.isEmpty()) {
      System.out.println("Błąd: Nie ma żadnych klientów w systemie. Dodaj klienta, aby wystawić fakturę.");
      return;
    }
    System.out.println("Wybierz klienta (podaj ID):");
    customers.forEach(c -> System.out.printf("%d. %s (NIP: %s)\n", c.getId(), c.getName(), c.getNIP()));
    int customerId;
    try {
      customerId = Integer.parseInt(scanner.nextLine());
    } catch (NumberFormatException e) {
      System.out.println("Błąd: Nieprawidłowy ID klienta.");
      return;
    }

  List<Item> items = itemService.getAllItems();
    if (items.isEmpty()) {
      System.out.println("Błąd: Nie ma żadnych artykułów w systemie. Dodaj artykuł.");
      return;
    }

    List<LineItemDTO> lines = new ArrayList<>();
    while (true) {
      System.out.println("\n--- Dodawanie pozycji ('koniec' aby zakończyć) ---");
  items.forEach(a -> System.out.printf("%d. %s\n", a.getId(), a.getName()));
      System.out.print("Wybierz ID artykułu: ");
      String input = scanner.nextLine();
      if ("koniec".equalsIgnoreCase(input)) {
        break;
      }

      int itemId;
      try {
        itemId = Integer.parseInt(input);
      } catch (NumberFormatException e) {
        System.out.println("Błąd: Nieprawidłowy ID artykułu.");
        continue;
      }

      System.out.print("Podaj ilość: ");
      int quantity;
      try {
        quantity = Integer.parseInt(scanner.nextLine());
      } catch (NumberFormatException e) {
        System.out.println("Błąd: Nieprawidłowa ilość.");
        continue;
      }

      System.out.print("Podaj cenę jednostkową: ");
      double price;
      try {
        price = Double.parseDouble(scanner.nextLine());
      } catch (NumberFormatException e) {
        System.out.println("Błąd: Nieprawidłowa cena.");
        continue;
      }

      if (quantity <= 0 || price < 0) {
        System.out.println("Błąd: Ilość musi być dodatnia, a cena nie może być ujemna.");
        continue;
      }

      lines.add(new LineItemDTO(itemId, quantity, price));
      System.out.println("Dodano pozycję.");
    }

    if (lines.isEmpty()) {
      System.out.println("Anulowano wystawianie faktury (brak pozycji).");
      return;
    }

    Invoice newInvoice = invoiceService.issueInvoice(customerId, lines);
    System.out.println("\n--- SUKCES ---");
    System.out.println("Pomyślnie wystawiono fakturę:");
    displayInvoiceDetails(newInvoice);
  }

  private static void handleDisplayCustomers(CustomerService customerService) {
    System.out.println("--- Lista Klientów ---");
    List<Customer> customers = customerService.getAllCustomers();
    if (customers.isEmpty()) {
      System.out.println("Brak klientów w bazie danych.");
    } else {
      customers.forEach(c -> System.out.printf("ID: %d | Nazwa: %s | NIP: %s\n", c.getId(), c.getName(), c.getNIP()));
    }
  }

  private static void handleDisplayItems(ItemService itemService) {
    System.out.println("--- Lista Artykułów/Usług ---");
    List<Item> items = itemService.getAllItems();
    if (items.isEmpty()) {
      System.out.println("Brak artykułów w bazie danych.");
    } else {
      items.forEach(a -> System.out.printf("ID: %d | Nazwa: %s\n", a.getId(), a.getName()));
    }
  }

  private static void handleDisplayCustomerInvoices(InvoiceService invoiceService, CustomerService customerService, Scanner scanner) {
    System.out.println("--- Faktury Klienta ---");
    List<Customer> customers = customerService.getAllCustomers();
    if (customers.isEmpty()) {
      System.out.println("Brak klientów w bazie.");
      return;
    }
    System.out.println("Wybierz klienta (podaj ID):");
    customers.forEach(c -> System.out.printf("%d. %s\n", c.getId(), c.getName()));
    int customerId;
    try {
      customerId = Integer.parseInt(scanner.nextLine());
    } catch (NumberFormatException e) {
      System.out.println("Błąd: Nieprawidłowy ID klienta.");
      return;
    }

    List<Invoice> invoices = invoiceService.getInvoicesByCustomerId(customerId);
    if (invoices.isEmpty()) {
      System.out.println("Ten klient nie ma jeszcze żadnych faktur.");
    } else {
      String customerName = customers.stream()
          .filter(c -> c.getId() == customerId)
          .findFirst()
          .map(Customer::getName)
          .orElse("Nieznany Klient");
      System.out.printf("Faktury dla klienta '%s':\n", customerName);
      invoices.forEach(f -> {
        String idPart = String.format("ID: %d", f.getId());
        String numPart = String.format("Numer: %s", f.getNumber());
        String sumPart = String.format("Suma: %.2f PLN", f.calculateTotalSum());
        System.out.println(idPart + " | " + numPart + " | " + sumPart);
      });
    }
  }

  private static void handleDisplayInvoiceDetails(InvoiceService invoiceService, Scanner scanner) {
    System.out.println("--- Szczegóły Faktury ---");
    System.out.print("Podaj ID faktury, którą chcesz zobaczyć: ");
    int invoiceId;
    try {
      invoiceId = Integer.parseInt(scanner.nextLine());
    } catch (NumberFormatException e) {
      System.out.println("Błąd: Nieprawidłowy ID faktury.");
      return;
    }

  Optional<Invoice> foundInvoice = invoiceService.getInvoiceByIdOptional(invoiceId);

    if (foundInvoice.isPresent()) {
      displayInvoiceDetails(foundInvoice.get());
    } else {
      System.out.println("Nie znaleziono faktury o ID: " + invoiceId);
    }
  }

  private static void displayInvoiceDetails(Invoice invoice) {
    System.out.println("==========================================");
    System.out.printf("Faktura Numer: %s\n", invoice.getNumber());
    System.out.printf("ID Faktury:    %d\n", invoice.getId());
    System.out.println("------------------------------------------");
    System.out.println("Klient:");
    System.out.printf("  Nazwa: %s\n", invoice.getCustomer().getName());
    System.out.printf("  NIP:   %s\n", invoice.getCustomer().getNIP());
    System.out.println("------------------------------------------");
    System.out.println("Pozycje:");

    for (InvoiceLine line : invoice.getLines()) {
      System.out.printf("  - %s\n", line.getItem().getName());
      System.out.printf("    Ilość: %d x %.2f PLN = %.2f PLN\n",
          line.getQuantity(), line.getPrice(), line.calculateValue());
    }

    System.out.println("------------------------------------------");
    System.out.printf("SUMA CAŁKOWITA: %.2f PLN\n", invoice.calculateTotalSum());
    System.out.println("==========================================");
  }
}
