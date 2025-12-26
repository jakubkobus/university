package pl.edu.pwr.tplab.faktura.service;

import pl.edu.pwr.tplab.faktura.model.Item;
import pl.edu.pwr.tplab.faktura.model.Invoice;
import pl.edu.pwr.tplab.faktura.model.Customer;
import pl.edu.pwr.tplab.faktura.validator.InvoiceValidator;
import pl.edu.pwr.tplab.faktura.repository.ItemRepository;
import pl.edu.pwr.tplab.faktura.repository.InvoiceRepository;
import pl.edu.pwr.tplab.faktura.repository.CustomerRepository;
import pl.edu.pwr.tplab.faktura.service.dto.LineItemDTO;

import java.util.List;

public class InvoiceService {

  private final InvoiceRepository invoiceRepository;
  private final CustomerRepository customerRepository;
  private final ItemRepository itemRepository;
  private static final int MILLIS_TO_SECONDS = 1000;

  public InvoiceService(InvoiceRepository invoiceRepository,
      CustomerRepository customerRepository,
      ItemRepository itemRepository) {
    this.invoiceRepository = invoiceRepository;
    this.customerRepository = customerRepository;
    this.itemRepository = itemRepository;
  }

  public Invoice issueInvoice(int customerId, List<LineItemDTO> lineDTOs) {
    Customer customer = customerRepository.findById(customerId)
        .orElseThrow(() -> new RuntimeException("Klient nie znaleziony"));

    new InvoiceValidator().validateForIssue(customerId, lineDTOs);

    Invoice invoice = new Invoice(customer);
    invoice.setNumber(generateInvoiceNumber());

    for (LineItemDTO dto : lineDTOs) {
      Item item = itemRepository.findById(dto.itemId())
          .orElseThrow(() -> new RuntimeException("Pozycja nie znaleziona"));

      invoice.addLine(item, dto.quantity(), dto.price());
    }

    System.out.println("Całkowita suma faktury: " + invoice.calculateTotalSum());

    return invoiceRepository.save(invoice);
  }

  public List<Invoice> getInvoicesByCustomerId(int customerId) {
    return invoiceRepository.findByCustomerId(customerId);
  }

  public Invoice getInvoiceById(int invoiceId) {
  return invoiceRepository.findById(invoiceId)
    .orElseThrow(() -> new RuntimeException("Faktura nie znaleziona"));
  }

  public java.util.Optional<Invoice> getInvoiceByIdOptional(int invoiceId) {
    return invoiceRepository.findById(invoiceId);
  }

  private String generateInvoiceNumber() {
    return "FV/" + System.currentTimeMillis() / MILLIS_TO_SECONDS;
  }
}
