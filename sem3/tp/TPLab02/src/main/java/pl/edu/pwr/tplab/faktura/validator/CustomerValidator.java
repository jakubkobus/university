package pl.edu.pwr.tplab.faktura.validator;

import pl.edu.pwr.tplab.faktura.model.Customer;

public class CustomerValidator {
  public void validateForCreate(Customer customer) {
    if (customer == null) {
      throw new IllegalArgumentException("Klient nie może być nullem");
    }
    if (customer.getName() == null || customer.getName().trim().isEmpty()) {
      throw new IllegalArgumentException("Nazwa klienta nie może być pusta");
    }
    if (customer.getNIP() == null || customer.getNIP().trim().isEmpty()) {
      throw new IllegalArgumentException("NIP klienta nie może być pusty");
    }
    String nip = customer.getNIP().replaceAll("\\s+", "");
    if (!nip.matches("\\d{8,15}")) {
      throw new IllegalArgumentException("NIP klienta musi być numeryczny i mieć od 8 do 15 cyfr");
    }
  }
}
