package pl.edu.pwr.tplab.faktura.repository;

import pl.edu.pwr.tplab.faktura.model.Invoice;
import java.util.List;
import java.util.Optional;

public interface InvoiceRepository {
  Invoice save(Invoice invoice);

  Optional<Invoice> findById(int id);

  List<Invoice> findAll();
  
  List<Invoice> findByCustomerId(int customerId);
}
