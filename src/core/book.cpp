#include "../../headers/core/book.h"

Book::Book(const QString& title, const QString& description, const QString& genre, const QString& imagepath, int year, int pages, const QString& isbn, const QString& publisher, const QString& author):
    Media::Media(title,description,genre,imagepath,year),
    pages((pages >= 0) ? pages : 0),
    isbn((!(isbn.isNull() && isbn.isEmpty()) ? isbn : "Default-ISBN")),
    publisher(!(publisher.isNull() && publisher.isEmpty()) ? publisher : "Default-Publisher"),
    author(!(author.isNull() && author.isEmpty()) ? author : "Default Book Author")
{}

Book::Book(const Book& book):
    Media(book),
    pages(book.pages),
    isbn(book.isbn),
    publisher(book.publisher),
    author(book.author)
{}

QString Book::getType() const { return "Book";}

void Book::accept(MediaVisitorInterface& visitor)
{
    visitor.visit(*this);
}

Book* Book::clone() const { return new Book(*this); }

int Book::getPages() const { return Book::pages; }

QString Book::getAuthor() const { return author;}

QString Book::getISBN() const { return Book::isbn; }

QString Book::getPublisher() const { return Book::publisher; }

void Book::setPages(int new_pages) { pages = new_pages; }

void Book::setISBN(const QString& new_isbn) { isbn = new_isbn; }

void Book::setPublisher(const QString& new_publisher) { publisher = new_publisher; }

void Book::setAuthor(const QString& new_author) { author = new_author;}
