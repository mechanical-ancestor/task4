#include<iostream>
#include<cstring>
using namespace std;

struct Book
{
    char name[50];
    char author[50];
    float price;
    bool isBorrowed;
};

Book books[100];
int bookCount = 0;

void addBook()
{
    if(bookCount >= 100)
    {
        cout << "图书库已满，无法继续入库！" << endl;
        return;
    }
    
    Book newBook;
    cout << "请输入书名：";
    cin >> newBook.name;
    cout << "请输入作者：";
    cin >> newBook.author;
    cout << "请输入价格：";
    cin >> newBook.price;
    newBook.isBorrowed = false;
    books[bookCount++] = newBook;
    cout << "图书入库成功！" << endl;
}

void borrowBook()
{
    char bookName[50];
    cout << "请输入要借的书名：";
    cin >> bookName;
    
    for(int i = 0; i < bookCount; i++)
    {
        if(strcmp(books[i].name, bookName) == 0)
        {
            if(books[i].isBorrowed)
            {
                cout << "该书已被借出，无法重复借阅！" << endl;
            }
            else
            {
                books[i].isBorrowed = true;
                cout << "借书成功！" << endl;
            }
            return;
        }
    }
    cout << "未找到该图书！" << endl;
}

void returnBook()
{
    char bookName[50];
    cout << "请输入要还的书名：";
    cin >> bookName;
    
    for(int i = 0; i < bookCount; i++)
    {
        if(strcmp(books[i].name, bookName) == 0)
        {
            if(!books[i].isBorrowed)
            {
                cout << "该书未被借出，无需归还！" << endl;
            }
            else
            {
                books[i].isBorrowed = false;
                cout << "还书成功！" << endl;
            }
            return;
        }
    }
    cout << "未找到该图书！" << endl;
}

void queryBook()
{
    cout << "\n=====当前图书列表=====" << endl;
    for(int i = 0; i < bookCount; i++)
    {
        cout << "[" << i+1 << "]书名：" << books[i].name 
             << "|作者：" << books[i].author 
             << "|价格：" << books[i].price 
             << "|状态：" << (books[i].isBorrowed ? "已借出" : "未借出") << endl;
    }
    cout << "=========================" << endl;
}

void showMenu()
{
    cout << "\n=====图书管理系统=====" << endl;
    cout << "1.入库" << endl;
    cout << "2.借书" << endl;
    cout << "3.还书" << endl;
    cout << "4.查询" << endl;
    cout << "0.退出" << endl;
    cout << "请选择操作（输入数字）：";
}

int main()
{
    int choice;
    while(true)
    {
        showMenu();
        cin >> choice;
        switch(choice)
        {
            case 1: addBook(); break;
            case 2: borrowBook(); break;
            case 3: returnBook(); break;
            case 4: queryBook(); break;
            case 0:
                cout << "程序已退出！" << endl;
                return 0;
            default:
                cout << "输入错误，请重新选择！" << endl;
        }
    }
}
