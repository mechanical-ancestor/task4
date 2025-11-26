#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

// 定义图书结构体,成员：名称、作者、价格、是否借出
struct Book {
    string title;
    string author;
    float price;
    bool isborrowed;
};

vector<Book> books; // 声明Book类型的容器，用于储存书的消息

// 函数声明自定义函数
void Menu();
void Add();
void Borrow();
void Return();
void Query();

// 初始化3本图书数据：一本已借出
void initialize() {
    // 添加书
    Book book1;     // 创建Book类型的对象，记载一本书的信息
    book1.title = "动手学机器学习";
    book1.author = "俞勇";
    book1.price = 89.80;
    book1.isborrowed = true;
    books.push_back(book1);

    Book book2;
    book2.title = "ROS2机器人开发";
    book2.author = "小鱼";
    book2.price = 99.00;
    book2.isborrowed = false;
    books.push_back(book2);

    Book book3;
    book3.title = "Easy RL";
    book3.author = "王琦";
    book3.price = 99.00;
    book3.isborrowed = false; 
    books.push_back(book3);
}

// 主菜单
void Menu() {
    cout << "1. Add book" << endl;
    cout << "2. Borrow book" << endl;
    cout << "3. Return book" << endl;
    cout << "4. Query book" << endl;
    cout << "5. Exit" << endl;
}

// 入库
void Add() {
    Book newbook;   // 创建Book类型的对象，储存新入库的书的信息
    
    cout << "\nAdd New Book: " << endl;
    cout << "Enter book title: ";
    getline(cin, newbook.title);
    
    cout << "Enter author: ";
    getline(cin, newbook.author);
    
    while (true) {
        cout << "Enter price(￥): ";
        cin >> newbook.price;
        if (newbook.price) {     // 验证价格输入是否为数字
            if (newbook.price >= 0) {
                break;
            } 
            else {
                cout << "价格不能为负数" << endl;
            }
        } 
        else {
            cin.clear();    // 重置输入状态
            cin.ignore(numeric_limits<streamsize>::max(), '\n');    //清除输入内容

            cout << "请输入有效的数字" << endl;
        }
    }
    
    newbook.isborrowed = false;
    
    books.push_back(newbook);      // 在books容器内添加书籍
    cout << "Book added successfully!" << endl;
}

// 借书功能
void Borrow() {
    cout << "\nBorrow Book: " << endl;
    
    vector<int> Available;  // 创建一个用于存储可借阅图书的索引的容器
    
    for(int i = 0; i < books.size(); i++) {
        string status = books[i].isborrowed ? "Borrowed" : "Available";     // 将书本的借用状态赋值status
        cout << setw(3) << i+1 << ". " << books[i].title << setw(10) << status << endl;
        
        if(!books[i].isborrowed) {
            Available.push_back(i);     // 存储可借阅图书的索引
        }
    }
    
    if(Available.empty()) {     // 判断是否有书可以借出
        cout << "No available books to borrow" << endl;
        return;
    }
    
    int borrow_choice;
    while (true) {
        cout << "Enter book number to borrow: ";
        cin >> borrow_choice;
    
        if(borrow_choice < 1 || borrow_choice > books.size()) {     // 判断选取书的编号是否超过范围
            cout << "Invalid book number, please Enter book number" << endl;
        }
        else if (books[borrow_choice - 1].isborrowed) {
            cout << "This book is already borrowed, please borrow another" << endl;
        }
        else {
            break;
        }
    }
    
    books[borrow_choice - 1].isborrowed = true;
    cout << "Book '" << books[borrow_choice - 1].title << "' borrowed successfully" << endl;
}

// 还书
void Return() {
    cout << "Return book: " << endl;
    vector<int> borrowed_book; 
    
    for(int i = 0; i < books.size(); i++) {
        if(books[i].isborrowed) {   // 判断是否有书已借出
            borrowed_book.push_back(i);  // 存储已借出图书的索引
        }
    }
    
    if(borrowed_book.empty()) {
        cout << "No books are currently borrowed" << endl;
        return;     // 若无书可借，则提前退出
    }
    
    cout << "Borrowed books:" << endl;
    
    for(int i = 0; i < borrowed_book.size(); i++) {
        int bookIndex = borrowed_book[i];
        cout << setw(3) << i+1 << ". " << books[bookIndex].title << endl;
    }
    
    int return_choice;
    while (true) {
        cout << "Enter book number to return: ";
        cin >> return_choice;
    
        if(return_choice < 1 || return_choice > borrowed_book.size()) {     // 判断选取书的编号是否超过范围
            cout << "Invalid book number, please Enter book number" << endl;
        }
        else {
            break;
        }
    }
    
    books[return_choice - 1].isborrowed = false;   // 借出书本
    cout << "Book '" << books[return_choice - 1].title << "' returned successfully" << endl;
}

// 查询功能
void Query() { 
    cout << "\nQuery Book: " << endl;

    for(int i = 0; i < books.size(); i++) {
        cout << setw(3) << i+1 << ". " << setw(5) << books[i].title << endl;
    }
    
    int query_choice;
    while (true) {
        cout << "Enter book number to query: ";
        cin >> query_choice;
    
        if(query_choice < 1 || query_choice > books.size()) {   // 判断选取书的编号是否超过范围
            cout << "Invalid book number, please Enter book number" << endl;
        }
        else {
            break;
        }
    }
    
    int query_index = query_choice - 1;
    cout << "\nBook Details: " << endl;   // 输出书本的详细信息
    cout << "Title: " << books[query_index].title << endl;
    cout << "Author: " << books[query_index].author << endl;
    cout << "Price(￥): " << fixed << setprecision(2) << books[query_index].price << endl;
    cout << "Status: " << (books[query_index].isborrowed ? "Borrowed" : "Available") << endl;
}

int main() {
    int choice;

    initialize();
    
    do {    // 先显示菜单再判断选项
        Menu();
        cout << "Select the function you wish to process (1-5): ";
        cin >> choice;
        cin.clear();
        cin.ignore();

        switch(choice) {    // 对chioce的输入分情况执行
            case 1:
                Add();
                break;
            case 2:
                Borrow();
                break;
            case 3:
                Return();
                break;
            case 4:
                Query();
                break;
            case 5:
                cout << "Thank you for using Library Management System" << endl;
                break;
            default:
                cout << "Invalid choice, Please Enter 1-5" << endl;
        }
        
        cout << endl;
    } while(choice != 5);
    
    return 0;
}
