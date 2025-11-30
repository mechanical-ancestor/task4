#include <iostream>
#include <string>
#include <vector>

using namespace std;

// 定义图书结构体
struct Book {
    string title;       // 书名
    string author;      // 作者
    double price;       // 价格
    bool isBorrowed;    // 是否借出
};

// 全局变量：图书集合
vector<Book> books;

// 函数声明
void showMenu();
void addBook();
void borrowBook();
void returnBook();
void searchBook();

int main() {
    int choice;

    do {
        showMenu();
        cout << "Please enter your choice (1-5): ";
        cin >> choice;

        switch (choice) {
        case 1:
            addBook();
            break;
        case 2:
            borrowBook();
            break;
        case 3:
            returnBook();
            break;
        case 4:
            searchBook();
            break;
        case 5:
            cout << "Thank you for using the system. Goodbye!" << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }

        if (choice != 5) {
            cout << "\nPress Enter to continue...";
            cin.ignore();
            cin.get();
        }

    } while (choice != 5);

    return 0;
}

// 显示菜单
void showMenu() {
    system("cls");  // 清屏（Windows）
    cout << "=== Book Management System ===" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Borrow Book" << endl;
    cout << "3. Return Book" << endl;
    cout << "4. Search Book" << endl;
    cout << "5. Exit" << endl;
    cout << "===============================" << endl;
}
// 入库功能
void addBook() {
    Book newBook;

    cout << "\n=== Add New Book ===" << endl;
    cout << "Enter book title: ";
    cin.ignore();
    getline(cin, newBook.title);

    cout << "Enter author: ";
    getline(cin, newBook.author);

    cout << "Enter price: ";
    cin >> newBook.price;

    newBook.isBorrowed = false;

    books.push_back(newBook);
    cout << "Book added successfully!" << endl;
}

// 借书功能
void borrowBook() {
    if (books.empty()) {
        cout << "No books in the library!" << endl;
        return;
    }

    cout << "\n=== Borrow Book ===" << endl;
    cout << "Available Books:" << endl;

    // 显示所有书籍和借出状态
    for (int i = 0; i < books.size(); i++) {
        cout << i + 1 << ". " << books[i].title
            << " - " << (books[i].isBorrowed ? "Borrowed" : "Available") << endl;
    }

    int bookIndex;
    cout << "Select book number to borrow: ";
    cin >> bookIndex;

    if (bookIndex < 1 || bookIndex > books.size()) {
        cout << "Invalid book number!" << endl;
        return;
    }

    if (books[bookIndex - 1].isBorrowed) {
        cout << "This book is already borrowed!" << endl;
    }
    else {
        books[bookIndex - 1].isBorrowed = true;
        cout << "Book borrowed successfully!" << endl;
    }
}

// 还书功能
void returnBook() {
    if (books.empty()) {
        cout << "No books in the library!" << endl;
        return;
    }

    cout << "\n=== Return Book ===" << endl;
    cout << "Borrowed Books:" << endl;

    // 显示已借出的书籍
    bool hasBorrowed = false;
    for (int i = 0; i < books.size(); i++) {
        if (books[i].isBorrowed) {
            cout << i + 1 << ". " << books[i].title << endl;
            hasBorrowed = true;
        }
    }

    if (!hasBorrowed) {
        cout << "No borrowed books to return!" << endl;
        return;
    }

    int bookIndex;
    cout << "Select book number to return: ";
    cin >> bookIndex;

    if (bookIndex < 1 || bookIndex > books.size() || !books[bookIndex - 1].isBorrowed) {
        cout << "Invalid selection!" << endl;
        return;
    }

    books[bookIndex - 1].isBorrowed = false;
    cout << "Book returned successfully!" << endl;
}

// 查询功能
void searchBook() {
    if (books.empty()) {
        cout << "No books in the library!" << endl;
        return;
    }

    cout << "\n=== Search Book ===" << endl;
    cout << "All Books:" << endl;

    // 显示所有书籍
    for (int i = 0; i < books.size(); i++) {
        cout << i + 1 << ". " << books[i].title << endl;
    }

    int bookIndex;
    cout << "Select book number to view details: ";
    cin >> bookIndex;

    if (bookIndex < 1 || bookIndex > books.size()) {
        cout << "Invalid book number!" << endl;
        return;
    }

    Book& book = books[bookIndex - 1];
    cout << "\n=== Book Details ===" << endl;
    cout << "Title: " << book.title << endl;
    cout << "Author: " << book.author << endl;
    cout << "Price: $" << book.price << endl;
    cout << "Status: " << (book.isBorrowed ? "Borrowed" : "Available") << endl;
}
