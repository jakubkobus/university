import javax.swing.*;
import java.awt.*;
import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class WierszTrojkataPascalaGUI extends JFrame {
  private JTextField inputField;
  private JTextArea outputArea;
  private final String cppPath = "./wiersz_cpp";

  public static void main(String[] args) {
    SwingUtilities.invokeLater(() -> new WierszTrojkataPascalaGUI().setVisible(true));
  }

  public WierszTrojkataPascalaGUI() {
    setTitle("Wiersz Trojkata Pascala");
    setLayout(new BorderLayout(10, 10));

    JPanel topPanel = new JPanel(new FlowLayout());
    topPanel.add(new JLabel("Parametry:"));
    inputField = new JTextField(20);
    topPanel.add(inputField);
    topPanel.add(new JButton("Uruchom") {{
      addActionListener(e -> runProcess());
    }});

    outputArea = new JTextArea();
    outputArea.setEditable(false);
    outputArea.setFont(new Font(Font.MONOSPACED, Font.PLAIN, 14));
    add(topPanel, BorderLayout.NORTH);
    add(new JScrollPane(outputArea), BorderLayout.CENTER);

    setSize(600, 400);
    setLocationRelativeTo(null);
    setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
  }

  private void runProcess() {
    String input = inputField.getText().trim();
    try {
      if(input.isEmpty())
        throw new IllegalArgumentException("Brak parametrow");
      
      String[] parts = input.split("\\s+");
      if(parts.length < 2)
        throw new IllegalArgumentException("Zbyt malo parametrow");
      
      int row = Integer.parseInt(parts[0]);
      if(row < 0)
        throw new IllegalArgumentException("Numer wiersza musi byc wiekszy lub rowny 0");

      for(int i = 1; i < parts.length; i++) {
        int column = Integer.parseInt(parts[i]);
        if(column < 0 || column > row)
          throw new IllegalArgumentException(
            "Kolumna musi byc w zakresie 0-" + row
          );
      }

      outputArea.setText("");

      List<String> command = new ArrayList<>();
      command.add(cppPath);
      for(String part : parts)
        command.add(part);

      ProcessBuilder pb = new ProcessBuilder(command);
      pb.redirectErrorStream(true);

      Process process = pb.start();
      SwingWorker<Void, String> worker = new SwingWorker<>() {
          @Override
          protected Void doInBackground() throws Exception {
            try(BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()))) {
              String line;
              while((line = reader.readLine()) != null)
                publish(line + "\n");
            }

            process.waitFor();
            return null;
          }

          @Override
          protected void process(List<String> chunks) {
            chunks.forEach(outputArea::append);
          }
      };
      worker.execute();
    } catch(NumberFormatException e) {
      JOptionPane.showMessageDialog(
        this,
        "Nieprawidlowy parametr",
        "Blad",
        JOptionPane.ERROR_MESSAGE
      );
    } catch(IllegalArgumentException | IOException e) {
      JOptionPane.showMessageDialog(
        this,
        e.getMessage(),
        "Blad",
        JOptionPane.ERROR_MESSAGE
      );
    }
  }
}