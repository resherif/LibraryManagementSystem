# LibraryManagementSystem

A simple C++ console application to manage books and users in a library using Object-Oriented Programming and the Strategy Design Pattern.  
The project supports borrowing, returning books, and tracking book availability states.

## Features

- Add and remove books
- Add users
- Borrow and return books
- Automatically track book state:
  - `Available` (copies ≥ 3)
  - `UpcomingSoon` (1–2 copies)
  - `OutOfStock` (0 copies)
- Save books and user data to files on exit

## Technologies

- C++
- STL (Vectors, Maps)
- OOP (Classes, Inheritance, Polymorphism)
- Design Patterns: Strategy Pattern
- Singleton Pattern (for LibraryManager)
- File I/O using `<fstream>`

## How to Run

1. Compile the program using a C++ compiler:
   ```bash
   g++ -std=c++11 main.cpp -o library
   ./library
   libraryManagementSystem/
   │
   ├── main.cpp              # Entry point (if separate)
   ├── Book.h / Book.cpp     # Book class
   ├── User.h / User.cpp     # User class
   ├── LibraryManager.h      # Singleton manager
   ├── Strategy.h            # Design pattern interfaces
   ├── books.txt             # Saved books (generated after use)
   ├── users.txt             # Saved users and borrowed books
   └── README.md             # This file
   ```

Example Output:
User "Reham" added.
Book "C++ Primer" added.
Reham borrowed "C++ Primer"
Book: C++ Primer
State: UpcomingSoon
Available Copies: 2

Author
Reham Sherif

GitHub Profile https://github.com/resherif

LinkedIn https://www.linkedin.com/in/reham-sherif-a6b631216developer/

License
This project is open-source and free to use for educational purposes.
# LibraryManagementSystem
