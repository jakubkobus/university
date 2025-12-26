package com.example;

import static org.junit.jupiter.api.Assertions.assertTrue;
import org.junit.jupiter.api.Test;

class AppTest {
  @Test
  void testLibrary() {
    Library library = new Library();

    Book book1 = new Book("1984", "George Orwell");
    Book book2 = new Book("Pan Tadeusz", "Adam Mickiewicz");

    library.addBook(book1);
    library.addBook(book2);

    assertTrue(library.getBooks().contains(book1));
    assertTrue(library.getBooks().contains(book2));
  }
}