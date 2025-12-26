package pl.edu.pwr.tplab.faktura.util;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class DatabaseConnector {
  private static final String DB_URL = "jdbc:mysql://localhost:3306/tplab_faktura";
  private static final String USER = "fv_admin";
  private static final String PASS = "fv_password";

  private static Connection connectionInstance;

  private DatabaseConnector() { }

  public static Connection getConnection() throws SQLException {
    if (connectionInstance == null || connectionInstance.isClosed()) {
      try {
        Class.forName("com.mysql.cj.jdbc.Driver");

        connectionInstance = DriverManager.getConnection(DB_URL, USER, PASS);
      } catch (ClassNotFoundException e) {
        throw new SQLException("Sterownik MySQL JDBC Driver nie został znaleziony", e);
      }
    }
    return connectionInstance;
  }

  public static void closeConnection() {
    try {
      if (connectionInstance != null && !connectionInstance.isClosed()) {
        connectionInstance.close();
      }
    } catch (SQLException e) {
      e.printStackTrace();
    }
  }
}
