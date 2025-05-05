#include <iostream>
#include <string>

#define BOOK_LIMIT 50 // New way of defining constants learnt in class

using namespace std;

class Book
{
private:
    string title;
    string author;
    string isbn;
    double price;
public:
    // Constructor
    Book(string t = "", string a = "", string i = "", double p = 0.0)
    {
        title = t;
        author = a;
        isbn = i;
        price = p;
        cout << "Book object created" << endl;
    }

    // Destructor
    ~Book()
    {
        cout << "Book object destruction has begun" << endl;
    }

    // Getters
    string getTitle() { return title; }
    string getAuthor() { return author; }
    string getIsbn() { return isbn; }
    double getPrice() { return price; }

    // Setters
    void setTitle(string t) { title = t; }
    void setAuthor(string a) { author = a; }
    void setIsbn(string i) { isbn = i; }
    void setPrice(double p) { price = p; }

    // Display function
    void display()
    {
        cout << endl << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "Price: " << price << endl;
    }
};

class Library
{
private:
    Book** books;       // Pointer to an array of Book pointers
    int counter;        // Current number of books

public:
    // Constructor
    Library()
    {
        counter = 0;
        // Allocate memory for an array of Book pointers
        books = new Book*[BOOK_LIMIT];

        // Initialize with nullptr
        for (int i = 0; i < BOOK_LIMIT; i++) {
            books[i] = nullptr;
        }

        // Add some initial books
        addBook("The Great Gatsby", "F. Scott Fitzgerald", "24127645", 10.99);
        addBook("To Kill a Mockingbird", "Harper Lee", "24127646", 12.99);
        addBook("1984", "George Orwell", "24127647", 9.99);
        addBook("Pride and Prejudice", "Jane Austen", "24127648", 8.99);
        addBook("The Catcher in the Rye", "J.D. Salinger", "24127649", 11.99);
    }

    // Destructor
    ~Library()
    {
        // Free memory for each Book object
        for (int i = 0; i < counter; i++) {
            if (books[i] != nullptr) {
                delete books[i];
            }
        }
        // Free the array of pointers
        delete[] books;
    }

    // Add a book with separate parameters
    void addBook(string title, string author, string isbn, double price)
    {
        if (counter >= BOOK_LIMIT) {
            cout << "Library is full!" << endl;
            return;
        }

        // Create a new Book object on the heap
        books[counter] = new Book(title, author, isbn, price);
        counter++;

        cout << "Book added successfully!" << endl;
    }

    // Add a book from user input
    void addBook()
    {
        if (counter >= BOOK_LIMIT) {
            cout << "Library is full!" << endl;
            return;
        }

        string title, author, isbn;
        double price;

        cin.ignore();
        cout << "Enter the title of the book: ";
        getline(cin, title);
        cout << "Enter the author of the book: ";
        getline(cin, author);
        cout << "Enter the isbn of the book: ";
        getline(cin, isbn);
        cout << "Enter the price of the book: ";
        cin >> price;

        // Create a new Book object on the heap
        books[counter] = new Book(title, author, isbn, price);
        counter++;

        cout << "Book added successfully!" << endl;
    }

    // Display all books
    void displayAll()
    {
        if (counter == 0) {
            cout << endl << "No book available." << endl;
            return;
        }

        cout << endl << "Books available:" << endl;
        for (int i = 0; i < counter; i++) {
            books[i]->display();  // Using -> operator for pointer
        }
    }

    // Delete a book
    void deleteBook()
    {
        if (counter == 0) {
            cout << "Sorry. No book to delete." << endl;
            return;
        }

        string isbnToBeDeleted;
        cout << "Enter the isbn: ";
        cin.ignore();
        getline(cin, isbnToBeDeleted);

        int foundIndex = -1;
        for (int i = 0; i < counter; i++) {
            if (books[i]->getIsbn() == isbnToBeDeleted) {
                foundIndex = i;
                break;
            }
        }

        if (foundIndex == -1) {
            cout << "Book with the ISBN " << isbnToBeDeleted << " not found!!" << endl;
            return;
        }

        cout << endl << "Book found: " << endl;
        books[foundIndex]->display();

        string confirm;
        cout << "Is this the book you want to delete? (yes/no): ";
        cin >> confirm;

        if (confirm == "yes") {
            // Free the memory for the Book object
            delete books[foundIndex];

            // Shift remaining pointers
            for (int j = foundIndex; j < counter - 1; j++) {
                books[j] = books[j + 1];
            }

            // Set the last pointer to nullptr
            books[counter - 1] = nullptr;
            counter--;

            cout << "Book successfully removed!!" << endl;
        } else {
            cout << "Deletion cancelled." << endl;
        }
    }

    // Search for a book
    void searchBook()
    {
        if (counter == 0) {
            cout << "No books available to search." << endl;
            return;
        }

        int choice;
        cout << endl << "Search by: " << endl;
        cout << "1. Title" << endl;
        cout << "2. ISBN" << endl;
        cout << "3. Author" << endl;
        cout << "4. Price" << endl;
        cout << "Response => ";
        cin >> choice;

        // Variable to track if any books were found
        bool found = false;

        if (choice == 1) {
            string searchTitle;
            cout << "Enter book title: ";
            cin.ignore();
            getline(cin, searchTitle);

            for (int i = 0; i < counter; i++) {
                if (books[i]->getTitle() == searchTitle) {
                    cout << endl << "Book found:" << endl;
                    books[i]->display();
                    found = true;
                }
            }
        }
        else if (choice == 2) {
            string searchISBN;
            cout << "Enter ISBN: ";
            cin.ignore();
            getline(cin, searchISBN);

            for (int i = 0; i < counter; i++) {
                if (books[i]->getIsbn() == searchISBN) {
                    cout << endl << "Book found:" << endl;
                    books[i]->display();
                    found = true;
                }
            }
        }
        else if (choice == 3) {
            string searchAuthor;
            cout << "Enter author name: ";
            cin.ignore();
            getline(cin, searchAuthor);

            for (int i = 0; i < counter; i++) {
                if (books[i]->getAuthor() == searchAuthor) {
                    cout << endl << "Book found:" << endl;
                    books[i]->display();
                    found = true;
                }
            }
        }
        else if (choice == 4) {
            double searchPrice;
            cout << "Enter price: ";
            cin >> searchPrice;

            for (int i = 0; i < counter; i++) {
                if (books[i]->getPrice() == searchPrice) {
                    cout << endl << "Book found:" << endl;
                    books[i]->display();
                    found = true;
                }
            }
        }
        else {
            cout << "Invalid choice." << endl;
            return;
        }

        if (!found) {
            cout << "No books found matching your search criteria." << endl;
        }
    }

    // Edit a book
    void editBook()
    {
        if (counter == 0) {
            cout << "No books available to edit." << endl;
            return;
        }

        string isbn;
        cout << "Enter the ISBN of the book to edit: ";
        cin.ignore();
        getline(cin, isbn);

        int foundIndex = -1;
        for (int i = 0; i < counter; i++) {
            if (books[i]->getIsbn() == isbn) {
                foundIndex = i;
                break;
            }
        }

        if (foundIndex == -1) {
            cout << "Book with ISBN " << isbn << " not found!" << endl;
            return;
        }

        cout << endl << "Book found: " << endl;
        books[foundIndex]->display();

        string confirm;
        cout << "Is this the book you want to edit? (yes/no): ";
        cin >> confirm;

        if (confirm == "yes") {
            int editChoice;
            cout << endl << "What would you like to edit?" << endl;
            cout << "1. Title" << endl;
            cout << "2. Author" << endl;
            cout << "3. ISBN" << endl;
            cout << "4. Price" << endl;
            cout << "Response => ";
            cin >> editChoice;

            cin.ignore(); // Clear the input buffer

            if (editChoice == 1) {
                string newTitle;
                cout << "Enter new title: ";
                getline(cin, newTitle);
                books[foundIndex]->setTitle(newTitle);
                cout << "Book title updated successfully!" << endl;
            }
            else if (editChoice == 2) {
                string newAuthor;
                cout << "Enter new author: ";
                getline(cin, newAuthor);
                books[foundIndex]->setAuthor(newAuthor);
                cout << "Book author updated successfully!" << endl;
            }
            else if (editChoice == 3) {
                string newISBN;
                cout << "Enter new ISBN: ";
                getline(cin, newISBN);
                books[foundIndex]->setIsbn(newISBN);
                cout << "Book ISBN updated successfully!" << endl;
            }
            else if (editChoice == 4) {
                double newPrice;
                cout << "Enter new price: ";
                cin >> newPrice;
                books[foundIndex]->setPrice(newPrice);
                cout << "Book price updated successfully!" << endl;
            }
            else {
                cout << "Invalid choice. No changes made." << endl;
            }
        } else {
            cout << "Edit cancelled." << endl;
        }
    }
};

int main()
{
    // Create a Library object on the stack
    Library lib;

    int choice;
    do {
        cout << endl << "Welcome to the Library Book Store." << endl << endl;
        cout << "Please select an option" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Display all books" << endl;
        cout << "3. Search for book" << endl;
        cout << "4. Delete book" << endl;
        cout << "5. Edit book" << endl;
        cout << "6. Exit" << endl;
        cout << "Response => ";
        cin >> choice;

        switch (choice) {
            case 1:
                lib.addBook();
                break;
            case 2:
                lib.displayAll();
                break;
            case 3:
                lib.searchBook();
                break;
            case 4:
                lib.deleteBook();
                break;
            case 5:
                lib.editBook();
                break;
            case 6:
                cout << "Thank you for using the program." << endl;
                break;
            default:
                cout << "Invalid option. Please try again.";
                break;
        }
    } while (choice != 6);

    // Library destructor will be called automatically when program exits
    return 0;
}
