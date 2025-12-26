package pl.edu.pwr.tplab.faktura.model;

public class Customer {
  private int id;
  private String name;
  private String NIP;

  public int getId() {
    return id;
  }

  public void setId(int id) {
    this.id = id;
  }

  public String getName() {
    return name;
  }

  public void setName(String name) {
    this.name = name;
  }

  public String getNIP() {
    return NIP;
  }

  public void setNIP(String NIP) {
    this.NIP = NIP;
  }
}
