db = db.getSiblingDB("library");

print("Wstawianie autorów");

var sapkowski = db.authors.insertOne({
  name: { first: "Andrzej", last: "Sapkowski" },
  country: "PL",
  birth: new Date("Jun 21, 1948"),
  death: null,
}).insertedId;

var lem = db.authors.insertOne({
  name: { first: "Stanisław", last: "Lem" },
  country: "PL",
  birth: new Date("Sep 12, 1921"),
  death: new Date("Mar 27, 2006"),
}).insertedId;

var tolkien = db.authors.insertOne({
  name: { first: "J.R.R", last: "Tolkien" },
  country: "UK",
  birth: new Date("Jan 3, 1892"),
  death: new Date("Sep 2, 1973"),
}).insertedId;

var king = db.authors.insertOne({
  name: { first: "Stephen", last: "King" },
  country: "USA",
  birth: new Date("Sep 21, 1947"),
  death: null,
}).insertedId;

print("Wstawianie książek");

var booksData = [
  {
    title: "Ostatnie życzenie",
    isbn: "978-83-7578-063-5",
    publication_year: 1993,
    language: "Polski",
    author: sapkowski,
    publisher: { name: "SuperNowa", country: "PL" },
  },
  {
    title: "Miecz przeznaczenia",
    isbn: "978-83-7578-064-2",
    publication_year: 1992,
    language: "Polski",
    author: sapkowski,
    publisher: { name: "SuperNowa", country: "PL" },
  },
  {
    title: "Krew elfów",
    isbn: "978-83-7578-065-9",
    publication_year: 1994,
    language: "Polski",
    author: sapkowski,
    publisher: { name: "SuperNowa", country: "PL" },
  },
  {
    title: "Solaris",
    isbn: "978-83-08-04905-4",
    publication_year: 1961,
    language: "Polski",
    author: lem,
    publisher: { name: "Wydawnictwo MON", country: "PL" },
  },
  {
    title: "Niezwyciężony",
    isbn: "978-83-08-04906-1",
    publication_year: 1964,
    language: "Polski",
    author: lem,
    publisher: { name: "Wydawnictwo MON", country: "PL" },
  },
  {
    title: "Cyberiada",
    isbn: "978-83-08-04907-8",
    publication_year: 1965,
    language: "Polski",
    author: lem,
    publisher: { name: "Wydawnictwo MON", country: "PL" },
  },
  {
    title: "The Hobbit",
    isbn: "978-0-261-10295-6",
    publication_year: 1937,
    language: "English",
    author: tolkien,
    publisher: { name: "George Allen & Unwin", country: "UK" },
  },
  {
    title: "The Fellowship of the Ring",
    isbn: "978-0-261-10235-4",
    publication_year: 1954,
    language: "English",
    author: tolkien,
    publisher: { name: "George Allen & Unwin", country: "UK" },
  },
  {
    title: "The Two Towers",
    isbn: "978-0-261-10236-1",
    publication_year: 1954,
    language: "English",
    author: tolkien,
    publisher: { name: "George Allen & Unwin", country: "UK" },
  },
  {
    title: "The Shining",
    isbn: "978-0-385-12167-5",
    publication_year: 1977,
    language: "English",
    author: king,
    publisher: { name: "Doubleday", country: "USA" },
  },
  {
    title: "It",
    isbn: "978-0-670-81302-5",
    publication_year: 1986,
    language: "English",
    author: king,
    publisher: { name: "Viking", country: "USA" },
  },
  {
    title: "The Green Mile",
    isbn: "978-0-452-27890-5",
    publication_year: 1996,
    language: "English",
    author: king,
    publisher: { name: "Signet", country: "USA" },
  },
];

db.books.insertMany(booksData);

print("Generowanie recenzji");

var reviewers = [
  { name: "Jan Kowalski", email: "jan@testmail.com" },
  { name: "Anna Nowak", email: "anna@testmail.com" },
  { name: "Tomasz Kot", email: "tomek@testmail.com" },
  { name: "Maria Wiśniewska", email: "maria@testmail.com" },
  { name: "Piotr Zieliński", email: "piotr@testmail.com" }
];

var reviewTexts = {
  1: "Tragedia!",
  2: "Nie polecam.",
  3: "Może być...",
  4: "Polecam!",
  5: "Rewelacyjna książka!",
};

var allBooks = db.books.find().toArray();

allBooks.forEach(book => {
  let shuffled = reviewers.slice().sort(() => Math.random() - 0.5);
  let selectedReviewers = shuffled.slice(0, 3);
  
  let rating1 = Math.floor(Math.random() * 5) + 1;
  let rating2 = Math.floor(Math.random() * 5) + 1;
  let rating3 = Math.floor(Math.random() * 5) + 1;
  
  db.reviews.insertMany([
    {
      book_id: book._id,
      reviewer: selectedReviewers[0],
      rating: rating1,
      text: reviewTexts[rating1],
    },
    {
      book_id: book._id,
      reviewer: selectedReviewers[1],
      rating: rating2,
      text: reviewTexts[rating2],
    },
    {
      book_id: book._id,
      reviewer: selectedReviewers[2],
      rating: rating3,
      text: reviewTexts[rating3],
    },
  ]);
});

print("Dodanie nagród i gatunków");

db.authors.updateMany({}, { $set: { awards: [] } });

db.authors.updateOne(
  { "name.last": "Sapkowski" },
  { $push: { awards: { name: "Paszport Polityki", year: 1997 } } }
);

db.authors.updateOne(
  { "name.last": "Tolkien" },
  { $push: { awards: { name: "International Fantasy Award", year: 1957 } } }
);

db.authors.updateOne(
  { "name.last": "King" },
  { $push: { awards: { name: "Bram Stoker Award", year: 1987 } } }
);

db.books.updateMany({}, { $set: { genres: ["Fantasy"] } });
db.books.updateMany({ author: lem }, { $set: { genres: ["Sci-Fi"] } });
db.books.updateMany(
  { author: king },
  { $set: { genres: ["Horror", "Thriller"] } }
);

print("Dodano 4 autorów, 12 książek, 36 recenzji");
