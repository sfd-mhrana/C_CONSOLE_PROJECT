#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Book class to represent books (Model Class)
class Book
{
public:
    string title;
    string author;
    int id;
    bool isAvailable;

    Book(string title, string author, int id)
    {
        this->title = title;
        this->author = author;
        this->id = id;
        this->isAvailable = true;
    }
};

// Library class to manage books (Controller Class)
class Library
{
private:
    vector<Book> books;

public:
    // Add book to the library
    void addBook(string title, string author, int id)
    {
        Book newBook(title, author, id);
        books.push_back(newBook);
    }

    // Display all books
    void displayBooks()
    {
        if (books.size() <= 0)
        {
            cout<<"No Books Found";
        }
        else
        {
            cout << "Books available in the library:" << endl;
            for (const auto &book : books)
            {
                if (book.isAvailable)
                {
                    cout << "Title: " << book.title << ", Author: " << book.author << ", ID: " << book.id << endl;
                }
            }
        }
    }

    // Edit a book
    void editBook(int id, string newTitle, string newAuthor)
    {
        for (auto &book : books)
        {
            if (book.id == id && book.isAvailable)
            {
                book.title = newTitle;
                book.author = newAuthor;
                cout << "Book with ID " << id << " has been edited successfully." << endl;
                return;
            }
        }
        cout << "Book with ID " << id << " is not available." << endl;
    }

    // Delete a book
    void deleteBook(int id)
    {
        for (auto it = books.begin(); it != books.end(); ++it)
        {
            if (it->id == id && it->isAvailable)
            {
                books.erase(it);
                cout << "Book with ID " << id << " has been deleted successfully." << endl;
                return;
            }
        }
        cout << "Book with ID " << id << " is not available." << endl;
    }

};

int main()
{
    Library library;

    int choice, bookId;
    string bookTitle, bookAuthor;

    // Main menu
    do
    {
        cout << "\n****Library Management System****\n";
        cout << "1. Display all books\n";
        cout << "2. Add a book\n";
        cout << "3. Edit a book\n";
        cout << "4. Delete a book\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            library.displayBooks();
            break;
        case 2:
            cout << "Enter Book Title: ";
            cin.ignore();
            getline(cin, bookTitle);
            cout << "Enter Book Author: ";
            getline(cin, bookAuthor);
            cout << "Enter Book ID: ";
            cin >> bookId;
            library.addBook(bookTitle, bookAuthor, bookId);
            cout << "Book added successfully.\n";
            break;
        case 3:
            cout << "Enter the ID of the book you want to edit: ";
            cin >> bookId;
            cout << "Enter the new title for the book: ";
            cin.ignore();
            getline(cin, bookTitle);
            cout << "Enter the new author for the book: ";
            getline(cin, bookAuthor);
            library.editBook(bookId, bookTitle, bookAuthor);
            break;
        case 4:
            cout << "Enter the ID of the book you want to delete: ";
            cin >> bookId;
            library.deleteBook(bookId);
            break;
        case 5:
            cout << "Exiting the program. Thank you!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
    while (choice != 5);

    return 0;
}
