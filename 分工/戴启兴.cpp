//����������ɳ齱�����������ʷ��¼ͳ��

//�������
//1.��ȡ �齱����Ϣ�ļ�������齱��������
//������ͨ������



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
	Person()//vis��ʼ��Ϊfalse
	{vis=false;}
};
Person p[50];
ifstream infile("date.txt",ios::in);//�������ڴ�ķ�ʽ���ļ�
int num=0;//��¼����

void shuru()//���ļ������ݶ��뵽�ṹ��������
{
	char ch;
	int count=0;
	while(infile.get(ch))//���ļ��е����ݽ��зֿ飨���ݿո�ָ���
	{
		if(ch==����)count++;
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
	cout<<"������Ϣ����"<<endl;
	cout<<s<<endl;
}

int Lottery()//�齱
{
	static int i;//��̬�ֲ�����
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
	{cout<<"��ȡ����"<<endl;
	exit(1);
	}
	string s1,s2,s3;
	shuru();
	int j;
	j=Lottery();
	cout<<"һ�Ƚ���Ϣ"<<p[j].name<<p[j].phone;
	getchar();
	j=Lottery();
	cout<<"���Ƚ���Ϣ"<<p[j].name<<p[j].phone;
	getchar();
	j=Lottery();
	cout<<"���Ƚ���Ϣ"<<p[j].name<<p[j].phone;
	getchar();
	return 0;
}
