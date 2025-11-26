#include <iostream>
#include <string>
#include <vector>
using namespace std;

// 定义图书结构体
struct Book {
    string name;     // 书名
    string author;   // 作者
    double price;    // 价格
    bool isBorrowed; // 是否借出
};

// 显示操作菜单
void showMenu() {
    cout << "\n===== 图书管理系统 =====" << endl;
    cout << "1. 入库" << endl;
    cout << "2. 借书" << endl;
    cout << "3. 还书" << endl;
    cout << "4. 查询" << endl;
    cout << "5. 退出" << endl;
    cout << "======================" << endl;
}

// 图书入库功能
void addBook(vector<Book>& books) {
    string name, author;
    double price;
    cout << "请输入书名：";
    cin >> name;
    cout << "请输入作者：";
    cin >> author;
    cout << "请输入价格：";
    cin >> price;
    // 创建图书对象并加入列表
    books.push_back({name, author, price, false});
    cout << "《" << name << "》已成功入库！" << endl;
}

// 图书借阅功能
void borrowBook(vector<Book>& books) {
    if (books.empty()) {
        cout << "暂无图书！" << endl;
        return;
    }
    cout << "\n图书列表：" << endl;
    for (int i = 0; i < books.size(); i++) {
        string status = books[i].isBorrowed ? "已借出" : "可借阅";
        cout << i + 1 << ". 《" << books[i].name << "》- " << status << endl;
    }
    int choice;
    cout << "\n请选择要借阅的图书序号：";
    cin >> choice;
    choice--; // 转换为数组索引（从0开始）
    if (choice >= 0 && choice < books.size()) {
        if (!books[choice].isBorrowed) {
            books[choice].isBorrowed = true;
            cout << "《" << books[choice].name << "》借阅成功！" << endl;
        } else {
            cout << "《" << books[choice].name << "》已被借出，无法借阅！" << endl;
        }
    } else {
        cout << "选择序号无效！" << endl;
    }
}

// 图书归还功能
void returnBook(vector<Book>& books) {
    if (books.empty()) {
        cout << "暂无图书！" << endl;
        return;
    }
    // 筛选出已借出的图书
    vector<Book> borrowedBooks;
    for (const auto& book : books) {
        if (book.isBorrowed) {
            borrowedBooks.push_back(book);
        }
    }
    if (borrowedBooks.empty()) {
        cout << "没有已借出的图书！" << endl;
        return;
    }
    cout << "\n已借出的图书：" << endl;
    for (int i = 0; i < borrowedBooks.size(); i++) {
        cout << i + 1 << ". 《" << borrowedBooks[i].name << "》" << endl;
    }
    int choice;
    cout << "\n请选择要归还的图书序号：";
    cin >> choice;
    choice--;
    if (choice >= 0 && choice < borrowedBooks.size()) {
        // 找到原图书列表中对应的图书并修改状态
        for (auto& book : books) {
            if (book.name == borrowedBooks[choice].name) {
                book.isBorrowed = false;
                cout << "《" << book.name << "》归还成功！" << endl;
                break;
            }
        }
    } else {
        cout << "选择序号无效！" << endl;
    }
}

// 图书查询功能
void queryBook(vector<Book>& books) {
    if (books.empty()) {
        cout << "暂无图书！" << endl;
        return;
    }
    cout << "\n图书列表：" << endl;
    for (int i = 0; i < books.size(); i++) {
        cout << i + 1 << ". 《" << books[i].name << "》" << endl;
    }
    int choice;
    cout << "\n请选择要查询的图书序号：";
    cin >> choice;
    choice--;
    if (choice >= 0 && choice < books.size()) {
        Book& book = books[choice];
        cout << "\n书名：《" << book.name << "》" << endl;
        cout << "作者：" << book.author << endl;
        cout << "价格：" << book.price << "元" << endl;
        string status = book.isBorrowed ? "已借出" : "可借阅";
        cout << "状态：" << status << endl;
    } else {
        cout << "选择序号无效！" << endl;
    }
}

int main() {
    vector<Book> books; // 存储所有图书的容器
    int choice;         // 用户选择的操作序号

    while (true) {
        showMenu(); // 显示操作界面
        cout << "请输入操作序号：";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook(books);
                break;
            case 2:
                borrowBook(books);
                break;
            case 3:
                returnBook(books);
                break;
            case 4:
                queryBook(books);
                break;
            case 5:
                cout << "感谢使用，再见！" << endl;
                return 0; // 退出程序
            default:
                cout << "输入序号无效，请重新输入！" << endl;
        }
    }

    return 0;
}