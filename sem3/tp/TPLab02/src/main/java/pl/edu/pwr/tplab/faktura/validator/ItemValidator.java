package pl.edu.pwr.tplab.faktura.validator;

import pl.edu.pwr.tplab.faktura.model.Item;

public class ItemValidator {

  public void validateForCreate(Item item) {
    if (item == null) {
      throw new IllegalArgumentException("Pozycja nie może być nullem");
    }
    if (item.getName() == null || item.getName().trim().isEmpty()) {
      throw new IllegalArgumentException("Nazwa pozycji nie może być pusta");
    }
  }
}
