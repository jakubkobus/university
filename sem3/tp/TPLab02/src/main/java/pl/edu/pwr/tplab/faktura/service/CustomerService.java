package pl.edu.pwr.tplab.faktura.service;

import java.util.List;

import pl.edu.pwr.tplab.faktura.model.Customer;
import pl.edu.pwr.tplab.faktura.repository.CustomerRepository;
import pl.edu.pwr.tplab.faktura.validator.CustomerValidator;

public class CustomerService {
  private final CustomerRepository customerRepository;

  public CustomerService(CustomerRepository customerRepository) {
    this.customerRepository = customerRepository;
  }

  public Customer addCustomer(String name, String nip) {
    Customer customer = new Customer();
    customer.setName(name);
    customer.setNIP(nip);

    new CustomerValidator().validateForCreate(customer);

    return customerRepository.save(customer);
  }

  public List<Customer> getAllCustomers() {
    return customerRepository.findAll();
  }
}
