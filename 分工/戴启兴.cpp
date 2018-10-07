//分配任务：完成抽奖函数，完成历史记录统计

//完成任务：
//1.读取 抽奖人信息文件，随机抽奖，输出结果
//但不能通过编译



#include<iostream>
#include<fstream>
#include<string.h>
//#include<conio.h>

using namespace std;

struct Person
{
	string name;
	string id;
	string phone;
	bool vis;
	Person()//vis初始化为false
	{vis=false;}
};
Person p[50];
ifstream infile("date.txt",ios::in);//以输入内存的方式打开文件
int num=0;//记录人数

void shuru()//将文件的数据读入到结构体数组中
{
	char ch;
	int count=0;
	while(infile.get(ch))//把文件中的数据进行分块（依据空格分隔）
	{
		if(ch==‘’)count++;
		if(count%3==1)
		p[count/3].name+=ch;
		if(count%3==2)
		p[cout/3].id+=ch;
		else if(count%3==0)
		p[count/3].phone+=ch;
	}
	num=count/3;
	infile.close();
}

void shuchu()
{
	char c;
	string s;
	while(infile.get(c))
	{s+=c;}
	cout<<"所有信息如下"<<endl;
	cout<<s<<endl;
}

int Lottery()//抽奖
{
	static int i;//静态局部变量
	while(!_kbhit())
	{
		i=rand()%num;
		while(p[i].vis)
		{
			i=rand()%num;
			if(!p[i].vis)break;
		}
		cout<<p[i].id<<endl;
		}
	cout<<p[i].id<<endl;
	p[i].vis=true;
	getchar();
	return i;
}
 
int main()
{
	if(!infile)
	{cout<<"读取有误"<<endl;
	exit(1);
	}
	string s1,s2,s3;
	shuru();
	int j;
	j=Lottery();
	cout<<"一等奖信息"<<p[j].name<<p[j].phone;
	getchar();
	j=Lottery();
	cout<<"二等奖信息"<<p[j].name<<p[j].phone;
	getchar();
	j=Lottery();
	cout<<"三等奖信息"<<p[j].name<<p[j].phone;
	getchar();
	return 0;
}
