package pl.edu.pwr.tplab.faktura.service;

import java.util.List;

import pl.edu.pwr.tplab.faktura.model.Item;
import pl.edu.pwr.tplab.faktura.repository.ItemRepository;
import pl.edu.pwr.tplab.faktura.validator.ItemValidator;

public class ItemService {
    private final ItemRepository itemRepository;

    public ItemService(ItemRepository itemRepository) {
        this.itemRepository = itemRepository;
    }

    public Item addItem(String name) {
        Item item = new Item();
        item.setName(name);

        new ItemValidator().validateForCreate(item);

        return itemRepository.save(item);
    }

    public List<Item> getAllItems() {
        return itemRepository.findAll();
    }
}
