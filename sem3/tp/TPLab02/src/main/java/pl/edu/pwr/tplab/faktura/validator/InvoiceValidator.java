package pl.edu.pwr.tplab.faktura.validator;

import pl.edu.pwr.tplab.faktura.service.dto.LineItemDTO;

import java.util.List;

public class InvoiceValidator {

  public void validateForIssue(int customerId, List<LineItemDTO> lines) {
    if (customerId <= 0) {
      throw new IllegalArgumentException("Klient ID musi być dodatni");
    }
    if (lines == null || lines.isEmpty()) {
      throw new IllegalArgumentException("Faktura musi mieć przynajmniej jedną pozycję");
    }
    for (LineItemDTO l : lines) {
      if (l.quantity() <= 0) {
        throw new IllegalArgumentException("Ilość pozycji musi być dodatnia");
      }
      if (l.price() < 0) {
        throw new IllegalArgumentException("Cena pozycji nie może być ujemna");
      }
      if (l.itemId() <= 0) {
        throw new IllegalArgumentException("ID pozycji musi być dodatnie");
      }
    }
  }
}
