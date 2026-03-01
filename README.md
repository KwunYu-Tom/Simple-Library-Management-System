# Simple Library Management System (C++)

A robust, command-line based Library Management System developed as part of my Object-Oriented Programming (COMP2012) coursework. This project demonstrates core C++ concepts, including dynamic memory management, linked lists, and class composition.

## 🚀 Key Features
* **Book Management:** Track inventory, titles, authors, and dynamic ratings.
* **User System:** Manage users with borrowing limits and the ability to upgrade slots.
* **Data Structures:** Custom Linked List implementation for storing and searching books.
* **Revenue Tracking:** Simulated library economy where adding books costs money and user upgrades generate revenue.
* **Rating System:** Users can provide ratings (0-5) which are averaged across all ratings for each book.

## 🛠️ Technical Concepts Used
* **OOP Principles:** Encapsulation, abstraction, and class relationships (Composition).
* **Memory Management:** Manual allocation/deallocation using `new` and `delete` to prevent memory leaks.
* **Constructors/Destructors:** Use of deep copy constructors and proper cleanup in destructors.
* **Const Correctness:** Strategic use of `const` member functions to ensure data integrity.

## 💻 How to Build and Run

### Prerequisites
* A C++ compiler (GCC/G++ recommended)

### Compilation
To compile all modules together, run:
```bash
g++ main.cpp Book.cpp BookList.cpp User.cpp Library.cpp -o library_system
