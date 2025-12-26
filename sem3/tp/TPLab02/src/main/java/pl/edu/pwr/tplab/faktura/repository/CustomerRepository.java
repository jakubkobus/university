package pl.edu.pwr.tplab.faktura.repository;

import pl.edu.pwr.tplab.faktura.model.Customer;
import java.util.List;
import java.util.Optional;

public interface CustomerRepository {
  Customer save(Customer customer);

  Optional<Customer> findById(int id);

  List<Customer> findAll();
}
