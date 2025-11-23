#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Book {
    string name, author;
    double price;
    bool borrowed = false;
};

class Lib {
    vector<Book> books;
    
public:
    void showMenu() {
        cout << "\n===== 图书管理系统 =====\n";
        cout << "1.入库 2.借书 3.还书 4.查询 5.退出\n选择: ";
    }
    
    void add() {
        Book b;
        cin.ignore();
        cout << "书名: "; getline(cin, b.name);
        cout << "作者: "; getline(cin, b.author);
        cout << "价格: "; cin >> b.price;
        books.push_back(b);
        cout << "添加成功!\n";
    }
    
    void borrow() {
        if(books.empty()) { cout << "无书!\n"; return; }
        cout << "可借书:\n";
        for(int i=0; i<books.size(); i++) {
            if(!books[i].borrowed) 
                cout << i+1 << "." << books[i].name << endl;
        }
        int c; cout << "选: "; cin >> c;
        if(c>0 && c<=books.size() && !books[c-1].borrowed) {
            books[c-1].borrowed = true;
            cout << "借书成功!\n";
        }
    }
    
    void ret() {
        if(books.empty()) { cout << "无书!\n"; return; }
        cout << "已借书:\n";
        for(int i=0; i<books.size(); i++) {
            if(books[i].borrowed) 
                cout << i+1 << "." << books[i].name << endl;
        }
        int c; cout << "选: "; cin >> c;
        if(c>0 && c<=books.size() && books[c-1].borrowed) {
            books[c-1].borrowed = false;
            cout << "还书成功!\n";
        }
    }
    
    void search() {
        if(books.empty()) { cout << "无书!\n"; return; }
        cout << "所有书:\n";
        for(int i=0; i<books.size(); i++) 
            cout << i+1 << "." << books[i].name << endl;
        int c; cout << "查看: "; cin >> c;
        if(c>0 && c<=books.size()) {
            Book &b = books[c-1];
            cout << "书名:" << b.name << " 作者:" << b.author;
            cout << " 价格:" << b.price << " 状态:" << (b.borrowed?"已借":"可借") << endl;
        }
    }
    
    void run() {
        int c;
        do {
            showMenu();
            cin >> c;
            if(c==1) add();
            else if(c==2) borrow();
            else if(c==3) ret();
            else if(c==4) search();
            else if(c==5) cout << "再见!\n";
            else cout << "错误!\n";
        } while(c != 5);
    }
};

int main() {
    Lib lib;
    lib.run();
    return 0;
}