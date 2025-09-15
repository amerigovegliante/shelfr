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
        Book(const Book&);

        virtual void accept(MediaVisitorInterface&) override;
        virtual ~Book() override = default;
        Book* clone() const override;

        int getPages() const;
        QString getISBN() const;
        QString getPublisher() const;
        QString getAuthor() const;

        void setAuthor(const QString&);
        void setPages(int);
        void setISBN(const QString&);
        void setPublisher(const QString&);
};

#endif