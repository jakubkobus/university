db = db.getSiblingDB('library');

print("1. Wszystkie książki napisane po polsku w gatunku \"Fantasy\"");
db.books.find({ language: "Polski", genres: "Fantasy" }, { title: 1, author: 1 }).forEach(printjson);

print("\n\n2. Książki ze średnią oceną >= 4");
db.books.aggregate([
  {
    $lookup: { from: "reviews", localField: "_id", foreignField: "book_id", as: "book_reviews" }
  },
  { $unwind: "$book_reviews" },
  {
    $group: {
      _id: "$_id",
      title: { $first: "$title" },
      avgRating: { $avg: "$book_reviews.rating" }
    }
  },
  { $match: { avgRating: { $gte: 4 } } }
]).forEach(printjson);

print("\n\n3. Książki Andrzeja Sapkowskiego");
db.books.aggregate([
  {
    $lookup: { from: "authors", localField: "author", foreignField: "_id", as: "author_info" }
  },
  { $match: { "author_info.name.last": "Sapkowski" } },
  { $project: { title: 1, "author_info.name.last": 1, _id: 0 } }
]).forEach(printjson);

print("\n\n4. Książki polskich autorów ze średnią oceną");
db.books.aggregate([
  {
    $lookup: { from: "authors", localField: "author", foreignField: "_id", as: "auth" }
  },
  { $match: { "auth.country": "PL" } },
  {
    $lookup: { from: "reviews", localField: "_id", foreignField: "book_id", as: "revs" }
  },
  {
      $project: {
          title: 1,
          authorName: { $arrayElemAt: ["$auth.name.last", 0] },
          avgRating: { $avg: "$revs.rating" }
      }
  }
]).forEach(printjson);

print("\n\n5. Autorzy i liczba książek");
db.authors.aggregate([
  {
    $lookup: { from: "books", localField: "_id", foreignField: "author", as: "written_books" }
  },
  {
    $project: {
      _id: 0,
      lastname: "$name.last",
      bookCount: { $size: "$written_books" }
    }
  }
]).forEach(printjson);

print("\n\n6. Średnia ocena wszystkich książek autora");
db.authors.aggregate([
  {
    $lookup: { from: "books", localField: "_id", foreignField: "author", as: "books" }
  },
  { $unwind: "$books" },
  {
    $lookup: { from: "reviews", localField: "books._id", foreignField: "book_id", as: "reviews" }
  },
  { $unwind: "$reviews" },
  {
    $group: {
      _id: "$_id",
      authorName: { $first: "$name.last" },
      avgRating: { $avg: "$reviews.rating" }
    }
  }
]).forEach(printjson);

print("\n\n7. Autorzy bez nagród");
db.authors.aggregate([
  {
    $match: {
      $or: [ { awards: { $exists: false } }, { awards: { $size: 0 } } ]
    }
  },
  { $project: { "name.last": 1, awards: 1 } }
]).forEach(printjson);

print("\n\n8. Liczba książek w gatunkach");
db.books.aggregate([
  { $unwind: "$genres" },
  {
    $group: { _id: "$genres", count: { $sum: 1 } }
  }
]).forEach(printjson);

print("\n\n9. Najaktywniejszy recenzent");
db.reviews.aggregate([
  {
    $group: {
      _id: "$reviewer.email",
      name: { $first: "$reviewer.name" },
      reviewCount: { $sum: 1 }
    }
  },
  { $sort: { reviewCount: -1 } },
  { $limit: 1 }
]).forEach(printjson);

print("\n\n10. Średnia ocena wg języka");
db.books.aggregate([
  {
    $lookup: { from: "reviews", localField: "_id", foreignField: "book_id", as: "reviews" }
  },
  { $unwind: "$reviews" },
  {
    $group: {
      _id: "$language",
      avgRating: { $avg: "$reviews.rating" }
    }
  }
]).forEach(printjson);