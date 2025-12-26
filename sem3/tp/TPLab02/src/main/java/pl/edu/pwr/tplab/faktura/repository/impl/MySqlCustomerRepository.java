package pl.edu.pwr.tplab.faktura.repository.impl;

import pl.edu.pwr.tplab.faktura.model.Customer;
import pl.edu.pwr.tplab.faktura.repository.CustomerRepository;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class MySqlCustomerRepository implements CustomerRepository {

  private final Connection connection;
  private static final int IDX_NAME = 1;
  private static final int IDX_NIP = 2;
  private static final int IDX_GENERATED = 1;

  public MySqlCustomerRepository(Connection connection) {
    this.connection = connection;
  }

  @Override
  public Customer save(Customer customer) {
    String sql = "INSERT INTO customers (name, nip) VALUES (?, ?)";
    try (PreparedStatement ps = connection.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)) {
  ps.setString(IDX_NAME, customer.getName());
  ps.setString(IDX_NIP, customer.getNIP());
      ps.executeUpdate();

      try (ResultSet generatedKeys = ps.getGeneratedKeys()) {
        if (generatedKeys.next()) {
          customer.setId(generatedKeys.getInt(IDX_GENERATED));
        }
      }
    } catch (SQLException e) {
      throw new RuntimeException("Błąd podczas zapisywania klienta", e);
    }
    return customer;
  }

  @Override
  public Optional<Customer> findById(int id) {
    String sql = "SELECT id, name, nip FROM customers WHERE id = ? ORDER BY id";
    try (PreparedStatement ps = connection.prepareStatement(sql)) {
      ps.setInt(1, id);
      try (ResultSet rs = ps.executeQuery()) {
        if (rs.next()) {
          Customer customer = new Customer();
          customer.setId(rs.getInt("id"));
          customer.setName(rs.getString("name"));
          customer.setNIP(rs.getString("nip"));
          return Optional.of(customer);
        }
      }
    } catch (SQLException e) {
      throw new RuntimeException("Błąd podczas wyszukiwania klienta według ID", e);
    }
    return Optional.empty();
  }

  @Override
  public List<Customer> findAll() {
    List<Customer> customers = new ArrayList<>();
    String sql = "SELECT id, name, nip FROM customers ORDER BY id";
    try (Statement st = connection.createStatement();
        ResultSet rs = st.executeQuery(sql)) {
      while (rs.next()) {
        Customer customer = new Customer();
        customer.setId(rs.getInt("id"));
        customer.setName(rs.getString("name"));
        customer.setNIP(rs.getString("nip"));
        customers.add(customer);
      }
    } catch (SQLException e) {
      throw new RuntimeException("Błąd podczas wyszukiwania wszystkich klientów", e);
    }
    return customers;
  }
}
