#ifndef BOOK_H
#define BOOK_H

#include "media.h"

class Book : public Media
{
    private:
        int pages;
        QString isbn;
        QString publisher;
        QString author;
    public:    
        Book(const QString&, const QString&, const QString&, const QString&, int, int, const QString&, const QString&, const QString&);

        virtual ~Book() override = default;

        int getPages() const;
        QString getISBN() const;
        QString getPublisher() const;
        QString getAuthor() const;

        void setPages(int);
        void setISBN(const QString&);
        void setPublisher(const QString&);
        void setAuthor(const QString&);
};

#endif