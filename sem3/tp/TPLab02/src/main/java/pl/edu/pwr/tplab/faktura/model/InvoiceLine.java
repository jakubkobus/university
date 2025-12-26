package pl.edu.pwr.tplab.faktura.model;

public class InvoiceLine {
  private Item item;
  private int quantity;
  private double price;

  public InvoiceLine(Item item, int quantity, double price) {
    this.item = item;
    this.quantity = quantity;
    this.price = price;
  }

  public double calculateValue() {
    return quantity * price;
  }

  public Item getItem() {
    return item;
  }

  public int getQuantity() {
    return quantity;
  }

  public double getPrice() {
    return price;
  }
}
