#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <fstream>
using namespace std;
class Strategy
{
public:
    virtual string State() = 0;
    virtual ~Strategy() {};
};
class Available : public Strategy
{
public:
    string State()
    {
        return "Available";
    }
};
class UpcomingSoon : public Strategy
{
public:
    string State()
    {
        return "UpcomingSoon";
    }
};
class OutOfStock : public Strategy
{
public:
    string State()
    {
        return "OutOfStock";
    }
};
class StateContext
{
    Strategy *strategy;

public:
    void setStrategy(Strategy *newStrategy)
    {
        if (strategy)
            delete strategy;
        strategy = newStrategy;
    }
    string State() const
    {
        if (strategy)
        {
            return strategy->State();
        }
        return "NotValid";
    }
    ~StateContext()
    {
        delete strategy;
    }
};
class Book{
    string BookTitle;
    string BookType;
    string BookAuthor;
    vector<string> BorrowedBooks;
    vector<string> readBooks;
    int availableCopies;
    StateContext stateContext;
    public:
    Book(string t,string Ty,string au, int avc){
        BookTitle=t;
        BookType=Ty;
        BookAuthor=au;
        availableCopies=avc;
        UpdateState();

    }
    void UpdateState(){
        if(availableCopies==0){
            stateContext.setStrategy(new OutOfStock());
        }
       else if(availableCopies<3){
            stateContext.setStrategy(new UpcomingSoon());
        }else{
            stateContext.setStrategy(new Available());
        }
    }
    void SetState(Strategy*strategy){
        stateContext.setStrategy(strategy);
    }
    string GetState()const{return stateContext.State();}
    void SetBookTitle(string title){
        BookTitle=title;
    }
     void SetBookType(string Type){
        BookType=Type;
    }
     void SetBookAuthor(string Author){
        BookAuthor=Author;
    }
     void SetBookTitle(string title){
        BookTitle=title;
    }
     void SetBookTitle(string title){
        BookTitle=title;
    }
    void SetAvailableCopies(int no){
        availableCopies=no;
        UpdateState();
    }
    string GetBookTitle(){return BookTitle;}
    string GetBookType(){return BookType;}
    string GetBookAuthor(){return BookAuthor;}
    int GetAvailableCopies(){return availableCopies;}
    void DecreaseBookCopies(){
        if(availableCopies>0)
        {availableCopies--;}
        UpdateState();
    }
    void increaseBookCopies(){
        availableCopies++;
        UpdateState();
    }
};
class User
{
    string UserName;
    vector<Book *> BorrowedBooks;

public:
    User(string name) : UserName(name) {}

    string GetUserName() const { return UserName; }
    vector<Book *> GetBorrowedBooks() const
    {
        return BorrowedBooks;
    }

    void BorrowBook(Book *book)
    {
        if (book->GetAvailableCopies() > 0)
        {
            BorrowedBooks.push_back(book);
            book->DecreaseBookCopies();
            cout << UserName << " borrowed \"" << book->GetBookTitle() << "\"\n";
        }
        else
        {
            cout << "Sorry, \"" << book->GetBookTitle() << "\" is not available now.\n";
        }
    }

    void ReturnBook(Book *book)
    {
        auto it = find(BorrowedBooks.begin(), BorrowedBooks.end(), book);
        if (it != BorrowedBooks.end())
        {
            BorrowedBooks.erase(it);
            book->increaseBookCopies();
            cout << UserName << " returned \"" << book->GetBookTitle() << "\"\n";
        }
        else
        {
            cout << "Book not found in " << UserName << "'s borrowed list.\n";
        }
    }

    void ShowBorrowedBooks()
    {
        cout << "Books borrowed by " << UserName << ":\n";
        for (auto book : BorrowedBooks)
            cout << "- " << book->GetBookTitle() << "\n";
    }
};
class libraryManager
{
    static libraryManager *instance;
    unordered_map<string, Book *> books;
    unordered_map<string, User *> users;
    libraryManager() {};

public:
    libraryManager(const libraryManager &) = delete;
    libraryManager &operator=(libraryManager &) = delete;
    ~libraryManager()
    {
        for (auto &pair : books)
            delete pair.second;
        for (auto &pair : users)
            delete pair.second;
    }

    static libraryManager *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new libraryManager();
        }
        return instance;
    }
    void AddBook(string title, string type, string author, int copies)
    {
        if (books.find(title) == books.end())
        {
            books[title] = new Book(title, type, author, copies);
            cout << "Book \"" << title << "\" added.\n";
        }
        else
        {
            cout << "Book \"" << title << "\" already exists.\n";
        }
    }

    void RemoveBook(string title)
    {
        auto it = books.find(title);
        if (it != books.end())
        {
            delete it->second;
            books.erase(it);
            cout << "Book \"" << title << "\" removed.\n";
        }
        else
        {
            cout << "Book not found.\n";
        }
    }

    void AddUser(string userName)
    {
        if (users.find(userName) == users.end())
        {
            users[userName] = new User(userName);
            cout << "User \"" << userName << "\" added.\n";
        }
        else
        {
            cout << "User \"" << userName << "\" already exists.\n";
        }
    }

    void BorrowBook(string userName, string title)
    {
        if (users.find(userName) != users.end() && books.find(title) != books.end())
        {
            users[userName]->BorrowBook(books[title]);
        }
        else
        {
            cout << "User or Book not found.\n";
        }
    }

    void ReturnBook(string userName, string title)
    {
        if (users.find(userName) != users.end() && books.find(title) != books.end())
        {
            users[userName]->ReturnBook(books[title]);
        }
        else
        {
            cout << "User or Book not found.\n";
        }
    }

    void ShowBookStatus(string title)
    {
        if (books.find(title) != books.end())
        {
            Book *book = books[title];
            cout << "Book: " << title << "\nState: " << book->GetState()
                 << "\nAvailable Copies: " << book->GetAvailableCopies() << "\n";
        }
        else
        {
            cout << "Book not found.\n";
        }
    }
    void saveToFile()
{
    // حفظ الكتب
    ofstream bookFile("books.txt");
    if (bookFile.is_open())
    {
        for (auto &pair : books)
        {
            Book *book = pair.second;
            bookFile << book->GetBookTitle() << ","
                     << book->GetBookType() << ","
                     << book->GetBookAuthor() << ","
                     << book->GetAvailableCopies() << ","
                     << book->GetState() << "\n";
        }
        bookFile.close();
        cout << "Books saved to books.txt\n";
    }
    else
    {
        cout << "Error opening books.txt\n";
    }

    // حفظ المستخدمين والكتب المستعارة
    ofstream userFile("users.txt");
    if (userFile.is_open())
    {
        for (auto &pair : users)
        {
            User *user = pair.second;
            userFile << user->GetUserName() << ":";
            vector<Book *> borrowed = user->GetBorrowedBooks();
            for (size_t i = 0; i < borrowed.size(); ++i)
            {
                userFile << borrowed[i]->GetBookTitle();
                if (i != borrowed.size() - 1)
                    userFile << "|";
            }
            userFile << "\n";
        }
        userFile.close();
        cout << "Users saved to users.txt\n";
    }
    else
    {
        cout << "Error opening users.txt\n";
    }
}
    bool HasUser(const string &userName)
    {
        return users.find(userName) != users.end();
    }

    void ShowUserBorrowedBooks(const string &userName)
    {
        if (users.find(userName) != users.end())
        {
            users[userName]->ShowBorrowedBooks();
        }
        else
        {
            cout << "User not found.\n";
        }
    }

};
libraryManager *libraryManager::instance = nullptr;