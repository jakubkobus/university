package pl.edu.pwr.tplab.faktura.repository.impl;

import pl.edu.pwr.tplab.faktura.model.Item;
import pl.edu.pwr.tplab.faktura.repository.ItemRepository;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class MySqlItemRepository implements ItemRepository {

  private final Connection connection;

  public MySqlItemRepository(Connection connection) {
    this.connection = connection;
  }

  @Override
  public Item save(Item item) {
    String sql = "INSERT INTO items (name) VALUES (?)";

    try (PreparedStatement ps = connection.prepareStatement(sql, Statement.RETURN_GENERATED_KEYS)) {

      ps.setString(1, item.getName());
      int affectedRows = ps.executeUpdate();

      if (affectedRows == 0) {
        throw new SQLException("Tworzenie pozycji nie powiodło się, brak zmienionych wierszy.");
      }

      try (ResultSet generatedKeys = ps.getGeneratedKeys()) {
        if (generatedKeys.next()) {
          item.setId(generatedKeys.getInt(1));
        } else {
          throw new SQLException("Tworzenie pozycji nie powiodło się, brak uzyskanego ID.");
        }
      }
    } catch (SQLException e) {
      throw new RuntimeException("Błąd podczas zapisywania pozycji", e);
    }
    return item;
  }

  @Override
  public Optional<Item> findById(int id) {
    String sql = "SELECT id, name FROM items WHERE id = ? ORDER BY id";

    try (PreparedStatement ps = connection.prepareStatement(sql)) {
      ps.setInt(1, id);

      try (ResultSet rs = ps.executeQuery()) {
        if (rs.next()) {
          Item item = mapRowToItem(rs);
          return Optional.of(item);
        }
      }
    } catch (SQLException e) {
      throw new RuntimeException("Błąd podczas wyszukiwania pozycji według ID", e);
    }
    return Optional.empty();
  }

  @Override
  public List<Item> findAll() {
    List<Item> items = new ArrayList<>();
    String sql = "SELECT id, name FROM items ORDER BY id";

    try (Statement st = connection.createStatement();
        ResultSet rs = st.executeQuery(sql)) {

      while (rs.next()) {
        items.add(mapRowToItem(rs));
      }
    } catch (SQLException e) {
      throw new RuntimeException("Błąd podczas wyszukiwania wszystkich pozycji", e);
    }
    return items;
  }

  private Item mapRowToItem(ResultSet rs) throws SQLException {
    Item item = new Item();
    item.setId(rs.getInt("id"));
    item.setName(rs.getString("name"));
    return item;
  }
}
