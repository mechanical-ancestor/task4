#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype> // 用于 tolower

using namespace std;

// 定义 Book 结构体，包含书名、作者、价格和是否借出状态
struct Book {
    string title;   // 书名
    string author;  // 作者
    double price;   // 价格
    bool isBorrowed; // 是否已借出，true表示已借出，false表示在库
};

// 全局向量存储所有书籍
vector<Book> library;

// 打印主菜单
void printMenu() {
    cout << "\n========== 图书管理系统 ==========" << endl;
    cout << "1. 入库" << endl;
    cout << "2. 借书" << endl;
    cout << "3. 还书" << endl;
    cout << "4. 查询" << endl;
    cout << "5. 退出" << endl;
    cout << "==================================" << endl;
    cout << "请选择操作 (1-5): ";
}

// 检查书名是否已存在
bool bookExists(const string& title) {
    for (const Book& b : library) {
        if (b.title == title) {
            return true;
        }
    }
    return false;
}

// 1. 入库功能：输入书本信息并添加到库中
void addBook() {
    cout << "\n--- 入库 ---" << endl;
    string title, author;
    double price;

    cout << "请输入书名: ";
    getline(cin, title); // 使用 getline 以支持包含空格的书名

    // 检查书名是否重复
    if (bookExists(title)) {
        cout << "错误: 书名 '" << title << "' 已存在！" << endl;
        return;
    }

    cout << "请输入作者: ";
    getline(cin, author);

    cout << "请输入价格: ";
    cin >> price;
    cin.ignore(); // 清除输入缓冲区中的换行符，避免影响下一次 getline

    // 创建新书并添加到库中
    Book newBook = {title, author, price, false}; // 新入库的书默认未借出
    library.push_back(newBook);
    cout << "成功入库: 《" << title << "》 by " << author << " (¥" << price << ")" << endl;
}

// 2. 借书功能：列出所有书，选择一本未借出的书进行借出
void borrowBook() {
    cout << "\n--- 借书 ---" << endl;

    // 如果没有书，提示并返回
    if (library.empty()) {
        cout << "当前无任何书籍可借！" << endl;
        return;
    }

    // 打印所有书籍及其借出状态
    cout << "现有书籍列表：" << endl;
    int index = 1;
    vector<int> availableIndices; // 存储可借书籍的索引（从0开始）
    for (const Book& b : library) {
        cout << index << ". 《" << b.title << "》 by " << b.author
             << " - 价格: ¥" << b.price
             << " - 状态: " << (b.isBorrowed ? "已借出" : "在库") << endl;
        if (!b.isBorrowed) {
            availableIndices.push_back(index - 1); // 将实际索引存入
        }
        index++;
    }

    // 如果没有可借的书
    if (availableIndices.empty()) {
        cout << "所有书籍均已借出！" << endl;
        return;
    }

    // 让用户选择要借的书
    int choice;
    cout << "请选择要借阅的书籍编号 (输入0取消): ";
    cin >> choice;
    cin.ignore(); // 清除换行符

    if (choice == 0) {
        cout << "已取消借书操作。" << endl;
        return;
    }

    // 检查选择是否有效且对应书籍未被借出
    if (choice >= 1 && choice <= library.size()) {
        int actualIndex = choice - 1;
        if (!library[actualIndex].isBorrowed) {
            library[actualIndex].isBorrowed = true;
            cout << "成功借出: 《" << library[actualIndex].title << "》" << endl;
        } else {
            cout << "错误: 该书已借出！" << endl;
        }
    } else {
        cout << "无效的书籍编号！" << endl;
    }
}

// 3. 还书功能：列出所有已借出的书，选择一本归还
void returnBook() {
    cout << "\n--- 还书 ---" << endl;

    // 如果没有书，提示并返回
    if (library.empty()) {
        cout << "当前无任何书籍！" << endl;
        return;
    }

    // 打印所有已借出的书籍
    cout << "已借出的书籍列表：" << endl;
    int index = 1;
    vector<int> borrowedIndices; // 存储已借出书籍的索引
    for (int i = 0; i < library.size(); ++i) {
        if (library[i].isBorrowed) {
            cout << index << ". 《" << library[i].title << "》 by " << library[i].author
                 << " - 价格: ¥" << library[i].price << endl;
            borrowedIndices.push_back(i); // 存储实际索引
            index++;
        }
    }

    // 如果没有已借出的书
    if (borrowedIndices.empty()) {
        cout << "当前无任何书籍被借出！" << endl;
        return;
    }

    // 让用户选择要归还的书
    int choice;
    cout << "请选择要归还的书籍编号 (输入0取消): ";
    cin >> choice;
    cin.ignore();

    if (choice == 0) {
        cout << "已取消还书操作。" << endl;
        return;
    }

    // 检查选择是否有效
    if (choice >= 1 && choice <= borrowedIndices.size()) {
        int actualIndex = borrowedIndices[choice - 1]; // 获取实际索引
        library[actualIndex].isBorrowed = false;
        cout << "成功归还: 《" << library[actualIndex].title << "》" << endl;
    } else {
        cout << "无效的书籍编号！" << endl;
    }
}

// 4. 查询功能：打印所有书，然后允许按书名、作者或价格查询
void queryBook() {
    cout << "\n--- 查询 ---" << endl;

    // 如果没有书，提示并返回
    if (library.empty()) {
        cout << "当前无任何书籍！" << endl;
        return;
    }

    // 打印所有书籍
    cout << "所有书籍列表：" << endl;
    for (const Book& b : library) {
        cout << "《" << b.title << "》 by " << b.author
             << " - 价格: ¥" << b.price
             << " - 状态: " << (b.isBorrowed ? "已借出" : "在库") << endl;
    }

    // 提供查询选项
    cout << "\n请选择查询方式:" << endl;
    cout << "a. 按书名查询" << endl;
    cout << "b. 按作者查询" << endl;
    cout << "c. 按价格查询" << endl;
    cout << "d. 按借出状态查询" << endl;
    cout << "e. 返回主菜单" << endl;
    cout << "请输入选项 (a-e): ";

    char option;
    cin >> option;
    cin.ignore(); // 清除换行符

    switch (tolower(option)) {
        case 'a': {
            string searchTitle;
            cout << "请输入书名关键词: ";
            getline(cin, searchTitle);
            bool found = false;
            cout << "\n搜索结果：" << endl;
            for (const Book& b : library) {
                // 不区分大小写的模糊匹配
                if (b.title.find(searchTitle) != string::npos) {
                    cout << "《" << b.title << "》 by " << b.author
                         << " - 价格: ¥" << b.price
                         << " - 状态: " << (b.isBorrowed ? "已借出" : "在库") << endl;
                    found = true;
                }
            }
            if (!found) {
                cout << "未找到相关书籍。" << endl;
            }
            break;
        }
        case 'b': {
            string searchAuthor;
            cout << "请输入作者姓名: ";
            getline(cin, searchAuthor);
            bool found = false;
            cout << "\n搜索结果：" << endl;
            for (const Book& b : library) {
                if (b.author.find(searchAuthor) != string::npos) {
                    cout << "《" << b.title << "》 by " << b.author
                         << " - 价格: ¥" << b.price
                         << " - 状态: " << (b.isBorrowed ? "已借出" : "在库") << endl;
                    found = true;
                }
            }
            if (!found) {
                cout << "未找到相关书籍。" << endl;
            }
            break;
        }
        case 'c': {
            double searchPrice;
            cout << "请输入价格: ";
            cin >> searchPrice;
            cin.ignore();
            bool found = false;
            cout << "\n搜索结果：" << endl;
            for (const Book& b : library) {
                if (abs(b.price - searchPrice) < 0.01) { // 浮点数比较，使用容差
                    cout << "《" << b.title << "》 by " << b.author
                         << " - 价格: ¥" << b.price
                         << " - 状态: " << (b.isBorrowed ? "已借出" : "在库") << endl;
                    found = true;
                }
            }
            if (!found) {
                cout << "未找到价格为 ¥" << searchPrice << " 的书籍。" << endl;
            }
            break;
        }
        case 'd': {
            cout << "请选择状态 (0: 在库, 1: 已借出): ";
            int status;
            cin >> status;
            cin.ignore();
            if (status == 0 || status == 1) {
                bool targetStatus = (status == 1);
                bool found = false;
                cout << "\n搜索结果：" << endl;
                for (const Book& b : library) {
                    if (b.isBorrowed == targetStatus) {
                        cout << "《" << b.title << "》 by " << b.author
                             << " - 价格: ¥" << b.price
                             << " - 状态: " << (b.isBorrowed ? "已借出" : "在库") << endl;
                        found = true;
                    }
                }
                if (!found) {
                    cout << "未找到相关书籍。" << endl;
                }
            } else {
                cout << "无效的状态选择！" << endl;
            }
            break;
        }
        case 'e':
            cout << "返回主菜单。" << endl;
            break;
        default:
            cout << "无效选项！" << endl;
            break;
    }
}

// 主函数
int main() {
    cout << "欢迎使用图书管理系统！" << endl;

    while (true) {
        printMenu(); // 每次循环都打印菜单

        int choice;
        cin >> choice;
        cin.ignore(); // 清除换行符，防止干扰后续输入

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
                queryBook();
                break;
            case 5:
                cout << "感谢使用，再见！" << endl;
                return 0; // 退出程序
            default:
                cout << "无效选择，请输入 1-5。" << endl;
                break;
        }
    }

    return 0;
}