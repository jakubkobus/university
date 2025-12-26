
import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.*;
import javafx.stage.Stage;
import java.util.ArrayList;
import java.util.List;

public class TrojkatPascalaFX extends Application {
  private TextField inField;
  private TextArea outArea;

  public static void main(String[] args) {
    launch(args);
  }

  @Override
  public void start(Stage primaryStage) {
    VBox root = new VBox(10);
    root.setPadding(new Insets(10));

    HBox inputPanel = new HBox(10);
    inputPanel.getChildren().addAll(
      new Label("Wysokosc:"),
      inField = new TextField(),
      new Button("Uruchom") {{
        setOnAction(e -> generateTriangle());
      }}
    );

    outArea = new TextArea();
    outArea.setEditable(false);
    outArea.setFont(javafx.scene.text.Font.font("Monospaced", 14));
    outArea.setStyle("-fx-control-inner-background: #f0f0f0;");

    root.getChildren().addAll(inputPanel, outArea);

    Scene scene = new Scene(root, 600, 400);
    primaryStage.setTitle("Trojkat Pascala");
    primaryStage.setScene(scene);
    primaryStage.show();
  }

  private void generateTriangle() {
    try {
      int size = Integer.parseInt(inField.getText());
      if(size < 1)
        throw new IllegalArgumentException("Rozmiar musi byc wiekszy lub rowny 1");

      List<List<Integer>> triangle = generatePascalTriangle(size);
      List<String> rows = new ArrayList<>();

      for(List<Integer> row : triangle) {
        StringBuilder sb = new StringBuilder();

        for(int num : row)
          sb.append(String.format("%4d ", num));

        if(sb.length() > 0)
          sb.setLength(sb.length() - 1);
          
        rows.add(sb.toString());
      }

      int maxWidth = rows.isEmpty() ? 0 : rows.get(rows.size() - 1).length();
      StringBuilder output = new StringBuilder();

      for(String row : rows) {
        int padding = (maxWidth - row.length()) / 2;
        String spaces = " ".repeat(padding);
        output.append(spaces).append(row).append("\n");
      }

      outArea.setText(output.toString());
    } catch(NumberFormatException e) {
      showAlert("Nieprawidlowa liczba", "Blad");
    } catch(IllegalArgumentException e) {
      showAlert(e.getMessage(), "Blad");
    }
  }

  private void showAlert(String message, String title) {
    Alert alert = new Alert(Alert.AlertType.ERROR);
    alert.setTitle(title);
    alert.setHeaderText(null);
    alert.setContentText(message);
    alert.showAndWait();
  }

  private List<List<Integer>> generatePascalTriangle(int size) {
    List<List<Integer>> triangle = new ArrayList<>();

    for(int i = 0; i < size; i++) {
      List<Integer> row = new ArrayList<>();
      row.add(1);

      for(int j = 1; j < i; j++) 
        row.add(triangle.get(i-1).get(j-1) + triangle.get(i-1).get(j));

      if(i > 0)
        row.add(1);

      triangle.add(row);
    }

    return triangle;
  }
}