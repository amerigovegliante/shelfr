#include "../../headers/core/book.h"

Book::Book(const QString& t, const QString& d, const QString& g, const QString& ip, int y, int p, const QString& in, const QString& ps, const QString& auth):
    Media::Media(t,d,g,ip,y),
    pages((p != NULL) ? p : 0),
    isbn((!(in.isNull() && in.isEmpty()) ? in : "Default-ISBN")),
    publisher(!(ps.isNull() && ps.isEmpty()) ? ps : "Default-Publisher"),
    author(!(auth.isNull() && auth.isEmpty()) ? auth : "Default Book Author")
{}

int Book::getPages() const { return Book::pages; }

QString Book::getISBN() const { return Book::isbn; }

QString Book::getPublisher() const { return Book::publisher; }

void Book::setPages(int new_pages) { pages = new_pages; }

void Book::setISBN(const QString& new_isbn) { isbn = new_isbn; }

void Book::setPublisher(const QString& new_publisher) { publisher = new_publisher; }
