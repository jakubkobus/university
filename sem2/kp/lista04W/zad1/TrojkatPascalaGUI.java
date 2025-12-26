import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.List;

public class TrojkatPascalaGUI extends JFrame {
  private JTextField inField;
  private JTextArea outArea;

  public static void main(String[] args) {
    SwingUtilities.invokeLater(() -> new TrojkatPascalaGUI().setVisible(true));
  }

  public TrojkatPascalaGUI() {
    setTitle("Trojkat Pascala");
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    setLayout(new BorderLayout(10, 10));

    JPanel topPanel = new JPanel(new FlowLayout());
    topPanel.add(new JLabel("Wysokosc:"));
    inField = new JTextField(10);
    topPanel.add(inField);
    JButton generateButton = new JButton("Uruchom");
    generateButton.addActionListener(e -> generateTriangle());
    topPanel.add(generateButton);

    outArea = new JTextArea();
    outArea.setEditable(false);
    outArea.setFont(new Font(Font.MONOSPACED, Font.PLAIN, 14));
    outArea.setBackground(new Color(240, 240, 240));
    JScrollPane scrollPane = new JScrollPane(outArea);

    add(topPanel, BorderLayout.NORTH);
    add(scrollPane, BorderLayout.CENTER);

    setSize(600, 400);
    setLocationRelativeTo(null);
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
      outArea.setText("");

      for(String row : rows) {
        int padding = (maxWidth - row.length()) / 2;
        String spaces = " ".repeat(padding);
        outArea.append(spaces + row + "\n");
      }
    } catch (NumberFormatException e) {
      JOptionPane.showMessageDialog(
        this,
        "Nieprawidlowa liczba",
        "Blad",
        JOptionPane.ERROR_MESSAGE
      );
    } catch (IllegalArgumentException e) {
      JOptionPane.showMessageDialog(
        this,
        e.getMessage(),
        "Blad",
        JOptionPane.ERROR_MESSAGE
      );
    }
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