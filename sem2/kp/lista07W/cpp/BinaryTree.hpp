#pragma once
#include <string>
#include <memory>
#include <sstream>

/**
 * @brief Klasa szablonowa reprezentująca drzewo binarne dowolnego typu porównywalnego.
 * @tparam T Typ przechowywanych danych.
 */
template <typename T>
class BinaryTree {
  /**
   * @brief Struktura reprezentująca węzeł drzewa.
   */
  struct Node
  {
    T value;
    std::unique_ptr<Node> left, right;
    Node(const T &v);
  };

  std::unique_ptr<Node> root;
  const int NODE_WIDTH = 8;

  /**
   * @brief Rekurencyjna metoda pomocnicza do wstawiania.
   */
  Node *insertRec(Node *node, const T &value);

  /**
   * @brief Rekurencyjna metoda pomocnicza do wyszukiwania.
   */
  bool searchRec(Node *node, const T &value) const;

  /**
   * @brief Rekurencyjna metoda pomocnicza do usuwania.
   */
  Node *deleteRec(Node *node, const T &value);

  /**
   * @brief Rekurencyjna metoda pomocnicza do rysowania drzewa.
   */
  void drawRec(const Node *node, std::ostringstream &oss, int depth) const;

  /**
   * @brief Rekurencyjna metoda pomocnicza do liczenia węzłów.
   */
  int sizeRec(const Node *node) const;

public:
  /**
   * @brief Konstruktor domyślny.
   */
  BinaryTree();

  /**
   * @brief Wstawia nową wartość do drzewa.
   * @param value Wartość do wstawienia.
   */
  void insert(const T &value);

  /**
   * @brief Sprawdza, czy wartość istnieje w drzewie.
   * @param value Szukana wartość.
   * @return true jeśli istnieje, false w przeciwnym razie.
   */
  bool search(const T &value) const;

  /**
   * @brief Usuwa wartość z drzewa.
   * @param value Wartość do usunięcia.
   * @return true jeśli usunięto, false jeśli nie znaleziono.
   */
  bool remove(const T &value);

  /**
   * @brief Zwraca tekstową reprezentację drzewa (rysunek).
   * @return Rysunek drzewa jako std::string.
   */
  std::string draw() const;

  /**
   * @brief Zwraca liczbę elementów w drzewie.
   * @return Liczba węzłów.
   */
  int size() const;

  /**
   * @brief Sprawdza, czy drzewo jest puste.
   * @return true jeśli puste, false w przeciwnym razie.
   */
  bool isEmpty() const;
};