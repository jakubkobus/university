package pl.edu.pwr.tplab.faktura.validator;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import pl.edu.pwr.tplab.faktura.model.Customer;
import pl.edu.pwr.tplab.faktura.model.Item;

import pl.edu.pwr.tplab.faktura.service.dto.LineItemDTO;

import static org.junit.jupiter.api.Assertions.assertEquals;

import java.util.List;

class ValidatorTest {
  private CustomerValidator customerValidator;
  private ItemValidator itemValidator;
  private InvoiceValidator invoiceValidator;

  @BeforeEach
  void setUp() {
    customerValidator = new CustomerValidator();
    itemValidator = new ItemValidator();
    invoiceValidator = new InvoiceValidator();
  }

  @Test
  void testCustomerValidator_NotNullName() {
    Customer customer = new Customer();
    customer.setName(null);
    customer.setNIP("1234567890");

    try {
      customerValidator.validateForCreate(customer);
    } catch (IllegalArgumentException e) {
        assertEquals("Nazwa klienta nie może być pusta", e.getMessage());
    }
  }

  @Test
  void testItemValidator_NotEmptyName() {
    Item item = new Item();
    item.setName("");

    try {
      itemValidator.validateForCreate(item);
    } catch (IllegalArgumentException e) {
        assertEquals("Nazwa pozycji nie może być pusta", e.getMessage());
    }
  }

  @Test
  void testInvoiceValidator_ValidCustomerAndItems() {
    Customer customer = new Customer();
    customer.setName("Poprawny klient");
    customer.setNIP("1234567890");
    customer.setId(100);

    Item item = new Item();
    item.setName("Poprawny produkt");
    item.setId(200);

    Item item2 = new Item();
    item2.setName("Drugi produkt");
    item2.setId(201);
    
    LineItemDTO lineItem = new LineItemDTO(item.getId(), 1, 100.0);
    LineItemDTO lineItem2 = new LineItemDTO(item2.getId(), 2, 50.0);

    try {
      invoiceValidator.validateForIssue(customer.getId(), List.of(lineItem, lineItem2));
    } catch (IllegalArgumentException e) {
        assertEquals("Walidacja powinna zakończyć się sukcesem dla poprawnego klienta i pozycji", e.getMessage());
    }
  }
}