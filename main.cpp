#include<iostream>
#include<string>
#include<iomanip>
#include<limits>
#define MAX 1000
using namespace std;

void clearScreen ()
{
	system("clear");
}

void pauseScreen ()
{
	cout<<"按回车键继续"<<endl;
	cin.ignore(numeric_limits<streamsize>::max(),'\n');
	cin.get();
}

void showMenu()//菜单
{
	cout << "1.入库" << endl;
	cout << "2.借书" << endl;
	cout << "3.还书" << endl;
	cout << "4.查询" << endl;
	cout << "0.退出" << endl;
}

struct Book//书籍信息
{
	string b_Name;
	string b_Author;
	int b_Price;
	int b_State;
};

struct Stack//书库信息
{
	Book bookArray[MAX];

	int b_Size;
};

void addBook(Stack* stk)//入库
{
	cout << endl;

	cout << "请输入书名：" << endl;
	string name;
	cin >> name;
	stk->bookArray[stk->b_Size].b_Name = name;
	cout << endl;

	cout << "请输入作者：" << endl;
	string author;
	cin >> author;
	stk->bookArray[stk->b_Size].b_Author = author;
	cout << endl;

	cout << "请输入价格：" << endl;
	int price;
	cin >> price;
	stk->bookArray[stk->b_Size].b_Price = price;
	cout << endl;

	int sta = 1;
	stk->bookArray[stk->b_Size].b_State = sta;

	stk->b_Size++;

	cout << endl;
	cout << "入库成功" << endl;
	pauseScreen ();
	clearScreen ();
}

void showBorrowBook(Stack* stk)//借书
{
	cout << endl;
	int num1 = 0,num2 = 0;
	for (int i = 0; i < stk->b_Size; i++)//显示所有书及其作者和状态
	{
		cout << "书名： " << left << setw(20) << stk->bookArray[i].b_Name << '\t'
			<< "作者： " << setw(20) << stk->bookArray[i].b_Author << "\t"
			<< (stk->bookArray[i].b_State == 1 ? "未借出" : "已借出") << endl;
	}

	while (true)
	{
		cout << endl;
		for(int i=0;i<stk->b_Size;i++)
		{
			if (stk->bookArray[i].b_State == 0)//判断所有书是否被借走
			{
				num2++;
			}
		}
		if (num2 == stk->b_Size)
		{
			cout << "所有书已借出" << endl;
			break;
		}
		num2 = 0;

		cout << "请输入你要借的书：" << endl;//输入要借的书
		string name;
		cin >> name;
		for (int i = 0; i < stk->b_Size; i++)
		{
			//判断输入书籍是否在书库且没被借走
			if (stk->bookArray[i].b_Name == name && stk->bookArray[i].b_State == 1)
			{
				cout << endl;
				cout << "借出成功" << endl;
				stk->bookArray[i].b_State = 0;
				break;
			}
			else
				num1++;
		}

		if (num1 == stk->b_Size)
		{
			cout << "该书已借出或请输入正确书名" << endl;
			cout << endl;
		}
		else
			break;
		num1 = 0;
	}

	pauseScreen ();
	clearScreen ();
}

void returnBook(Stack* stk)//还书
{
	int num = 0,num2=0;
	cout << "已借出的书：" << endl;//显示已借出的数
	for (int i = 0; i < stk->b_Size; i++)
	{
		if (stk->bookArray[i].b_State == 0)
		{
			cout << "书名： " << left << setw(20) << stk->bookArray[i].b_Name << '\t'
				<< "作者： " << setw(20) << stk->bookArray[i].b_Author << endl;
		}
	}
	cout << endl;

	while (true)
	{
		cout << endl;
		for (int i = 0; i < stk->b_Size; i++)
		{
			if (stk->bookArray[i].b_State == 1)//判断所有书是否已归还
			{
				num2++;
			}
		}
		if (num2 == stk->b_Size)
		{
			cout << "所有书已归还" << endl;
			break;
		}
		num2 = 0;

		cout << "请输入你要归还的书：" << endl;//输入要还的书
		string name;
		cin >> name;

		//判断要还的书是否在书库且判断状态
		for (int i = 0; i < stk->b_Size; i++)
		{
			if (stk->bookArray[i].b_Name == name && stk->bookArray[i].b_State == 0)
			{
				cout << "还书成功" << endl;
				stk->bookArray[i].b_State = 1;
				break;
			}
			else
				num++;
		}

		if (stk->b_Size == num)
		{
			cout << "请输入正确书名" << endl;
			cout << endl;
		}
		else
			break;
		num = 0;
	}
        pauseScreen ();
	clearScreen ();
	
}

void showStak(Stack stk)//查询书库
{
	cout << endl;
	for (int i = 0; i < stk.b_Size; i++)
	{
		cout << "书名： " << left << setw(20) << stk.bookArray[i].b_Name << '\t'
			<< "作者： " << setw(20) << stk.bookArray[i].b_Author << "\t"
			<<"价格：" << setw(10) <<stk.bookArray[i].b_Price<<"\t"
			<< (stk.bookArray[i].b_State == 1 ? "未借出" : "已借出") << endl;
	}
	pauseScreen ();
	clearScreen ();
}

int main()
{
	Stack stk;
	stk.b_Size = 0;

	while (true)
	{
		showMenu();
		cout << "请输入选项：" << endl;
		int select;
		cin >> select;
		switch (select)
		{
		case 1:
			addBook(&stk);//入库
			break;
		case 2:
			showBorrowBook(&stk);//借书
			break;
		case 3:
			returnBook(&stk);//还书
			break;
		case 4:
			showStak(stk);//查询
			break;
		case 0:
			pauseScreen ();//退出
			return 0;
		}
	}
}
