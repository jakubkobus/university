package pl.edu.pwr.tplab.faktura.model;

import java.util.ArrayList;
import java.util.List;

public class Invoice {
  private int id;
  private String number;
  private Customer customer;
  private final List<InvoiceLine> lines;

  public Invoice(Customer customer) {
    this.customer = customer;
    this.lines = new ArrayList<>();
  }

  public void addLine(Item item, int quantity, double price) {
    this.lines.add(new InvoiceLine(item, quantity, price));
  }

  public double calculateTotalSum() {
    return lines.stream()
        .mapToDouble(InvoiceLine::calculateValue)
        .sum();
  }

  public List<InvoiceLine> getLines() {
    return List.copyOf(lines);
  }

  public Customer getCustomer() {
    return customer;
  }

  public String getNumber() {
    return number;
  }

  public void setNumber(String number) {
    this.number = number;
  }

  public void setId(int id) {
    this.id = id;
  }

  public int getId() {
    return id;
  }
}
