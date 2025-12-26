package pl.edu.pwr.tplab.faktura.repository.impl;

import pl.edu.pwr.tplab.faktura.model.Customer;
import pl.edu.pwr.tplab.faktura.model.Invoice;
import pl.edu.pwr.tplab.faktura.model.InvoiceLine;
import pl.edu.pwr.tplab.faktura.model.Item;
import pl.edu.pwr.tplab.faktura.repository.InvoiceRepository;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class MySqlInvoiceRepository implements InvoiceRepository {

  private final Connection connection;
  private static final int IDX_INVOICE_CUSTOMER = 1;
  private static final int IDX_INVOICE_NUMBER = 2;
  private static final int IDX_INVOICE_TOTAL = 3;
  private static final int IDX_LINE_INVOICE_ID = 1;
  private static final int IDX_LINE_ITEM_ID = 2;
  private static final int IDX_LINE_QUANTITY = 3;
  private static final int IDX_LINE_PRICE = 4;
  private static final int IDX_GENERATED = 1;

  public MySqlInvoiceRepository(Connection connection) {
    this.connection = connection;
  }

  @Override
  public Invoice save(Invoice invoice) {
    String sqlInvoice = "INSERT INTO invoices (customer_id, number, total) VALUES (?, ?, ?)";
    String sqlLine = "INSERT INTO invoice_lines (invoice_id, item_id, quantity, price) VALUES (?, ?, ?, ?)";

    try {
      connection.setAutoCommit(false);

      int invoiceId;
      try (PreparedStatement psInvoice = connection.prepareStatement(sqlInvoice, Statement.RETURN_GENERATED_KEYS)) {

  psInvoice.setInt(IDX_INVOICE_CUSTOMER, invoice.getCustomer().getId());
  psInvoice.setString(IDX_INVOICE_NUMBER, invoice.getNumber());
  psInvoice.setDouble(IDX_INVOICE_TOTAL, invoice.calculateTotalSum());
        psInvoice.executeUpdate();

        try (ResultSet generatedKeys = psInvoice.getGeneratedKeys()) {
          if (generatedKeys.next()) {
            invoiceId = generatedKeys.getInt(IDX_GENERATED);
            invoice.setId(invoiceId);
          } else {
            throw new SQLException("Błąd podczas zapisywania faktury, brak uzyskanego ID.");
          }
        }
      }

      try (PreparedStatement psLine = connection.prepareStatement(sqlLine)) {
        for (InvoiceLine line : invoice.getLines()) {
          psLine.setInt(IDX_LINE_INVOICE_ID, invoiceId);
          psLine.setInt(IDX_LINE_ITEM_ID, line.getItem().getId());
          psLine.setInt(IDX_LINE_QUANTITY, line.getQuantity());
          psLine.setDouble(IDX_LINE_PRICE, line.getPrice());
          psLine.addBatch();
        }
        psLine.executeBatch();
      }

      connection.commit();

    } catch (SQLException e) {
      try {
        connection.rollback();
      } catch (SQLException ex) {
        System.err.println("Błąd podczas wycofywania transakcji: " + ex.getMessage());
      }
      throw new RuntimeException("Błąd podczas zapisywania faktury", e);
    } finally {
      try {
        connection.setAutoCommit(true);
      } catch (SQLException e) {
        System.err.println("Błąd podczas resetowania auto-commit: " + e.getMessage());
      }
    }
    return invoice;
  }

  @Override
  public Optional<Invoice> findById(int id) {
    String sqlInvoice = "SELECT i.id, i.number, i.total, " +
        "c.id AS customer_id, c.name AS customer_name, c.nip " +
        "FROM invoices i " +
        "JOIN customers c ON i.customer_id = c.id " +
        "WHERE i.id = ? " +
        "ORDER BY i.id";

    Invoice invoice = null;
    Customer customer = null;

    try (PreparedStatement psInvoice = connection.prepareStatement(sqlInvoice)) {
      psInvoice.setInt(1, id);

      try (ResultSet rsInvoice = psInvoice.executeQuery()) {
        if (rsInvoice.next()) {
          customer = new Customer();
          customer.setId(rsInvoice.getInt("customer_id"));
          customer.setName(rsInvoice.getString("customer_name"));
          customer.setNIP(rsInvoice.getString("nip"));

          invoice = new Invoice(customer);
          invoice.setId(rsInvoice.getInt("id"));
          invoice.setNumber(rsInvoice.getString("number"));
        } else {
          return Optional.empty();
        }
      }
    } catch (SQLException e) {
      throw new RuntimeException("Błąd podczas wyszukiwania faktury według ID", e);
    }

    String sqlLines = "SELECT il.quantity, il.price, " +
        "it.id AS item_id, it.name AS item_name " +
        "FROM invoice_lines il " +
        "JOIN items it ON il.item_id = it.id " +
        "WHERE il.invoice_id = ?";

    try (PreparedStatement psLines = connection.prepareStatement(sqlLines)) {
      psLines.setInt(1, id);

      try (ResultSet rsLines = psLines.executeQuery()) {
        while (rsLines.next()) {
          Item item = new Item();
          item.setId(rsLines.getInt("item_id"));
          item.setName(rsLines.getString("item_name"));

          int quantity = rsLines.getInt("quantity");
          double price = rsLines.getDouble("price");

          invoice.addLine(item, quantity, price);
        }
      }
    } catch (SQLException e) {
      throw new RuntimeException("Błąd podczas wyszukiwania pozycji faktury", e);
    }

    return Optional.of(invoice);
  }

  public List<Invoice> findByCustomerId(int customerId) {
    List<Invoice> invoices = new ArrayList<>();
    String sql = "SELECT id FROM invoices WHERE customer_id = ? ORDER BY id";

    try (PreparedStatement ps = connection.prepareStatement(sql)) {
      ps.setInt(1, customerId);

      try (ResultSet rs = ps.executeQuery()) {
        while (rs.next()) {
          int invoiceId = rs.getInt("id");
          findById(invoiceId).ifPresent(invoices::add);
        }
      }
    } catch (SQLException e) {
      throw new RuntimeException("Błąd podczas wyszukiwania faktur według ID klienta", e);
    }
    return invoices;
  }

  @Override
  public List<Invoice> findAll() {
    List<Invoice> invoices = new ArrayList<>();
    String sql = "SELECT id FROM invoices ORDER BY id";

    try (Statement st = connection.createStatement();
         ResultSet rs = st.executeQuery(sql)) {

      while (rs.next()) {
        int invoiceId = rs.getInt("id");
        findById(invoiceId).ifPresent(invoices::add);
      }
    } catch (SQLException e) {
      throw new RuntimeException("Błąd podczas wyszukiwania wszystkich faktur", e);
    }
    return invoices;
  }
}
