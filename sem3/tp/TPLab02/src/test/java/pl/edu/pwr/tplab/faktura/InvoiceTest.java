package pl.edu.pwr.tplab.faktura;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import pl.edu.pwr.tplab.faktura.model.Customer;
import pl.edu.pwr.tplab.faktura.model.Invoice;
import pl.edu.pwr.tplab.faktura.model.Item;

import static org.junit.jupiter.api.Assertions.assertEquals;

class InvoiceTest {
  private Invoice invoice;
  private Item itemA;
  private Item itemB;

  @BeforeEach
  void setUp() {
    Customer customer = new Customer();
    customer.setName("Testowy Klient");
    invoice = new Invoice(customer);

    itemA = new Item();
    itemA.setName("Produkt A");

    itemB = new Item();
    itemB.setName("Produkt B");
  }

  @Test
  void testCalculateTotalSum_ShouldReturnZeroForEmptyInvoice() {
    double total = invoice.calculateTotalSum();

    assertEquals(0.0, total, 0.001);
  }

  @Test
  void testCalculateTotalSum_ShouldReturnCorrectSumForOneLine() {
    invoice.addLine(itemA, 2, 10.0);

    double total = invoice.calculateTotalSum();

    assertEquals(20.0, total, 0.001);
  }

  @Test
  void testCalculateTotalSum_ShouldReturnCorrectSumForMultipleLines() {
    invoice.addLine(itemA, 2, 10.0);
    invoice.addLine(itemB, 3, 5.0);

    double total = invoice.calculateTotalSum();

    assertEquals(35.0, total, 0.001);
  }
}