#include<iostream>
#include "LibraryManagementSystem.h"
using namespace std;
void showMenu()
{
    cout << "\n====== Library Management System ======\n";
    cout << "1. Add Book\n";
    cout << "2. Add User\n";
    cout << "3. Borrow Book\n";
    cout << "4. Return Book\n";
    cout << "5. Show Book Status\n";
    cout << "6. Show Borrowed Books\n";
    cout << "7. Save to File\n";
    cout << "0. Exit\n";
    cout << "Choose an option: ";
}

int main()
{
    libraryManager *lib = libraryManager::getInstance();

    int choice;
    string title, type, author, user;
    int copies;

    while (true)
    {
        showMenu();
        cin >> choice;
        cin.ignore(); // لتفادي مشاكل getline

        switch (choice)
        {
        case 1:
            cout << "Enter Book Title: ";
            getline(cin, title);
            cout << "Enter Book Type: ";
            getline(cin, type);
            cout << "Enter Author Name: ";
            getline(cin, author);
            cout << "Enter Number of Copies: ";
            cin >> copies;
            lib->AddBook(title, type, author, copies);
            break;

        case 2:
            cout << "Enter Username: ";
            getline(cin, user);
            lib->AddUser(user);
            break;

        case 3:
            cout << "Enter Username: ";
            getline(cin, user);
            cout << "Enter Book Title: ";
            getline(cin, title);
            lib->BorrowBook(user, title);
            break;

        case 4:
            cout << "Enter Username: ";
            getline(cin, user);
            cout << "Enter Book Title: ";
            getline(cin, title);
            lib->ReturnBook(user, title);
            break;

        case 5:
            cout << "Enter Book Title: ";
            getline(cin, title);
            lib->ShowBookStatus(title);
            break;

        case 6:
            cout << "Enter Username: ";
            getline(cin, user);
            if (lib->HasUser(user))
                lib->ShowUserBorrowedBooks(user);
            else
                cout << "User not found.\n";
            break;

        case 7:
            lib->saveToFile(); // يفترض نقلها من كلاس Book إلى libraryManager
            break;

        case 0:
            cout << "Exiting...\n";
            return 0;

        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}
