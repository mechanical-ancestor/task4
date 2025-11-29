#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// 定义图书结构体
struct Book {
    string title;      // 书名
    string author;     // 作者
    double price;      // 价格
    bool isBorrowed;   // 是否借出
};

// 全局变量：图书列表
vector<Book> books;

// 函数声明
void displayMenu();
void addBook();
void borrowBook();
void returnBook();
void searchBook();
void clearInputBuffer();

int main() {
    int choice;
    
    // 主循环
    while (true) {
        displayMenu();
        cout << "Please enter your choice (0-4): ";
        cin >> choice;
        
        // 清除输入缓冲区
        clearInputBuffer();
        
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
            case 0:
                cout << "Thank you for using the Library Management System. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
                break;
        }
        
        cout << "\nPress Enter to continue...";
        cin.get(); // 等待用户按回车
    }
    
    return 0;
}

/**
 * 显示主菜单
 */
void displayMenu() {
    cout << "\n";
    cout << "===================================" << endl;
    cout << "    Library Management System" << endl;
    cout << "===================================" << endl;
    cout << "1. Add Book" << endl;
    cout << "2. Borrow Book" << endl;
    cout << "3. Return Book" << endl;
    cout << "4. Search Book" << endl;
    cout << "0. Exit" << endl;
    cout << "===================================" << endl;
}

/**
 * 清除输入缓冲区
 */
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/**
 * 添加图书（入库功能）
 */
void addBook() {
    Book newBook;
    
    cout << "\n=== Add New Book ===" << endl;
    
    // 输入书名
    cout << "Enter book title: ";
    getline(cin, newBook.title);
    
    // 输入作者
    cout << "Enter author: ";
    getline(cin, newBook.author);
    
    // 输入价格
    cout << "Enter price: ";
    while (!(cin >> newBook.price) || newBook.price < 0) {
        cout << "Invalid price! Please enter a valid number: ";
        clearInputBuffer();
    }
    clearInputBuffer();
    
    // 新书默认为未借出状态
    newBook.isBorrowed = false;
    
    // 添加到图书列表
    books.push_back(newBook);
    
    cout << "Book '" << newBook.title << "' added successfully!" << endl;
}

/**
 * 借书功能
 */
void borrowBook() {
    if (books.empty()) {
        cout << "\nNo books available in the library!" << endl;
        return;
    }
    
    cout << "\n=== Borrow Book ===" << endl;
    cout << "Available Books:" << endl;
    cout << "==============================================" << endl;
    cout << setw(4) << "No." << setw(20) << "Title" << setw(15) << "Status" << endl;
    cout << "==============================================" << endl;
    
    // 显示所有图书及其状态
    vector<int> availableBooks; // 存储可借阅图书的索引
    
    for (int i = 0; i < books.size(); i++) {
        string status = books[i].isBorrowed ? "Borrowed" : "Available";
        cout << setw(4) << (i + 1) << setw(20) << books[i].title << setw(15) << status << endl;
        
        if (!books[i].isBorrowed) {
            availableBooks.push_back(i);
        }
    }
    
    if (availableBooks.empty()) {
        cout << "No books available for borrowing!" << endl;
        return;
    }
    
    // 选择要借阅的图书
    int choice;
    cout << "\nEnter the number of the book you want to borrow (0 to cancel): ";
    cin >> choice;
    clearInputBuffer();
    
    if (choice == 0) {
        return;
    }
    
    // 验证选择
    if (choice < 1 || choice > books.size()) {
        cout << "Invalid book number!" << endl;
        return;
    }
    
    int bookIndex = choice - 1;
    
    // 检查图书是否可借
    if (books[bookIndex].isBorrowed) {
        cout << "Sorry, this book is already borrowed!" << endl;
    } else {
        books[bookIndex].isBorrowed = true;
        cout << "You have successfully borrowed '" << books[bookIndex].title << "'" << endl;
    }
}

/**
 * 还书功能
 */
void returnBook() {
    if (books.empty()) {
        cout << "\nNo books in the library!" << endl;
        return;
    }
    
    cout << "\n=== Return Book ===" << endl;
    
    // 显示已借出的图书
    vector<int> borrowedBooks; // 存储已借出图书的索引
    
    cout << "Borrowed Books:" << endl;
    cout << "==============================================" << endl;
    cout << setw(4) << "No." << setw(20) << "Title" << setw(15) << "Author" << endl;
    cout << "==============================================" << endl;
    
    for (int i = 0; i < books.size(); i++) {
        if (books[i].isBorrowed) {
            cout << setw(4) << (i + 1) << setw(20) << books[i].title << setw(15) << books[i].author << endl;
            borrowedBooks.push_back(i);
        }
    }
    
    if (borrowedBooks.empty()) {
        cout << "No books are currently borrowed!" << endl;
        return;
    }
    
    // 选择要归还的图书
    int choice;
    cout << "\nEnter the number of the book you want to return (0 to cancel): ";
    cin >> choice;
    clearInputBuffer();
    
    if (choice == 0) {
        return;
    }
    
    // 验证选择
    if (choice < 1 || choice > books.size()) {
        cout << "Invalid book number!" << endl;
        return;
    }
    
    int bookIndex = choice - 1;
    
    // 检查图书是否确实是借出的
    if (!books[bookIndex].isBorrowed) {
        cout << "This book is not borrowed!" << endl;
    } else {
        books[bookIndex].isBorrowed = false;
        cout << "You have successfully returned '" << books[bookIndex].title << "'" << endl;
    }
}

/**
 * 查询图书功能
 */
void searchBook() {
    if (books.empty()) {
        cout << "\nNo books available in the library!" << endl;
        return;
    }
    
    cout << "\n=== Search Book ===" << endl;
    
    // 显示所有图书
    cout << "All Books:" << endl;
    cout << "==============================================" << endl;
    cout << setw(4) << "No." << setw(20) << "Title" << endl;
    cout << "==============================================" << endl;
    
    for (int i = 0; i < books.size(); i++) {
        cout << setw(4) << (i + 1) << setw(20) << books[i].title << endl;
    }
    
    // 选择要查询的图书
    int choice;
    cout << "\nEnter the number of the book you want to search (0 to cancel): ";
    cin >> choice;
    clearInputBuffer();
    
    if (choice == 0) {
        return;
    }
    
    // 验证选择
    if (choice < 1 || choice > books.size()) {
        cout << "Invalid book number!" << endl;
        return;
    }
    
    int bookIndex = choice - 1;
    
    // 显示图书详细信息
    cout << "\n=== Book Details ===" << endl;
    cout << "Title: " << books[bookIndex].title << endl;
    cout << "Author: " << books[bookIndex].author << endl;
    cout << "Price: $" << fixed << setprecision(2) << books[bookIndex].price << endl;
    cout << "Status: " << (books[bookIndex].isBorrowed ? "Borrowed" : "Available") << endl;
}