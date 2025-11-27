#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// 图书结构体
struct Book {
    int id;           // 序号
    string title;     // 标题  
    string author;    // 作者
    bool isBorrowed;  // 是否借出
};

// 图书管理系统类
class LibrarySystem {
private:
    vector<Book> books;
    int nextId;
    
public:
    LibrarySystem() {
        nextId = 1;
    }
    
    // 显示菜单
    void showMenu() {
        cout << "===== 图书管理系统 =====" << endl;
        cout << "1. 图书入库" << endl;
        cout << "2. 借书" << endl;
        cout << "3. 还书" << endl;
        cout << "4. 查询图书" << endl;
        cout << "5. 退出系统" << endl;
        cout << "请输入选择 (1-5): ";
    }
    
    // 图书入库
    void addBook() {
        Book newBook;
        newBook.id = nextId;
        nextId++;
        
        cout << "请输入图书标题: ";
        cin.ignore();
        getline(cin, newBook.title);
        
        cout << "请输入作者: ";
        getline(cin, newBook.author);
        
        newBook.isBorrowed = false;
        
        books.push_back(newBook);
        
        cout << "图书入库成功! ID: " << newBook.id << endl;
    }
    
    // 借书
    void borrowBook() {
        if (books.empty()) {
            cout << "当前没有图书!" << endl;
            return;
        }
        
        showAllBooks();
        
        int id;
        cout << "请输入要借阅的图书ID: ";
        cin >> id;
        
        for (int i = 0; i < books.size(); i++) {
            if (books[i].id == id) {
                if (books[i].isBorrowed) {
                    cout << "这本书已经被借出了!" << endl;
                } else {
                    books[i].isBorrowed = true;
                    cout << "借书成功! 《" << books[i].title << "》" << endl;
                }
                return;
            }
        }
        
        cout << "没有找到ID为 " << id << " 的图书" << endl;
    }
    
    // 还书
    void returnBook() {
        if (books.empty()) {
            cout << "当前没有图书!" << endl;
            return;
        }
        
        showAllBooks();
        
        int id;
        cout << "请输入要归还的图书ID: ";
        cin >> id;
        
        for (int i = 0; i < books.size(); i++) {
            if (books[i].id == id) {
                if (!books[i].isBorrowed) {
                    cout << "这本书没有被借出!" << endl;
                } else {
                    books[i].isBorrowed = false;
                    cout << "还书成功! 《" << books[i].title << "》" << endl;
                }
                return;
            }
        }
        
        cout << "没有找到ID为 " << id << " 的图书" << endl;
    }
    
    // 显示所有图书
    void showAllBooks() {
        if (books.empty()) {
            cout << "当前没有图书!" << endl;
            return;
        }
        
        cout << "ID\t标题\t\t作者\t\t状态" << endl;
        cout << "----------------------------------------" << endl;
        
        for (int i = 0; i < books.size(); i++) {
            cout << books[i].id << "\t"
                 << books[i].title << "\t\t"
                 << books[i].author << "\t\t"
                 << (books[i].isBorrowed ? "已借出" : "在库") 
                 << endl;
        }
    }
    
    // 运行系统
    void run() {
        int choice;
        
        while (true) {
            showMenu();
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
                    showAllBooks();
                    break;
                case 5:
                    cout << "谢谢使用，再见!" << endl;
                    return;
                default:
                    cout << "无效选择，请重新输入!" << endl;
                    break;
            }
            
            cout << endl;
        }
    }
};

int main() 
{
    LibrarySystem library;
    library.run();
    return 0;
}