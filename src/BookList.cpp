#include "BookList.h"
#include "Book.h"

BookList::BookList() : head(nullptr)        //done
{
}

BookList::BookList(const BookList &other): head(nullptr)       //
{
    // can use insert method?
    Node* current = other.head;
    while (current != nullptr){
        insertBook(current->data);
        current = current->next;
    }
}

BookList::~BookList()
{
    
    Node * current = head;
    while(current != nullptr){
        Node * next = current->next;
        delete current;
        current = next ;
    }
}

bool BookList::isEmpty() const
{
    return head == nullptr ; // header = nullptr means true, return true. if is empty -> true
}

void BookList::insertBook(Book *book)
{
    // need check is exist? can use search list
    Book * TargetBook = searchList(book->getId());
    if (TargetBook != nullptr){     // book exist, add copies
        TargetBook->changeInventoryCount(1);
        return;

    }
    //adding book into linked list.

    Node* node = new Node{book};        // create new node to add
    // data(book) assigned using build in constructor.
    node->next = nullptr ; // playsafe! should be neglected.
    if (isEmpty()){ // empty linked list.
        head = node; // added end.
        return;
    }
    //add at the end.
    Node* current = head;
    while (current != nullptr){
        if (current->next == nullptr) { // found the last node
            current->next = node;
            break; // escape the loop.

        } 
        current = current->next;    // move next ptr
    }
}

void BookList::removeBook(Book *book)
{
    if (isEmpty()){     // empty booklist.
        cout << "The book list is empty." << endl;
        return;
    }
    Book * TargetBook = searchList(book->getId());
    if (TargetBook == nullptr){
        cout << "Book with ID "<< book->getId() << " not found." << endl;
        return;
    }
    // book exist
    if (TargetBook->getInventoryCount() > 1){  // don't need to remove in the list
        TargetBook->changeInventoryCount(-1);
        return;
    }
    // need remove in the list.
    Node* curret = head ;
    Node* previous = nullptr ;
    while (curret!= nullptr){
        if (curret->data->getId() == TargetBook->getId()){ //found book, remove book form the list.
            if (curret == head){    // remove first book. need change head ptr
                head = curret->next;
                delete curret ;
                return;
            }
            else{       // remove last or in between.
                previous->next = curret->next ;
                delete curret ;
                return;
            }
            
        }
        previous = curret;
        curret = curret->next ;
    }


}

void BookList::displayBooks() const     // 2,6,7,8 test case have format
{
    // need check format and isempty?
    cout << "Library Book Details:" << endl;
    if (isEmpty()){
        cout << "The book list is empty." << endl;
        return ;        //stop program
    }
    // display all book details.
    /*
    Library Book Details:
    ID: 1 - Title: The Great Gatsby - Author: F. Scott Fitzgerald - Rating: 0
    ID: 2 - Title: 1984 - Author: George Orwell - Rating: 0
    ID: 3 - Title: To Kill a Mockingbird - Author: Harper Lee - Rating: 0
    ID: 4 - Title: Great Expectations - Author: Charles Dickens - Rating: 0
    */
    Node* current = head ;
    while(current != nullptr){
        cout<< "ID: " << current->data->getId() << " - Title: " << current->data->getTitle()<<
        " - Author: " << current->data->getAuthor() <<" - Rating: " << current->data->getRating() << endl;
        current = current->next;
    }
    //output done!
}

void BookList::sortBooks(SortCriteria criteria)
{
    
    // If the list is empty or has only one book, it's already sorted
    if (isEmpty() || head->next == nullptr) {
        return;
    }

    for (Node* i = head; i->next != nullptr; i = i->next) {
        Node* minNode = i;

        for (Node* j = i->next; j != nullptr; j = j->next) {
            bool shouldSwap = false;

            if (criteria == BY_RATING) {
                // Ascending order: smallest rating first
                if (j->data->getRating() < minNode->data->getRating()) {
                    shouldSwap = true;
                }
            } 
            else if (criteria == BY_TITLE) {
                // Alphabetical order: title starting with numbers come before A-Z
                // C++ string comparison ( < ) naturally handles "123" < "ABC" < "abc"
                if (j->data->getTitle() < minNode->data->getTitle()) {
                    shouldSwap = true;
                }
            }

            if (shouldSwap) {
                minNode = j;
            }
        }

        // Swap the Book pointers, not the nodes themselves (easier for linked lists)
        if (minNode != i) {
            Book* temp = i->data;
            i->data = minNode->data;
            minNode->data = temp;
        }
    
    }


}

Book *BookList::searchList(int bookId) const        // return nullptr if not found. loop the list
{       // data is Book*
    Node * current = head ;
    while (current != nullptr){
        if (current->data->getId() == bookId){
            return current->data ;
        }
        current = current->next;
    }
    return nullptr ;
}

int BookList::countBooks() const
{
    Node* current = head;
    int count = 0;
    while (current != nullptr){
        count = count + current->data->getInventoryCount();
        current = current->next;
    }
    return count ;
}

void BookList::rateBook(int bookId, double newRating)
{
    // need check bookId exist? use searchbook.
    Book* TargetBook = searchList(bookId);
    if (TargetBook == nullptr) {        // Book not found.
        cout << "Book with ID "<< bookId << " not found." << endl;
        return;
    }
    
    TargetBook->addRating(newRating);       //ratebook using book method
    cout << "Rating updated for Book "<< TargetBook->getId() <<". New rating: " <<TargetBook->getRating() << endl;
    // output message;
}
Book *BookList::getBookWithMaxRating() const
{
    // check is empty first.
    if (isEmpty()){     // empty booklist.
        cout << "The book list is empty." << endl;
        return nullptr ;
    }
    //booklist not empty.
    // data is book*
    Node* current = head;
    Book* MaxRatingBook = current->data;
    while (current != nullptr){
        if ((current->data->getRating()) > (MaxRatingBook->getRating())){      // new biggest rating book found.
        MaxRatingBook = current->data ; //replace a new max rating book.
        }
        current = current->next ;
    }
    return MaxRatingBook ;
}

Book *BookList::getBookWithMinRating() const
{
    // check is empty first.
    if (isEmpty()){     // empty booklist.
        cout << "The book list is empty." << endl;
        return nullptr ;
    }
    //booklist not empty.
    // data is book*
    Node* current = head;
    Book* MinRatingBook = current->data;
    while (current != nullptr){
        if ((current->data->getRating()) < (MinRatingBook->getRating())){      // new biggest rating book found.
        MinRatingBook = current->data ; //replace a new max rating book.
        }
        current = current->next ;
    }
    return MinRatingBook ;
}

void BookList::reverseBooksByRating()
{
    sortBooks(BY_RATING);
}