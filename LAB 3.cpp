#include <iostream>

#define BOOK_LIMIT 50 // New way of defining constants learnt in class

using namespace std;

class Book
{
private:
    //private member variables that allow restrict access
    string title;
    string author;
    string isbn;
    double price;
public:
    //The constructor which allows empty books
    Book(string t = "", string a ="", string i ="", double p=0.0)
    {
        title = t;
        author = a;
        isbn = i;
        price = p;
    }

    //The getters
    string getTitle() { return title;}
    string getAuthor() { return author; }
    string getIsbn() { return isbn; }
    double getPrice() { return price; }

    // The setters
    void setTitle(string t){ title = t; }
    void setAuthor(string a){ author = a; }
    void setIsbn(string i) { isbn = i; }
    void setPrice(double p) { price = p; }

    //member function for displaying the items
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
    Book books[BOOK_LIMIT] = {
        Book("The Great Gatsby", "F. Scott Fitzgerald", "24127645", 10.99),
        Book("To Kill a Mockingbird", "Harper Lee", "24127646", 12.99),
        Book("1984", "George Orwell", "24127647", 9.99),
        Book("Pride and Prejudice", "Jane Austen", "24127648", 8.99),
        Book("The Catcher in the Rye", "J.D. Salinger", "24127649", 11.99)
    };
    int counter = 5;

public:
    // Member function for adding the books
    void addBook()
    {
        if(counter >= BOOK_LIMIT)
        {
            cout << "Library is full!" << endl;
            return;
        }

        string title, author, isbn;
        double price;

        cin.ignore();
        cout << "Enter the title of the book: ";
        getline(cin,title);
        cout << "Enter the author of the book: ";
        getline(cin,author);
        cout << "Enter the isbn of the book: ";
        getline(cin,isbn);
        cout << "Enter the price of the book: ";
        cin >> price;

        books[counter] = Book(title, author, isbn, price);
        counter++;

        cout << "Book added successfully!" << endl;
    }

    // Display all the books available in the Library
    void displayAll()
    {
        if (counter == 0)
        {
            cout << endl << "No book available." << endl;
            return;
        }

        cout << endl << "Books available" << endl;
        for(int i = 0; i < counter; i++)
        {
            if (books[i].getTitle() == "")
            {
                break;
            }
            books[i].display();
        }
    }

    void deleteBook()
    {
        if (counter == 0)
        {
            cout << "Sorry. No book to delete." << endl;
            return;
        }
        string isbnToBeDeleted;
        cout << "Enter the isbn: ";
        cin.ignore();
        getline(cin, isbnToBeDeleted);

        int foundIndex = -1;
        for (int i = 0; i < counter; i++)
        {
            if (books[i].getIsbn() == isbnToBeDeleted)
            {
                foundIndex = i;
                break;
            }
        }

        if (foundIndex == -1)
        {
            cout << "Book with the ISBN " << isbnToBeDeleted << " not found!!" << endl;
            return;
        }

        cout << endl << "Book found: " << endl;
        books[foundIndex].display();
        string confirm;
        cout << "Is this the book you want to delete? (yes/no): ";
        cin >> confirm;

        if (confirm == "yes")
        {
            for (int j = foundIndex; j < counter - 1; j++)
            {
                books[j] = books[j + 1];
            }
            books[counter - 1] = Book(); // Clear the last book
            counter--;
            cout << "Book successfully removed!!" << endl;
        }
        else
        {
            cout << "Deletion cancelled." << endl;
        }
    }

    void searchBook()
    {
        if (counter == 0)
        {
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

        int foundIndex = -1;
        if (choice == 1)
        {
            string searchTitle;
            cout << "Enter book title: ";
            cin.ignore();
            getline(cin, searchTitle);
            for (int i = 0; i < counter; i++)
            {
                if (books[i].getTitle() == searchTitle)
                {
                    foundIndex = i;
                    break;
                }
            }
        }
        else if (choice == 2)
        {
            string searchISBN;
            cout << "Enter ISBN: ";
            cin.ignore();
            getline(cin, searchISBN);
            for (int i = 0; i < counter; i++)
            {
                if (books[i].getIsbn() == searchISBN)
                {
                    foundIndex = i;
                    break;
                }
            }
        }
        else if (choice == 3)
        {
            string searchAuthor;
            cout << "Enter author name: ";
            cin.ignore();
            getline(cin, searchAuthor);
            for (int i = 0; i < counter; i++)
            {
                if (books[i].getAuthor() == searchAuthor)
                {
                    foundIndex = i;
                    break;
                }
            }
        }
        else if (choice == 4)
        {
            double searchPrice;
            cout << "Enter price: ";
            cin >> searchPrice;
            for (int i = 0; i < counter; i++)
            {
                if (books[i].getPrice() == searchPrice)
                {
                    foundIndex = i;
                    break;
                }
            }
        }
        else
        {
            cout << "Invalid choice." << endl;
            return;
        }

        if (foundIndex == -1)
        {
            cout << "Book not found." << endl;
            return;
        }

        cout << endl << "Book found: " << endl;
        books[foundIndex].display();
    }

    void editBook()
    {
        if (counter == 0)
        {
            cout << "No books available to edit." << endl;
            return;
        }

        string isbn;
        cout << "Enter the ISBN of the book to edit: ";
        cin.ignore();
        getline(cin, isbn);

        int foundIndex = -1;
        for (int i = 0; i < counter; i++)
        {
            if (books[i].getIsbn() == isbn)
            {
                foundIndex = i;
                break;
            }
        }

        if (foundIndex == -1)
        {
            cout << "Book with ISBN " << isbn << " not found!" << endl;
            return;
        }

        cout << endl << "Book found: " << endl;
        books[foundIndex].display();
        string confirm;
        cout << "Is this the book you want to edit? (yes/no): ";
        cin >> confirm;

        if (confirm == "yes")
        {
            string newTitle;
            cout << "Enter new title: ";
            cin.ignore();
            getline(cin, newTitle);
            books[foundIndex].setTitle(newTitle);
            cout << "Book title updated successfully!" << endl;
        }
        else
        {
            cout << "Edit cancelled." << endl;
        }
    }
};

int main()
{
    Library lib;

    int choice;
    do
    {
        cout << endl << "Welcome to the Library Book Store." << endl << endl;
        cout << "Please select an option" << endl;
        cout << "1. Add Book" << endl;
        cout << "2. Display all books" << endl;
        cout << "3. Search for book" << endl;
        cout << "4. Delete book" << endl;
        cout << "5. Edit book title" << endl;
        cout << "6. Exit" << endl;
        cout << "Response => ";
        cin >> choice;

        switch(choice)
        {
            case 1:
            {
                lib.addBook();
                break;
            }
            case 2:
            {
                lib.displayAll();
                break;
            }
            case 3:
            {
                lib.searchBook();
                break;
            }
            case 4:
            {
                lib.deleteBook();
                break;
            }
            case 5:
            {
                lib.editBook();
                break;
            }
            case 6:
            {
                cout << "Thank you for using the program." << endl;
                break;
            }
            default:
            {
                cout << "Invalid option. Please try again.";
                break;
            }
        }
    }
    while(choice != 6);

    return 0;
}
