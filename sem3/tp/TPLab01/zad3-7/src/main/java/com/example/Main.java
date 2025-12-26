package com.example;

public class Main {
  public static void main(String[] args) {
    Library library = new Library();

    Book book1 = new Book("1984", "George Orwell");
    Book book2 = new Book("Pan Tadeusz", "Adam Mickiewicz");
    Book book3 = new Book("Quo vadis", "Henryk Sienkiewicz");
    Book book4 = new Book("Potop", "Henryk Sienkiewicz");
    Book book5 = new Book("W pustyni i w puszczy", "Henryk Sienkiewicz");

    library.addBook(book1);
    library.addBook(book2);
    library.addBook(book3);
    library.addBook(book4);
    library.addBook(book5);

    for (Book book : library.getBooks()) {
      System.out.println(book.toString());
    }
  }
}
