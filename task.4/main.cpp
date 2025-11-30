#include <iostream>
#include <string>
using namespace std;

struct Book {
    string id;
    string name;
    int count;
};

const int MAX_BOOK = 100;
Book library[MAX_BOOK];
int bookNum = 0;

void inStock() {
    if (bookNum >= MAX_BOOK) {
        cout << "图书馆已满，无法添加新图书！" << endl;
        return;
    }

    Book newBook;
    cout << "请输入图书编号：";
    cin >> newBook.id;
    cout << "请输入图书名称：";
    cin >> newBook.name;
    cout << "请输入入库数量：";
    cin >> newBook.count;

    library[bookNum++] = newBook;
    cout << "图书入库成功！" << endl;
}

void borrowBook() {
    string bookId;
    int borrowCount;
    cout << "请输入要借的图书编号：";
    cin >> bookId;
    cout << "请输入借阅数量：";
    cin >> borrowCount;

    for (int i = 0; i < bookNum; i++) {
        if (library[i].id == bookId) {
            if (library[i].count >= borrowCount) {
                library[i].count -= borrowCount;
                cout << "借阅成功！当前《" << library[i].name << "》剩余：" << library[i].count << endl;
            } else {
                cout << "库存不足，当前《" << library[i].name << "》仅剩余：" << library[i].count << endl;
            }
            return;
        }
    }
    cout << "未找到该图书！" << endl;
}

void returnBook() {
    string bookId;
    int returnCount;
    cout << "请输入要还的图书编号：";
    cin >> bookId;
    cout << "请输入归还数量：";
    cin >> returnCount;

    for (int i = 0; i < bookNum; i++) {
        if (library[i].id == bookId) {
            library[i].count += returnCount; 
            cout << "归还成功！当前《" << library[i].name << "》剩余：" << library[i].count << endl;
            return;
        }
    }
    cout << "未找到该图书！" << endl;
}


void queryBook() {
    if (bookNum == 0) {
        cout << "图书馆暂无图书！" << endl;
        return;
    }

    cout << "===== 图书馆图书列表 =====" << endl;
    cout << "编号\t名称\t库存" << endl;
    for (int i = 0; i < bookNum; i++) {
        cout << library[i].id << "\t" << library[i].name << "\t" << library[i].count << endl;
    }
}

int main() {
    int choice;
    while (true) {
        cout << "\n===== 图书管理系统 =====" << endl;
        cout << "1. 入库" << endl;
        cout << "2. 借书" << endl;
        cout << "3. 还书" << endl;
        cout << "4. 查询" << endl;
        cout << "0. 退出" << endl;
        cout << "请选择操作：";
        cin >> choice;

        switch (choice) {
            case 1: inStock(); break;
            case 2: borrowBook(); break;
            case 3: returnBook(); break;
            case 4: queryBook(); break;
            case 0: cout << "系统已退出！" << endl; return 0;
            default: cout << "无效操作，请重新选择！" << endl;
        }
    }
}
