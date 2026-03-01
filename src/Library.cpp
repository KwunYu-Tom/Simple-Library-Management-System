#include "Library.h"

// Constructor
Library::Library(int initialCapacity): userCount{0},capacity{initialCapacity},totalRevenue{0}
{
    users = new User*[capacity];
    for (int i =0 ; i<capacity;i++){
        users[i]=nullptr ;
    }
}

// Destructor
Library::~Library()
{
    for (int i = 0; i < userCount; i++)
    {
        delete users[i]; 
    }
    delete[] users;
}

void Library::addUser(int id, const string &name)
{
    if (userCount>=capacity){
        capacity = capacity* 2;
        User **TempUsers = new User*[capacity];
        for (int i = 0; i < userCount; i++)
        {
            TempUsers[i] = users[i]; // Copy 
        }
        for (int i = userCount; i < capacity; i++)
        {
            TempUsers[i] = nullptr; // Init
        }
        delete[] users; 
        users = TempUsers; 
    }
    users[userCount++] = new User(id,name);
    totalRevenue = totalRevenue +5 ;
}

void Library::upgradeUserSlots(int userId, int additionalSlots)
{
    User* Target = getUserById(userId);
    if (Target == nullptr){
        cout<<"User ID "<< userId <<"not found.";
        return;
    }
    Target->updateMaxBooks(additionalSlots);
    totalRevenue = totalRevenue +additionalSlots;
    cout << "User ID "<< userId << " upgraded by "<< additionalSlots<< " slots." << endl;
}

double Library::getTotalRevenue() const
{
    return totalRevenue ;
}

void Library::displayUsers() const
{
    //User ID: 1, Name: Bob, Borrowed Books: 0, Max Books: 5
    for (int i =0; i< userCount;i++){
        cout << "User ID: " << users[i]->getUserId() << ", Name: " << users[i]->getUserName() << 
        ", Borrowed Books: " << users[i]->getNumBooksBorrowed() << ", Max Books: " << users[i]->getMaxBooks() << endl;
    }
}

User *Library::getUserById(int userId) const
{
    for (int i =0 ;i < userCount;i++){
        if (users[i]->getUserId() == userId){
            return users[i] ;
        }
    }
    return nullptr;
}

void Library::addNewBook(Book *book)
{
    if (totalRevenue <= 2){
        cout << "Insufficient funds to add the book " << book->getTitle() <<"." << endl;
        return;
    }
    Book* Target = libraryInventory.searchList(book->getId());
    libraryInventory.insertBook(book);
    totalRevenue = totalRevenue -2 ;
    cout<<"Book '"<<book->getTitle()<<"' added to the library." << endl;
}

void Library::removeBook(int bookId)
{
    Book*Target = libraryInventory.searchList(bookId);
    if (Target == nullptr)
    {
        cout << "Book with ID " << bookId << " not found in the library." << endl;
        return;
    }
    for (int i =0; i < Target->getInventoryCount();i++){
        libraryInventory.removeBook(Target);
        totalRevenue = totalRevenue + 1;
    }
}

void Library::displayBooks() const
{
    this->libraryInventory.displayBooks();
}

BookList &Library::getLibraryInventory()
{
    return libraryInventory;
}