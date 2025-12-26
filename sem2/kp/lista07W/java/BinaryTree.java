/**
 * Klasa reprezentująca drzewo binarne dowolnego typu porównywalnego.
 * @author Jakub Kobus
 */
public class BinaryTree<T extends Comparable<T>> {
  /** Szerokość węzła w rysunku drzewa */
  private final int NODE_WIDTH = 8;

  /**
   * Wewnętrzna klasa reprezentująca węzeł drzewa.
   */
  private static class Node<T> {
    T value;
    Node<T> left, right;

    Node(T value) {
      this.value = value;
    }
  }

  /** Korzeń drzewa */
  private Node<T> root;

  /**
   * Wstawia nową wartość do drzewa.
   * @param value wartość do wstawienia
   */
  public synchronized void insert(T value) {
    root = insertRec(root, value);
  }

  /** 
   * Rekurencyjna metoda pomocnicza do wstawiania.
   */
  private Node<T> insertRec(Node<T> node, T value) {
    if (node == null)
      return new Node<T>(value);
    int cmp = value.compareTo(node.value);
    if (cmp < 0)
      node.left = insertRec(node.left, value);
    else if (cmp > 0)
      node.right = insertRec(node.right, value);
    return node;
  }

  /**
   * Sprawdza, czy wartość istnieje w drzewie.
   * @param value szukana wartość
   * @return true jeśli istnieje, false w przeciwnym razie
   */
  public synchronized boolean search(T value) {
    return searchRec(root, value);
  }

  /**
   * Rekurencyjna metoda pomocnicza do wyszukiwania.
   */
  private boolean searchRec(Node<T> node, T value) {
    if (node == null)
      return false;
    int cmp = value.compareTo(node.value);
    if (cmp == 0)
      return true;
    return cmp < 0 ? searchRec(node.left, value) : searchRec(node.right, value);
  }

  /**
   * Usuwa wartość z drzewa.
   * @param value wartość do usunięcia
   * @return true jeśli usunięto, false jeśli nie znaleziono
   */
  public synchronized boolean delete(T value) {
    int before = size();
    root = deleteRec(root, value);
    return size() < before;
  }

  /**
   * Rekurencyjna metoda pomocnicza do usuwania.
   */
  private Node<T> deleteRec(Node<T> node, T value) {
    if (node == null)
      return null;
    int cmp = value.compareTo(node.value);
    if (cmp < 0)
      node.left = deleteRec(node.left, value);
    else if (cmp > 0)
      node.right = deleteRec(node.right, value);
    else {
      if (node.left == null)
        return node.right;
      if (node.right == null)
        return node.left;
      Node<T> min = node.right;
      while (min.left != null)
        min = min.left;
      node.value = min.value;
      node.right = deleteRec(node.right, min.value);
    }
    return node;
  }

  /**
   * Zwraca tekstową reprezentację drzewa (rysunek).
   * @return rysunek drzewa jako String
   */
  public synchronized String draw() {
    if (root == null)
      return null;
    StringBuilder sb = new StringBuilder();
    drawRec(root, sb, 0);
    return sb.toString();
  }

  /**
   * Rekurencyjna metoda pomocnicza do rysowania drzewa.
   */
  private void drawRec(Node<T> node, StringBuilder sb, int depth) {
    if (node == null)
      return;
    drawRec(node.right, sb, depth + 1);
    for (int i = 0; i < depth; i++)
      sb.append(" ".repeat(NODE_WIDTH));
    String valueStr = String.valueOf(node.value);
    if (valueStr.length() < NODE_WIDTH)
      valueStr = String.format("%-" + NODE_WIDTH + "s", valueStr);
    sb.append(valueStr).append("\n");
    drawRec(node.left, sb, depth + 1);
  }

  /**
   * Zwraca liczbę elementów w drzewie.
   * @return liczba węzłów
   */
  public int size() {
    return sizeRec(root);
  }

  /**
   * Rekurencyjna metoda pomocnicza do liczenia węzłów.
   */
  private int sizeRec(Node<T> node) {
    if (node == null)
      return 0;
    return 1 + sizeRec(node.left) + sizeRec(node.right);
  }

  /**
   * Sprawdza, czy drzewo jest puste.
   * @return true jeśli puste, false w przeciwnym razie
   */
  public boolean isEmpty() {
    return root == null;
  }
}