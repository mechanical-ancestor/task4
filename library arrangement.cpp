#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>
#define MAX  1000
using namespace std;
void pause_clear()
{
    cout << "即将返回目录，请按任意键继续..." << endl;
    cin.ignore(numeric_limits<streamsize>::max() , '\n');
    cin.get();
    system("clear");
}
void menu()
{
	cout << "**********************" << endl;
	cout << "*******1.入库*********" << endl;
	cout << "*******2.借书*********" << endl;
	cout << "*******3.还书*********" << endl;
	cout << "*******4.查询*********" << endl;
	cout << "*******0.退出*********" << endl;
	cout << "**********************" << endl;
}
struct book {
	string name1;//书名
	string name2;//作者
	string price;//价格
	string situation;//是否借出
};
struct libriary {
	struct book narry[MAX];//限制图书数量为1000；
	int b_size = 0;        //初始化图书数量；
};
void addbook(libriary* wzc)
{
	if (wzc->b_size == MAX)
	{
		cout << "图书馆已满，无法入库。" << endl;
		return;
	}
	else
	{
		string name1;
		cout << "请输入所添加图书名称：" << endl;
		cin >> name1;
		wzc->narry[wzc->b_size].name1 = name1;
		string name2;
		cout << "请输入所添加图书的作者名称：" << endl;
		cin >> name2;
		wzc->narry[wzc->b_size].name2 = name2;
		string price;
		cout << "请输入所添加图书价格：" << endl;
		cin >> price;
		wzc->narry[wzc->b_size].price = price;
		string situation;
		cout << "所添加图书是否借出？     yes/no" << endl;
		cin >> situation;
		wzc->narry[wzc->b_size].situation = situation;
		cout << "入库成功!" << endl;
		wzc->b_size++;
	}
	pause_clear();
}
int checkbook(libriary* wzc, string name)//查找图书
{
	for (int i = 0; i < wzc->b_size; i++)
	{
		if (wzc->narry[i].name1 == name)
		{
			return i;
		}

	}
	return -1;
}
void borrowbook(libriary* wzc, string name)//借书
{
	checkbook(wzc, name);
	while (true)
	{
		cin >> name;
		if (checkbook(wzc, name) != -1)
		{
			if (wzc->narry[checkbook(wzc, name)].situation == "no")
			{
				wzc->narry[checkbook(wzc, name)].situation = "yes";//更改书籍状态
				cout << "借书成功！" << endl;
				break;
			}
			else
			{
			   cout << "该书已被借出" << endl;
			   break;
			}
		}
		else
		{
			cout << "未找到该书" << endl;

		}
	}
	pause_clear();
}
void showbook(libriary* wzc)
{
	for (int i = 0; i < wzc->b_size; i++)//显示书名及其状态
	{
		cout << "书名：" << wzc->narry[i].name1 << "\t";
		cout << "是否借出：" << wzc->narry[i].situation << "\t";
		cout << endl;
	}
}
void backbook(libriary* wzc, string name)//还书
{
	for (int i = 0; i < wzc->b_size; i++)
	{
		if (wzc->narry[i].situation == "yes")
		{
			cout << "书名：" << wzc->narry[i].name1 << "\t";
			cout<<"作者："<< wzc->narry[i].name2 << "\t";
			cout << "价格：" << wzc->narry[i].price << "\t";
			cout << "是否借出：" << wzc->narry[i].situation << "\t" << endl;
		}
	}
	cout << "请输入要归还书的名称：";
	cin >> name;
	checkbook(wzc, name);
	wzc->narry[checkbook(wzc, name)].situation = "no";
	cout << "还书成功！";
	pause_clear();
}
void exhibitbook(libriary* wzc)//展示所有书名
{
	for (int i = 0; i < wzc->b_size;i++)
	{
		cout << "书名： " << wzc->narry[i].name1 << endl;
	}
}
void searchbook(libriary* wzc, string name)//查询书
{
	checkbook(wzc, name);
	if (checkbook(wzc, name) != -1)
	{
		string answer;
		cout << "请输入要查询的该书的信息：   作者/价格/是否借出" << endl;
		cin >> answer;
		if (answer == "作者")
		{
			cout << "该书作者为：" << wzc->narry[checkbook(wzc, name)].name2 << endl;
		}
		if (answer == "价格")
		{
			cout << "该书价格为： " << wzc->narry[checkbook(wzc, name)].price << endl;
		}
		if (answer == "是否借出")
		{
			if (wzc->narry[checkbook(wzc, name)].situation == "yes")
			{
				cout << "该书已被借出" << endl;
			}
			else
			{
				cout << "该书未被借出" << endl;
			}
		}
	}
	else
	{
		cout << "未找到该书" << endl;
	}
	pause_clear();
}
int main()
{
	libriary wzc;
	int select = 0;
	wzc.b_size = 0;
	while (true)
	{
		system("clear");//清屏
		menu();       //显示菜单
		cin >> select;
		switch (select)
		{
		case 1:
		{
			addbook(&wzc);
			break;
		}
		case 2:
		{
			showbook(&wzc);
			string name;
			cout << "请输入要借出的书的名称：" << endl;
			borrowbook(&wzc,name);
			break;
		}
		case 3:
		{
			string name;
			backbook(&wzc, name);
			break;
		}
		case 4:
		{
			exhibitbook(&wzc);
			cout << "请输入要查询书的名称" << endl;
			string name;
			cin >> name;
			searchbook(&wzc, name);
			break;
		}
		case 0:           //退出菜单
		{
			return 0;
			break;
		}
		default:
			break;
		}
	}
		return 0;
}
