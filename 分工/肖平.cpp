
//分配任务：完成奖项设置函数

//完成任务：
//1.完成奖项设置函数，包括单组与多组抽奖



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

int OnlyOrDefault=1;//选择单组抽奖还是多组，默认为单组，可更改
int initial=0;//判断是否遵从初始设置
    

/* 第一组为阳光奖
 * 第二组为最佳气质奖
 * 第三组为最搞笑人物奖
 * 第四组为最暖笑容奖
 * 第五组为最奋斗忘我奖
 */

void PrizeSet(Prize pri[],int group[]);
void PrizeInfornation();
void PrizeNumber(Prize pri[],int group[]);
void single(Prize pri[],int group[]);
void multiple(Prize pri[],int group[]);
void tacitiy(Prize pri[]);
void chooseNumber(Prize pri[],int num,int group[]);

int main ()
{
    int group[]={1,0,0,0,0};//抽奖默认设置选择第一组
    Prize pri[5]=
    {
        {"阳光奖","一等奖","二等奖","三等奖","","",1,2,3,0,0},
        {"最佳气质奖","一等奖","二等奖","三等奖","","",1,2,3,0,0},
        {"最搞笑人物奖","一等奖","二等奖","三等奖","","",1,2,3,0,0},
        {"最暖笑容奖","一等奖","二等奖","三等奖","","",1,2,3,0,0},
        {"最奋斗忘我奖","一等奖","二等奖","三等奖","","",1,2,3,0,0},
    };
  
   PrizeSet(pri,group);//奖项设置函数
   
   return 0;
}

void PrizeSet(Prize pri[],int group[])
{
    //PrizeInfornation();//抽奖信息介绍
    PrizeNumber(pri,group);//奖项组数和分配人数设置函数
}

/*
 * 该函数为奖项组数设置函数，基本设置有五组，每一组有三种奖项（既一二三等奖）
 * 第一组为阳光奖
 * 第二组为最佳气质奖
 * 第三组为最搞笑人物奖
 * 第四组为最暖笑容奖
 * 第五组为最奋斗忘我奖
 */



void PrizeNumber(Prize pri[],int group[])
{
    int n;
    
    printf("你选则单组抽奖还是多组抽奖\n");//你选择单组抽奖还是多组抽奖
    printf("单组选择1,多组选择2.其他输入默认初始设置: ");
    scanf("%d",&n);
    switch(n)
    {
        case 1: single(pri,group); break;//单组函数;
        case 2: multiple(pri,group); break;//多组函数;
        default:  tacitiy(pri);//默认初始设置函数;
    }
}

//这里是单组抽奖的设置函数（包括设置奖项为那一组和该组奖项人员分配）
void single(Prize pri[],int group[])
{
    int n;
    //请选择你想要的奖项名称
    printf("你选择了单组抽奖。\n");
    printf("第一组为阳光奖\n第二组为最佳气质奖\n第三组为最搞笑人物奖\n第四组为最暖笑容奖\n第五组为最奋斗忘我奖\n\n");
    printf("你想要设置的奖项为：");
    scanf("%d",&n);
    chooseNumber(pri,n,group);

}

//这是多组抽奖函数，至少选择两组，至多选择五组
void multiple(Prize pri[],int group[])
{
    int i,n,N;
    
    printf("%s名,\n",pri[0].Name);
     printf("%s\n",pri[1].Name);
     printf("%s\n",pri[2].Name);
     printf("%s\n",pri[3].Name);
     printf("%s\n\n\n",pri[4].Name);
    
     //请选择你想要的奖项名称
    printf("你选择了多组抽奖。\n");
    printf("第一组为阳光奖\n第二组为最佳气质奖\n第三组为最搞笑人物奖\n第四组为最暖笑容奖\n第五组为最奋斗忘我奖\n\n");
    printf("这里是多组抽奖，你想要参与几组(要大于或等于两组）：");
    
    scanf("%d",&n);

    printf("你想参与%d组。",n);
    for(i=1;i<=n;i++){
        OnlyOrDefault++;
        printf("第 %d 组为：",i);
        scanf("%d",&N);
        group[N-1]=1;
        
        chooseNumber(pri,N,group) ;
    }
}

//这个函数是对于用户选择的抽奖项目进行人员分配。默认设置为（一二三等奖，并为1,2,3人）
void chooseNumber(Prize pri[],int num,int group[])
{
    char question;
    int OneOrTwo;
    group[num-1]='1';
        
    
    printf("这里是对奖品个数和人员直接的分配。\n");
    printf("你正在设置第 %d 组的奖项数量和人员分配\n",num);
    //奖品个数
    printf("我们的奖品默认分为一等奖一名，二等奖两名，三等奖三名。\n");
    printf("除了一二三等奖以外，你还可以设置两个奖项名称，如若不设置则为默认。你是否要设置？\n\n");
    do{  
        printf("请回答 y or n(大小写皆可）\n");
        scanf("%s",&question);
        
    }while(question!='Y'&&question!='y'&&question!='N'&&question!='n');
    
    if(question=='y'||question=='Y'){
        initial++;
        printf("你还想要设置一个还是两个奖项？(可以输入1或者2): ");
        scanf("%d",&OneOrTwo);
       if(OneOrTwo==1){
            printf("请输入你想要设置奖项的名字: ");
            scanf("%s",&pri[num-1].Pfour);
            printf("%s",pri[num-1].Pfour);
            printf("请输入该奖项的人数：");
            scanf("%d",&pri[num-1].Nfour);
       }else{
            initial++;
            printf("请输入你想要设置奖项的第一个名字： ");
            scanf("%s",&pri[num-1].Pfour);
            printf("请输入该奖项的人数：");
            scanf("%d",&pri[num-1].Nfour);
            printf("请输入你想要设置奖项的第二个名字： ");
            scanf("%s",&pri[num-1].Pfive);
            printf("请输入该奖项的人数：");
            scanf("%d",&pri[num-1].Nfive);
       }
    }
    printf("你是否要设置该组奖项的一二三等奖的人数？(一等奖人数大于二等奖大于三等奖）\n\n ");
    do{  
             printf("请回答 y or n(大小写皆可）\n");
             scanf("%s",&question);
             
    }while(question!='Y'&&question!='y'&&question!='N'&&question!='n');
    if(question=='y'||question=='Y'){
        printf("请输入一等奖人数：");
        scanf("%d",&pri[num-1].None);
        printf("二等奖人数为：");
        scanf("%d",&pri[num-1].Ntwo);
        printf("三等奖人数为：");
        scanf("%d",&pri[num-1].Nthree);
    }
    
    printf("最后的奖项设置结果为：\n");
    switch(initial){
        case  0: 
            printf("%s %s %d名, %s %d名, %s %d名 ,\n",pri[num-1].Name,pri[num-1].Pone,pri[num-1].None,pri[num-1].Ptwo,pri[num-1].Ntwo,pri[num-1].Pthree,pri[num-1].Nthree); break;
        case  1: 
            printf("%s %s %d名, %s %d名, %s %d名, %s %d名,\n",pri[num-1].Name,pri[num-1].Pone,pri[num-1].None,pri[num-1].Ptwo,pri[num-1].Ntwo,pri[num-1].Pthree,pri[num-1].Nthree,pri[num-1].Pfour,pri[num-1].Nfour); break;
        default: 
            printf(" %s %s %d名, %s %d名, %s %d名, %s %d名, %s %d 名,\n",pri[num-1].Name,pri[num-1].Pone,pri[num-1].None,pri[num-1].Ptwo,pri[num-1].Ntwo,pri[num-1].Pthree,pri[num-1].Nthree,pri[num-1].Pfour,pri[num-1].Nfour,pri[num-1].Pfive,pri[num-1].Nfive);
     }
}

//该函数为默认设置奖项个数和人员分配
void tacitiy(Prize pri[])
{
    printf("最后的奖项设置结果为：\n");
    printf("%s %s %d名, %s %d 名,%s %d名, \n",pri[0].Name,pri[0].Pone,pri[0].None,pri[0].Ptwo,pri[0].Ntwo,pri[0].Pthree,pri[0].Nthree);
}
