#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Library {
    string bookID, bookName, authorName, studentName, searchID;
    fstream file; // File handling object

public:
    void addBook();     // Add new book (Admin)
    void showAll();     // Show all books
    void searchBook();  // Search a specific book by ID
    void issueBook();   // Issue a book to student
    void returnBook();  // Return issued book
};
void Library::addBook() {
    cout << "\n===== Add New Book =====\n";
    cout << "Enter Book ID: ";
    getline(cin, bookID);
    cout << "Enter Book Name: ";
    getline(cin, bookName);
    cout << "Enter Author Name: ";
    getline(cin, authorName);

    // Open file in append mode (adds at the end)
    file.open("books.txt", ios::out | ios::app);
    file << bookID << "*" << bookName << "*" << authorName << endl;
    file.close();

    cout << "\n✅ Book added successfully!\n";
}
void Library::showAll() {
    file.open("books.txt", ios::in);

    if (!file) {
        cout << "\n⚠️ No books found yet!\n";
        return;
    }

    cout << "\n----------------------------------------------\n";
    cout << "Book ID\t\tBook Name\t\tAuthor\n";
    cout << "----------------------------------------------\n";

    // Read file data separated by '*'
    while (getline(file, bookID, '*')) {
        getline(file, bookName, '*');
        getline(file, authorName, '\n');
        cout << bookID << "\t\t" << bookName << "\t\t" << authorName << endl;
    }

    cout << "----------------------------------------------\n";
    file.close();
}
void Library::searchBook() {
    cout << "\nEnter Book ID to Search: ";
    getline(cin, searchID);

    file.open("books.txt", ios::in);
    if (!file) {
        cout << "\n⚠️ No book records found!\n";
        return;
    }

    bool found = false;
    while (getline(file, bookID, '*')) {
        getline(file, bookName, '*');
        getline(file, authorName, '\n');

        if (bookID == searchID) {
            cout << "\n✅ Book Found!\n";
            cout << "Book ID: " << bookID << endl;
            cout << "Book Name: " << bookName << endl;
            cout << "Author: " << authorName << endl;
            found = true;
            break;
        }
    }

    if (!found)
        cout << "\n❌ Book not found with ID: " << searchID << endl;

    file.close();
}
void Library::issueBook() {
    cout << "\nEnter Book ID to Issue: ";
    getline(cin, searchID);

    // Check if book exists in books.txt
    ifstream check("books.txt");
    bool found = false;
    string line;

    while (getline(check, line)) {
        if (line.find(searchID + "*") == 0) { // ID matches at line start
            found = true;
            break;
        }
    }
    check.close();

    if (!found) {
        cout << "\n❌ Book not found! Please check the ID.\n";
        return;
    }

    cout << "Enter Student Name: ";
    getline(cin, studentName);

    // Store issued book record
    ofstream issueFile("issued.txt", ios::app);
    issueFile << searchID << "*" << studentName << endl;
    issueFile.close();

    cout << "\n✅ Book issued successfully to " << studentName << "!\n";
}
void Library::returnBook() {
    cout << "\nEnter Book ID to Return: ";
    getline(cin, searchID);

    ifstream in("issued.txt");
    ofstream temp("temp.txt");

    bool found = false;
    string bID, stud;

    while (getline(in, bID, '*')) {
        getline(in, stud, '\n');

        if (bID == searchID) {
            cout << "\n✅ Book Returned by " << stud << "!\n";
            found = true;
            continue; // Skip writing this (book returned)
        }
        temp << bID << "*" << stud << endl;
    }

    in.close();
    temp.close();

    remove("issued.txt");
    rename("temp.txt", "issued.txt");

    if (!found)
        cout << "\n❌ No record found for this Book ID.\n";
}
int main() {
    Library lib;
    char choice;

    while (true) {
        cout << "\n=========================================\n";
        cout << "      📚 LIBRARY MANAGEMENT SYSTEM       \n";
        cout << "=========================================\n";
        cout << "1 - Show All Books\n";
        cout << "2 - Search Book by ID\n";
        cout << "3 - Add Book (Admin)\n";
        cout << "4 - Issue Book\n";
        cout << "5 - Return Book\n";
        cout << "6 - Exit\n";
        cout << "-----------------------------------------\n";
        cout << "Enter Your Choice: ";
        cin >> choice;
        cin.ignore();  // Clear input buffer

        switch (choice) {
            case '1': lib.showAll(); break;
            case '2': lib.searchBook(); break;
            case '3': lib.addBook(); break;
            case '4': lib.issueBook(); break;
            case '5': lib.returnBook(); break;
            case '6':
                cout << "\nThank you for using Library System!\n";
                return 0;
            default:
                cout << "\n⚠️ Invalid choice! Please try again.\n";
        }
    }
}
