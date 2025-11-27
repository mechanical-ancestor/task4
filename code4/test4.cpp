#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>  // 用于 system("cls") 清屏

using namespace std;

// 定义图书结构体：存储单本图书的信息
struct Book {
    string bookName;   // 书名
    string author;     // 作者
    double price;      // 价格
    bool isBorrowed;   // 借阅状态：true=已借出，false=未借出
};

// 1. 显示操作菜单
void showMenu() {
    cout << "===================== 图书管理系统 =====================" << endl;
    cout << "1. 图书入库" << endl;
    cout << "2. 图书借阅" << endl;
    cout << "3. 图书归还" << endl;
    cout << "4. 图书查询" << endl;
    cout << "======================================================" << endl;
}

// 2. 图书入库功能
void addBook(vector<Book>& bookList) {
    Book newBook;  // 临时存储新入库图书信息
    cout << "\n===== 图书入库 =====" << endl;
    
    cout << "请输入书名：";
    getline(cin, newBook.bookName);  // 支持带空格的书名输入
    
    cout << "请输入作者：";
    getline(cin, newBook.author);
    
    cout << "请输入价格：";
    cin >> newBook.price;
    cin.ignore();  // 清除价格输入后的换行符，避免影响后续 getline
    
    newBook.isBorrowed = false;  // 新图书默认未借出
    bookList.push_back(newBook);  // 将新图书添加到列表
    
    cout << "\n图书《" << newBook.bookName << "》入库成功！" << endl;
}

// 3. 图书借阅功能
void borrowBook(vector<Book>& bookList) {
    if (bookList.empty()) {
        cout << "\n暂无图书，请先入库！" << endl;
        return;
    }

    cout << "\n===== 图书借阅 =====" << endl;
    cout << "当前可借图书列表：" << endl;
    // 遍历显示所有未借出的图书
    for (int i = 0; i < bookList.size(); i++) {
        if (!bookList[i].isBorrowed) {
            cout << i + 1 << ". 《" << bookList[i].bookName << "》（作者：" << bookList[i].author << "）" << endl;
        }
    }

    string borrowName;
    cout << "\n请输入要借阅的书名：";
    getline(cin, borrowName);

    // 查找并修改借阅状态
    bool found = false;
    for (auto& book : bookList) {
        if (book.bookName == borrowName) {
            found = true;
            if (book.isBorrowed) {
                cout << "\n《" << borrowName << "》已被借出，无法借阅！" << endl;
            } else {
                book.isBorrowed = true;
                cout << "\n《" << borrowName << "》借阅成功！" << endl;
            }
            break;
        }
    }
    if (!found) {
        cout << "\n未找到图书《" << borrowName << "》！" << endl;
    }
}

// 4. 图书归还功能
void returnBook(vector<Book>& bookList) {
    if (bookList.empty()) {
        cout << "\n暂无图书！" << endl;
        return;
    }

    cout << "\n===== 图书归还 =====" << endl;
    cout << "当前已借出的图书：" << endl;
    bool hasBorrowed = false;
    for (int i = 0; i < bookList.size(); i++) {
        if (bookList[i].isBorrowed) {
            cout << i + 1 << ". 《" << bookList[i].bookName << "》" << endl;
            hasBorrowed = true;
        }
    }

    if (!hasBorrowed) {
        cout << "\n暂无已借出的图书！" << endl;
        return;
    }

    string returnName;
    cout << "\n请输入要归还的书名：";
    getline(cin, returnName);

    // 查找并修改归还状态
    bool found = false;
    for (auto& book : bookList) {
        if (book.bookName == returnName) {
            found = true;
            if (!book.isBorrowed) {
                cout << "\n《" << returnName << "》未被借出，无需归还！" << endl;
            } else {
                book.isBorrowed = false;
                cout << "\n《" << returnName << "》归还成功！" << endl;
            }
            break;
        }
    }
    if (!found) {
        cout << "\n未找到图书《" << returnName << "》！" << endl;
    }
}

// 5. 图书查询功能
void queryBook(const vector<Book>& bookList) {
    if (bookList.empty()) {
        cout << "\n暂无图书，请先入库！" << endl;
        return;
    }

    cout << "\n===== 图书查询 =====" << endl;
    cout << "当前所有图书：" << endl;
    for (int i = 0; i < bookList.size(); i++) {
        cout << i + 1 << ". 《" << bookList[i].bookName << "》 - " 
             << (bookList[i].isBorrowed ? "【已借出】" : "【可借阅】") << endl;
    }

    string queryName;
    cout << "\n请输入要查询的书名：";
    getline(cin, queryName);

    // 查找并显示详细信息
    bool found = false;
    for (const auto& book : bookList) {
        if (book.bookName == queryName) {
            found = true;
            cout << "\n===== 《" << queryName << "》详情 =====" << endl;
            cout << "作者：" << book.author << endl;
            cout << "价格：" << book.price << " 元" << endl;
            cout << "状态：" << (book.isBorrowed ? "已借出" : "可借阅") << endl;
            break;
        }
    }
    if (!found) {
        cout << "\n未找到图书《" << queryName << "》！" << endl;
    }
}

// 主函数：程序入口
int main() {
    vector<Book> bookList;  // 存储所有图书的动态列表
    int choice;             // 用户选择的操作编号

    while (true) {  // 循环显示菜单，直到手动关闭程序
        showMenu();
        cout << "\n请输入操作编号（1-4）：";
        cin >> choice;
        cin.ignore();  // 清除输入编号后的换行符，避免影响后续 getline

        // 根据用户选择执行对应功能
        switch (choice) {
            case 1:
                addBook(bookList);
                break;
            case 2:
                borrowBook(bookList);
                break;
            case 3:
                returnBook(bookList);
                break;
            case 4:
                queryBook(bookList);
                break;
            default:
                cout << "\n输入无效，请重新输入 1-4 之间的编号！" << endl;
                break;
        }

        // 操作完成后暂停，等待用户确认后清屏
        cout << "\n按回车键返回菜单..." << endl;
        cin.get();
        system("cls");  // Windows 清屏命令（Linux/macOS 请改为 "clear"）
    }

    return 0;
}
