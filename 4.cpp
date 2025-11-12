#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;
struct book{
    string bookname;
    string writer;
    float price;
    string borrowing;

};
int main( ){ 
    int choice;//操作界面的选择变量
    int n,i,j,g;
    vector<book> a;//存储书的信息
    do{            //循环
cout<<"   1.入库   "<<endl;
cout<<"   2.借书   "<<endl;
cout<<"   3.还书   "<<endl;
cout<<"   4.查询   "<<endl;
cout<<"请选择序号:"<<endl;
cin >> choice;

if(choice==1){
    cout<<"请输入要入库的书本数量："<<endl;
    cin>>n;
    a.resize(n);
    for(int i=0;i<n;i++){
     cout<<"请输入第"<<i+1<<"本书的信息："<<endl;
     cout<<"bookname: "<<endl;
     cin>>a[i].bookname;                            //书本入库
         cout<<"writer: "<<endl;
         cin>>a[i].writer;
              cout<<"price: "<<endl;
               cin>>a[i].price;
                    cout<<"borrowing(YES/no): "<<endl;
                     cin>>a[i].borrowing;

    cout<<"sucess"<<endl;
    }
}else if(choice==2){
    for(int j=0;j<a.size();j++){
    cout<<a[j].bookname<<" "<<a[j].borrowing<<endl;//打印书名和借出情况
    if(a[j].borrowing=="no"){
        cout<<"你可以借出："<<j<<" "<<a[j].bookname<<endl;
    }
}

   int h;
    cout<<"请输入想借的序号和书名:"<<endl;
    cin>>h>>a[h].bookname;
    if(h>=0&&h<a.size()){         //选择未借出的书
        a[h].borrowing="YES";
        cout<<"借书成功"<<endl;
    }

 } else if(choice==3){
        for(int g=0;g<a.size();g++){
            if(a[g].borrowing=="YES")
            {                               //打印已借出的书
                cout<<"已借出的书："<<endl;
                cout<<a[g].bookname<<endl;
            }
        }
            
                cout<<"请选择要归还的书序号："<<endl;
                cin>>g;
                if(g>=0&&g<a.size()){           //选择归还哪本书
                    a[g].borrowing="no";
                    cout<<"还书成功"<<endl;
                }
            
        }else if (choice==4){
        for(i=0;i<a.size();i++){
            cout<<i<<" "<<a[i].bookname<<endl;          //打印出全部书名
        }
            cout<<"请输入想查询作者或价格或是否借出的书的序号:"<<endl;
            int s;
            cin>>s;//输入想查询的书的序号
            if(s>=0&&s<a.size()){
            cout<<a[s].writer<<" "<<a[s].price<<" "<<a[s].borrowing<<endl;
        }//输出查询结果
    }
    if(choice!=0){
        cout<<"\n按回车键继续";
        cin.ignore();            //清空界面
        cin.get();
        system("clear");
    }
}
while(choice!=0);//循环主界面
    return 0;

}

