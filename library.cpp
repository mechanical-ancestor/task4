#include<iostream>
#include<vector>
using namespace std;

class books{ //定义一个书类
public:
       books(string name,string author,int price){//构造函数初始化
          book_name=name;
          book_author=author;
          books::price=price;//添加作用域
       }
       
       string book_name;  //书名
       string book_author;//作者
       int    price;      //价格
       bool   status=true;//状态（利用布尔类型类型标识借出与否）

       void displaybook(){//成员函数：用来展示书的元素
         cout<<"书名："<<book_name<<"\t";
         cout<<"作者："<<book_author<<"\t";
         cout<<"价格"<<price<<"\t";
         cout<<(status==true?"未借出":"已借出")<<endl;
       }

   
};

class library{  //定义一个图书管理类
public:
       vector<books>book;

      void addbook(){//书入库
         string name,author;
         int price;
         cin.ignore();//清楚缓冲区，避免getline读取的缓冲区的换行符从而跳过输入书名
         cout<<"请输入您需要入库的书名"<<endl;
         getline(cin,name);//保证书名有空格的情况
         cout<<"请您输入作者"<<endl;
         getline(cin,author);
         cout<<"请您输入价格"<<endl;
         cin>>price;
         book.push_back(books(name,author,price));//利用vector成员函数达到添加的效果
         cout<<"入库成功"<<endl;
      }

      void displaylibrary(){//展示所有的书
         if(book.empty()){
            cout<<"当前图书馆中无书"<<endl;
            return;
         }
         cout<<"当前图书馆中的书如下"<<endl;
         for( auto&element:book)//element为自定义函数，book为vector容器
         element.displaybook();
      }

      void borrowbook(){//成员函数实现借书功能
         displaylibrary();
         string name;
         cout<<"请选择你需要借出的书(输入书名)"<<endl;
         cin.ignore();
         getline(cin,name);
         for(auto & element : book){
            if(element.book_name==name){
               element.status=false;
               cout<<"借书成功！"<<endl;}
            else cout<<"当前图书馆中未记录该书"<<endl;
               return ;
      }
   }

      void returnbook() {//成员函数实现还书功能
         cout<<"当前图书馆中尚未归还的书如下"<<endl;
         for( auto&element:book){//element为自定义函数，book为vector容器，for循环遍历数组
         if(!element.status)
               element.displaybook();
         }
         string name;
         cout<<"请选择您需要归还的书（输入书名）"<<endl;
         cin.ignore();
         getline(cin,name);
          for(auto & element : book){
            if(element.book_name==name){
               element.status=true;
               cout<<"还书成功！"<<endl;}
            else cout<<"当前图书馆中未记录该书!"<<endl;
               return ;
      }

      }
 
};

void menu(){//菜单
   cout<<"  ----------------"<<endl;
   cout<<"  |    1.入库    |"<<endl;
   cout<<"  |    2.借书    |"<<endl;
   cout<<"  |    3.还书    |"<<endl;
   cout<<"  |    4.查询    |"<<endl;
   cout<<"  |    0.退出    |"<<endl;
   cout<<"  ----------------"<<endl;
}



int main(){
   library libraries;//定义图书馆里类
   int choice;
   do{
      menu();
       cin>>choice;
   switch(choice){
       case 1:libraries.addbook();//入库
           break;
      case 2:libraries.borrowbook();//借书
            break;
      case 3:libraries.returnbook();//还书
            break;
      case 4:libraries.displaylibrary();//查询
            break;
      case 0://退出功能
            break;
       default:
            cout<<"输入错误，请重新输入!"<<endl;
            break;
   }
}while(choice!=0);
cout<<"退出成功感谢使用！"<<endl;

    return 0;
}