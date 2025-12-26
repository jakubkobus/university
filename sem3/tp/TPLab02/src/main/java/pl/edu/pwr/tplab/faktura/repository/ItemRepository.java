package pl.edu.pwr.tplab.faktura.repository;

import pl.edu.pwr.tplab.faktura.model.Item;
import java.util.List;
import java.util.Optional;

public interface ItemRepository {
  Item save(Item item);

  Optional<Item> findById(int id);

  List<Item> findAll();
}
