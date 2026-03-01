#include "User.h"
#include "Book.h"

User::User():userId{0}, name {""}, numBooksBorrowed{0},maxBooks{5}
{
    booksBorrowed = new Book* [maxBooks];
    for (int i =0; i < maxBooks;i++){
        booksBorrowed[i] = nullptr;
    }
}

User::User(int id, const string &n, int borrow, int max): userId{id}, name{n}, numBooksBorrowed{borrow}, maxBooks{max}
{
    booksBorrowed = new Book* [maxBooks];
    for (int i =0; i < maxBooks;i++){
        booksBorrowed[i] = nullptr;
    }
}

User::~User()
{
    delete [] booksBorrowed;
}

void User::borrowBook(Book *book)
{
    // need check is inventory >0
    if (numBooksBorrowed >= maxBooks){  // blocked, boorowed too manybooks
        cout << "You cannot borrow more books." << endl;
        return ;

    }
    if (!(book->getInventoryCount() >0)){
        cout << "This book is currently unavailable." << endl;
        return ;
    }

    // can borrow case.
    booksBorrowed[numBooksBorrowed++] = book ;
    book->changeInventoryCount(-1);
    cout  << "Successfully borrowed: " << book->getTitle() << endl;
}

void User::returnBook(Book *book)
{
    for (int i = 0; i < numBooksBorrowed;i++){
        if (booksBorrowed[i]->getId() == book->getId()){    // books found.
            for (int j = i; j < numBooksBorrowed-1; j++){
                booksBorrowed[j] = booksBorrowed[j+1]; // move books
            }
            booksBorrowed[--numBooksBorrowed] = nullptr ;
            book->changeInventoryCount(1); //return book.
            cout << "Successfully returned: " << book->getTitle() << endl;
            return;
        }
    }
    // loop end, not found.
    cout << "This book was not borrowed by you." << endl;

}

int User::getNumBooksBorrowed() const
{   
    return numBooksBorrowed ;
}

int User::getUserId() const
{   
    return userId;
}

string User::getUserName() const
{
    return name ;
}

int User::getMaxBooks() const
{
    return maxBooks;
}

void User::viewBorrowedBooks() const
{
    if (numBooksBorrowed ==0){  // didn't borrow any books
        cout << name <<" has not borrowed any books." << endl;
        return;
    }
    cout << name << "'s Borrowed Books:" << endl;
    // Book * UniqueBooks[maxBooks] ;
    // int UniqueBooksCount = 0;
    // for (int i =0; i < numBooksBorrowed;i++){
    //     UniqueBooks[i] = nullptr;
    // }
    // UniqueBooks[0] = booksBorrowed[0] ;
    // for (int i =1; i < numBooksBorrowed;i++){
    //     if 
       
    // }
    Book * BooksDisplayed[maxBooks] ;
    for (int i=0;i<maxBooks;i++){
        BooksDisplayed[i] = nullptr ;
    }
    int DisplayedBooksCount = 0;
    for (int i =0; i<numBooksBorrowed;i++){
        bool isDisplayed = false;
        for (int j =0;j<DisplayedBooksCount;j++){   // check is displayed?
            if (BooksDisplayed[j]->getId() == booksBorrowed[i]->getId()){       // displayed
                isDisplayed = true;
                break;
            }
        }
        if (!isDisplayed){
            BooksDisplayed[DisplayedBooksCount++] =booksBorrowed[i];
        }
    }
    //display message
    for (int i =0; i <DisplayedBooksCount;i++){
        int count = 0;
        for (int j =0; j<numBooksBorrowed;j++){
            if (BooksDisplayed[i]->getTitle() == booksBorrowed[j]->getTitle()){
                count++ ;
            }
        }
        cout << BooksDisplayed[i]->getTitle() << " (x" << count <<")" <<endl; 
    }


    /*
        The Great Gatsby (x1)
        1984 (x1)
        */
}

void User::giveRating(BookList &list, int bookId, double newRating)
{
    if (numBooksBorrowed >= maxBooks){  //check is blocked
        cout << "User is blocked and cannot rate books." << endl;
        return;
    }
    list.rateBook(bookId,newRating);
}

void User::updateMaxBooks(int additionalSlots)
{
    if (additionalSlots <= 0){
        cout << "Invalid number of additional slots." << endl;
        return;
    }
    maxBooks = maxBooks + additionalSlots ;
    cout << "Max books updated to: " << maxBooks << endl;
}