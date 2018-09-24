#include <stdio.h>
#include <iostream>

#define max 100

typedef struct 
{
    char  Name[max];
    char   Pone[max],Ptwo[max],Pthree[max],Pfour[max],Pfive[max];
    int None;//一等奖人数
    int Ntwo;//二等奖人数
    int Nthree;//三等奖人数
    int Nfour;//其他自己设置奖项四号人数
    int Nfive;//其他自己设置奖项五号人数
}Prize;

void Try(Prize pri[],int a[]);

int main()
{
	
 Prize pri[5]=
    {
        {"阳光奖","一等奖","二等奖","三等奖","","",1,2,3,0,0},
        {"最佳气质奖","一等奖","二等奖","三等奖","","",1,2,3,0,0},
        {"最搞笑人物奖","一等奖","二等奖","三等奖","","",1,2,3,0,0},
        {"最暖笑容奖","一等奖","二等奖","三等奖","","",1,2,3,0,0},
        {"最奋斗忘我奖","一等奖","二等奖","三等奖","","",1,2,3,0,0},
    };
int a[]={1,2,3};
//printf("(%s)",pri[0].Name);
Try(pri,a);
//printf("(%s)",pri[0].Name);
 printf("%d",a[0]);

return 0;
}

void Try(Prize pri[],int a[])
{
// scanf("%s",&pri[0].Name);
//std::cin>>pri[0].Name;
// printf("%s",pri[0].Name);
scanf("%d",&a[0]);
 printf("%d",a[0]);
}
