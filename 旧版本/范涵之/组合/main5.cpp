#include <stdio.h>
#include "iostream"
#include "unistd.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <cctype> //判断字符串类型需要
#include <sstream>

using namespace std; //包含命名空间std（解决string未声明问题）

//**************************************张海军 输入抽奖人信息函数
struct Student{
int  num;
char name[20];
char sex[20];  //性别
int  nj;       //年级
char grjj[100];//简介
};

//**************************************肖平 奖项设置函数

#define max 100

typedef struct 
{
   char name[max];
   int num;
 
}Single;

typedef struct 
{
    char Name[max];
    Single *sp;
}Prize;

Prize pri;  
int N = 3;
int TotalPrize = 6;

int initial=0;//判断是否遵从初始设置
//int group[]={1,0,0,0,0,0};        //抽奖默认设置选择第一组

void PrizeSet();
void PrizeInfornation();    //待写
void PrizeNumber(int group[]);
void single(int group[]);
void multiple(int group[]);
void OutputInit();
void ChangePri();
    
//**************************************范涵之 滚动函数

int ms = 100; //近似延迟的毫秒数
int numdataline = 10;//候选人数

int IsRoll = 1;//是否滚动
int IsSex =0;//是否滚动学生性别
int IsNj =0;//是否滚动学生年级

typedef struct {
    char  num[100];
    char name[100];
    char  sex[100]; //性别
    char  nj[100];  //年级
    char grjj[1000];//简介
    int IsUsed;  //是否已抽中奖

}Student2;

void GetAllData(Student2 student[] );
void Roll(Student2 students[]);
unsigned int Rand(int min, int max2);//max2 为不与max重名
void delay(unsigned int xms);


//**************************************************向祯 记录函数（以及其他零零碎碎）

int InitPrize(Prize &pri); //初始化奖项设置
void InitRecord();
bool IsNum(string str); //判断字符串是否全为数字
int StrToNum(string str); //将字符串类型转换为整型
void InputTime(void);
void InputPri(int i, Prize pri);
void InputStudent(int b, Student2 students[]);
void OutputRecord(); //打印抽奖记录
int CountLines(char *filename); //统计文本行数



//**************************************************范涵之 main函数


void SoftInformation();
void Set();
void RollSet();
void ChooseWhatToRoll();
int GetYesOrNo (char ask[]);

void Lottery();
void Search();

int main()
{
    SoftInformation(); //抽奖程序介绍
    InitPrize(pri);
    InitRecord();
    
    while(1){
        Set();      //设置函数
        
        Lottery();  //抽奖函数
        OutputRecord();   //查询函数Search
        char s[]="你想退出程序吗 (y/n) ";
        if(GetYesOrNo(s)==1)
            break;
    }
    printf("程序结束\n");
}

int InitPrize(Prize &pri) //初始化奖项设置
{
    pri.sp = new Single[max];
    if(!pri.sp) exit(0);
    
    strcpy(pri.Name,"新年赢大奖啦啦啦");
    strcpy(pri.sp[0].name,"一等奖");
    strcpy(pri.sp[1].name,"二等奖");
    strcpy(pri.sp[2].name,"三等奖");
    pri.sp[0].num = 1;
    pri.sp[1].num = 2;
    pri.sp[2].num = 3;
    
    return 1;
}

void SoftInformation()
{
    printf("\033[;30;5m这是个抽奖程序\033[0m\n");
}

void Set()
{
    char n[50]="100";//即使用户输入了奇怪的字符，程序仍能正常运行
    while(n!=0){
        printf("\033[;36;5m设置:\033[0m\n");
        printf(" 1.输入抽奖人信息\n");//输入抽奖人信息
        printf(" 2.奖项设置\n");//奖项设置
        printf(" 3.候选人信息滚动\n");//候选人信息滚动
        // printf(" 4.抽奖项目主题信息\n");//抽奖项目信息,主题
        printf(" 0.退出设置\n");
        printf("请选择你的数字: ");
        std::cin>>n;
        while(strcmp (n,"1") && strcmp (n,"2") && strcmp (n,"3")  && strcmp (n,"0")){
            printf("无效字符, 再试一次 ");
            std::cin>>n;
        }
        printf("OK\n");
        
        if(strcmp (n,"1")==0){     //张海军 输入抽奖人信息函数
            int n;
            int i;
            printf("请输入总的抽奖人数\n");
            scanf("%d",&n);  //不能输字符
            numdataline = n;
            struct Student stus[n];
            
            FILE *fp;
            for(i=0;i<n;i++)
            {
                printf("请依次输入第%d个学生的学号.姓名.性别.年级.个人简介:\n",i+1);//%d不能输字符
                scanf("%d %s %s %d %s",&stus[i].num,stus[i].name,stus[i].sex,&stus[i].nj,stus[i].grjj);
            }
            
            fp=fopen("data.txt","wt+");
            for(i=0;i<n;i++)
            {
                fprintf(fp,"%d %s %s %d %s\n",stus[i].num,stus[i].name,stus[i].sex,stus[i].nj,stus[i].grjj);
            }
            fclose(fp);
            fp=fopen("data.txt","r");
            if(fp==0)
            {
                printf("can not open the file!\n");
                exit(1);
            }
            for(i=0;i<n;i++)
            {
                fscanf(fp,"%d %s %s %d %s", &stus[i].num,stus[i].name,stus[i].sex,&stus[i].nj,stus[i].grjj);
            }
            for(i=0;i<n;i++)
            {
                printf("学号:%d 姓名:%s 性别:%s 年级:%d 个人简介：%s\n", stus[i].num, stus[i].name, stus[i].sex, stus[i].nj, stus[i].grjj);  
            }
            fclose(fp);
            char txt[]="data.txt";
            if(CountLines(txt) < TotalPrize)
            {
                printf("当前抽奖候选人数小于各奖项分配人数总和，建议继续录入候选人信息或者缩减奖项分配数量\n");
            }
        }else if(strcmp (n,"2")==0){   //肖平 奖项设置函数
            PrizeSet();//奖项设置函数
        }else if(strcmp (n,"3")==0){   
            RollSet();
        }else if(strcmp (n,"0")==0){   
            break;
        }else {   
            printf("\033[;32;5m无效字符?\033[0m\n");
        }
    }
}

void RollSet()
{
    char n[50]="100";
    while(n!=0){
        printf("\033[;36;5m滚动设置:\033[0m\n");
        printf(" 1.开启候选人信息滚动\n");//开启滚动
        printf(" 2.关闭候选人信息滚动\n");//关闭滚动
        printf(" 3.选择被滚动的候选人信息\n");//选择会被滚动的信息
        printf(" 0.退出滚动设置\n");
        printf("请选择你的数字: ");
        std::cin>>n;
        while(strcmp (n,"1") && strcmp (n,"2") && strcmp (n,"3")  && strcmp (n,"0")){
            printf("无效字符, 再试一次 ");
            std::cin>>n;
          }
        printf("OK\n");
        if(strcmp (n,"1")==0){
            if(IsRoll == 1)printf("\033[;32;5m滚动已开启\033[0m\n");
            else {
                IsRoll = 1;
                printf("\033[;32;5m滚动将开启\033[0m\n");
            }    
        }else if(strcmp (n,"2")==0){   
            if(IsRoll == 0)printf("\033[;32;5m滚动已关闭\033[0m\n");
            else {
                IsRoll = 0;
                printf("\033[;32;5m滚动将关闭\033[0m\n");
            }
            
        }else if(strcmp (n,"3")==0){   
            ChooseWhatToRoll();
                
        }else if(strcmp (n,"0")==0){   
            break;
                
        }else {   
            printf("\033[;32;5m无效字符?\033[0m\n");
        }
        
    }  
    
}

void ChooseWhatToRoll()
{
    
    char n[50]="100";
    while(n!=0){
        printf("\033[;36;5m滚动信息选择:\033[0m\n");
        printf(" 1.开启滚动学生年级\n");//开启滚动学生年级
        printf(" 2.关闭滚动学生年级\n");//关闭滚动学生年级
	  printf(" 3.开启滚动学生性别\n");
        printf(" 4.关闭滚动学生性别\n");
        printf(" 0.退出滚动信息选择\n");
        
        printf("\033[;31;5m提示：学生姓名 学号默认滚动，你无法改变\033[0m\n");
        
        if(IsNj == 0 && IsSex==0) printf("*现在会被滚动的信息: 学生姓名 学号\n");
        else if(IsNj == 1 && IsSex==0)printf("*现在会被滚动的信息: 学生姓名 学号 年级\n");
 	  else if(IsNj == 0 && IsSex==1)printf("*现在会被滚动的信息: 学生姓名 学号 性别\n");
	 else if(IsNj == 1 && IsSex==1)printf("*现在会被滚动的信息: 学生姓名 学号 性别 年级\n");
        
        printf("请选择你的数字: ");
        std::cin>>n;
        while(strcmp (n,"1") && strcmp (n,"2")  && strcmp (n,"3") && strcmp (n,"4") && strcmp (n,"0")){
            printf("无效字符, 再试一次 ");
            std::cin>>n;
          }
        printf("OK\n");
        
        if(strcmp (n,"1")==0){
            if(IsNj == 1)printf("\033[;32;5m学生年级 已滚动\033[0m\n");
            else {
                IsNj = 1;
                printf("\033[;32;5m学生年级 将滚动\033[0m\n");
            }    
        }else if(strcmp (n,"2")==0){   
            if(IsNj == 0)printf("\033[;32;5m学生年级 已取消滚动\033[0m\n");
            else {
                IsNj = 0;
                printf("\033[;32;5m学生年级 将取消滚动\033[0m\n");
           	}
            
	}else if(strcmp (n,"3")==0){
		if(IsSex == 1)printf("\033[;32;5m学生性别 已滚动\033[0m\n");
            else {
                IsSex = 1;
                printf("\033[;32;5m学生性别 将滚动\033[0m\n");
            	}    
       }else if(strcmp (n,"4")==0){   
            if(IsSex == 0)printf("\033[;32;5m学生性别 已取消滚动\033[0m\n");
            else {
                IsSex = 0;
                printf("\033[;32;5m学生性别 将取消滚动\033[0m\n");
           	}
            

        }else if(strcmp (n,"0")==0){   
            break;
                
        }else {   
            printf("\033[;32;5m无效字符?\033[0m\n");
        }
        
    }
    
}


int GetYesOrNo (char ask[])
{
    char answer[50];
    while (1){
        printf("%s",ask);
        std::cin>>answer;
	//printf("%s", answer);
        if (strcmp (answer, "yes") && strcmp (answer, "no") && strcmp (answer, "y") && strcmp (answer, "n")){
            printf ("请回答 y(yes) 或 n(no).\n"); 
            continue;
        }    
        break;
    }
    return ( !strcmp(answer, "yes") || !strcmp(answer, "y") );//yes return 1
}	


void Lottery()  
{
    InputTime();                  //时间存取函数应用，读取当前时间存入文件 
    printf("已保存当前时间\n");
    
    printf("\n");
    Student2 students[numdataline];
    
    printf("抽奖开始\n");
    fflush(stdout);
    
    GetAllData(students);
    printf("%s\n",pri.Name);
    
    fflush(stdout);
    for(int i=0; i<N; i++){
        printf("%s\n",pri.sp[i].name);
        InputPri(i, pri);
        fflush(stdout);
        for(int j=0;j<pri.sp[i].num;j++){
            printf("第%d位获奖者\n",j+1);
            fflush(stdout);
            Roll(students);
            printf("\n");
        }
    }
}

//*********************************************************************肖平 奖项设置函数
void PrizeSet()
{
    //PrizeInfornation();//抽奖信息介绍
    //PrizeNumber();//奖项组数和分配人数设置函数
    OutputInit();
    char s[]="是否要改变默认抽奖信息设置？(y/n)\n";
    if(GetYesOrNo(s)==1)
    {
        ChangePri();
    }
}

//这个函数用于修改默认的抽奖信息设置
void ChangePri()
{
    string str1, str2;
    int i;
    
    TotalPrize = 0;
    printf("请输入需要设置的抽奖项目名称: \n");
    scanf("%s", pri.Name);
    printf("请输入需要设置的奖项数量: \n");
    while(1)
    {
        cin>>str1;
        if(IsNum(str1)){
            break;
        }else{
             printf("非法输入，请输入数字: \n");
        }
    }

    N = StrToNum(str1);
    char txt[]="data.txt";
    
    for(i=0; i<N; i++)
    {
        printf("请输入第%d个奖项的名称：\n", i+1);
        scanf("%s", pri.sp[i].name);
        printf("请输入给%s分配的获奖人数：\n", pri.sp[i].name);
        while(1)
        {
            cin>>str2;
            if(IsNum(str2)){
                break;
            }else{
                printf("非法输入，请输入数字: \n");
            }
        }
        pri.sp[i].num = StrToNum(str2);
        TotalPrize += pri.sp[i].num;
        if(CountLines(txt) < TotalPrize)
        {
            printf("当各奖项分配人数总和已大于前抽奖候选人数，系统将自动丢弃对%s及以后奖项的设置\n", pri.sp[i].name);
            N = i;
            printf("若对系统作出的判决不满意，请在设置下—2.奖项设置处重新设置抽奖信息\n");
            break;
        }
    }

    printf("最终的抽奖设置信息如下——\n");
    printf("抽奖项目: \n");
    printf("%s \n", pri.Name);
    printf("奖项设置：\n");
    for(i=0; i<N; i++)
    {
        printf("%s %d名\n", pri.sp[i].name, pri.sp[i].num);
    }
}

//该函数用于打印默认抽奖设置信息给用户
void OutputInit()
{
    printf("默认抽奖设置信息如下——\n");
    printf("抽奖项目: \n");
    printf("%s \n", pri.Name);
    printf("奖项设置：\n");
    printf("%s %d名, %s %d 名, %s %d名, \n",pri.sp[0].name, pri.sp[0].num, pri.sp[1].name, pri.sp[1].num, pri.sp[2].name, pri.sp[2].num);
}

bool IsNum(string str)
{
    int i ;
    for(i = 0; i != str.length(); i++)
    {
        if(!isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}

int StrToNum(string str)
{
    int num;
    stringstream ss(str);
    ss >> num;
    return num;
}

//*********************************************************************范涵之 滚动函数



void GetAllData(Student2 students[])
{
    FILE *fp;
    if((fp=fopen("data.txt","r"))==NULL){
        printf("open failed\n");
        exit(1);
    }
    
    //需要函数确定numdataline的数
    for(int i=0; i<numdataline;i++){
        fscanf(fp,"%s %s %s %s %s",students[i].num,students[i].name,students[i].sex,students[i].nj,students[i].grjj);
    }
    
    fclose(fp);
}
    
void Roll(Student2 students[])
{
    srand((unsigned int)time(NULL));
    int b;
    
    for(int i=0;i<20;i++){
        do{
            b=Rand(0, numdataline-1);
        }while(students[b].IsUsed==1);
        if(IsRoll==1){
            printf("%s",students[b].num);
            fflush(stdout);
            printf(" ");
            printf("%s",students[b].name);
            fflush(stdout);
            
            if(IsSex ==1){
                printf(" ");
                printf("%s",students[b].sex);
                fflush(stdout);
            }
            if(IsNj ==1){
                printf(" ");
                printf("%s",students[b].nj);
                fflush(stdout);
            }
            
            delay(ms);
            printf("\r");
            for(int h=0;h<40;h++){   //不知道有多少个字符
                printf(" ");
            }
            printf("\r");
        }
    }
    students[b].IsUsed=1;
    
    InputStudent(b, students);
    printf("%s",students[b].num);
    printf(" ");
    
    printf("%s",students[b].name);
    
    if(IsSex ==1){
        printf(" ");
        printf("%s",students[b].sex);
    }
    if(IsNj ==1){
        printf(" ");
        printf("%s",students[b].nj);
    }
    printf("\n");
}


unsigned int Rand(int min, int max2)
{
    return((rand()%((max2+1)-min))+min);  
}




void delay(unsigned int xms)  // xms近似代表需要延时的毫秒数
{
    unsigned int x,y;
    for(x=xms;x>0;x--)
        for(y=400000;y>0;y--);
}




//*******************************************************向祯 记录函数

void InitRecord()
{
    ofstream inFile;
    
    inFile.open("record.txt", ios::trunc);  //ios::trunc 打开一个文件，然后清空内容
    inFile.close();//关闭文件
}

void InputTime(void)
{
    ofstream inFile;
    
    inFile.open("record.txt", ios::app);  //ios::app 从文件末尾开始写
    time_t timep; 
    time (&timep); 
    inFile << "本项目抽奖开始时间： " << ctime(&timep) << "\n";
    inFile.close();//关闭文件
}

void InputPri(int i, Prize pri)
{
    ofstream inFile;
    
    inFile.open("record.txt", ios::app);  //ios::app 从文件末尾开始写
    inFile << pri.Name << " * " << pri.sp[i].name << "获得者：" << "\n";
    //inFile << pri.sp[i].name << "\n";
    inFile.close();//关闭文件
}

void InputStudent(int b, Student2 students[])
{
    ofstream inFile;
    
    inFile.open("record.txt", ios::app);  //ios::app 从文件末尾开始写
    GetAllData(students);
    
    inFile << students[b].num << " " << students[b].name << " " << students[b].sex << " " << students[b].nj << " " << students[b].grjj << "\n";
    inFile.close();//关闭文件
}

void OutputRecord() //打印抽奖记录
{
    char buffer[256];
    fstream out;
    
    out.open("record.txt",ios::in); //ios::in 读
    printf("\n");
    printf("该项目抽奖已完成，具体结果如下——\n");
    printf("\n");
    while(!out.eof())
    {
        out.getline(buffer,256,'\n');//getline(char *,int,char) 表示该行字符达到256个或遇到换行就结束
        cout<<buffer<<endl;
    }
    out.close();
    //cin.get();//cin.get() 是用来读取回车键的,如果没这一行，输出的结果一闪就消失了
}

int CountLines(char *filename) //统计文本行数
{
    ifstream ReadFile;
    int n=0;
    string tmp;
    ReadFile.open(filename,ios::in);//ios::in 表示以只读的方式读取文件
    if(ReadFile.fail())//文件打开失败:返回0
    {
        return 0;
    }
    else//文件存在
    {
        while(getline(ReadFile,tmp,'\n'))
        {
            n++;
        }
        ReadFile.close();
        return n;
    }
}
 
