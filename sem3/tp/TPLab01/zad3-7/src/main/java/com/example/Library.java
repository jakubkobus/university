package com.example;

import java.util.ArrayList;

public class Library {
  private ArrayList<Book> books;

  public Library() {
    this.books = new ArrayList<>();
  }

  public void addBook(Book book) {
    books.add(book);
  }

  public ArrayList<Book> getBooks() {
    return books;
  }
}
