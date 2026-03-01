#include "Book.h"

Book::Book() : bookId {0},title{""},author{""},inventoryCount{1},rating{0},ratingCount{0}
{
}

Book::Book(int id, const string &t, const string &a, int count, double rat, int ratCount)
:bookId {id},title{t},author{a},inventoryCount{count},rating{rat},ratingCount{ratCount}{
}

int Book::getId() const
{
    return bookId ;
}

int Book::getInventoryCount() const
{
    return inventoryCount ;
}

void Book::changeInventoryCount(int c)
{
    inventoryCount = inventoryCount + c ;
}

string Book::getTitle() const
{
    return title ;
}

string Book::getAuthor() const
{   
    return author ;
}

double Book::getRating() const
{
    return rating ;
}

void Book::addRating(double newRating)
{
    if( (newRating > 5) || (newRating < 0) ){
        cout << "Rating must be between 0 and 5." << endl;
        return;
    }
    double oldRatingTotal = rating * ratingCount;
    rating = (oldRatingTotal + newRating) / (++ratingCount);

}