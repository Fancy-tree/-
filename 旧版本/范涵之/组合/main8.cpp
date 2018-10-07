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
struct Student stus[100];
void PrintStudents(Student stus[],int n);

//**************************************肖平 奖项设置函数

#define max 100

typedef struct 
{
   char name[max];
   int num;
   char gift[max]; 
 
}Single;

typedef struct 
{
    char Name[max];
    Single *sp;
}Prize;

Prize pri;  
int N = 3;//现有奖项数
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
int numdataline ;//候选人数
int a=0;  //在候选人小于奖项数时能给出正常反应

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
int lovelyms=400;
void Lovely();

//**************************************************向祯 记录函数（以及其他零零碎碎）

int IsShowSex =0;//结果是否显示学生性别
int IsShowNj =0;//结果是否显示学生年级
int IsShowGrjj =0;//结果是否显示学生年级

int InitPrize(Prize &pri); //初始化奖项设置
void InitRecord();
bool IsNum(string str); //判断字符串是否全为数字
int StrToNum(string str); //将字符串类型转换为整型
void InputTime(void);
void InputPri(int i, Prize pri);
void InputStudent(int b, Student2 students[]);
void OutputRecord(); //打印抽奖记录
int CountLines(char *filename); //统计文本行数
void OutputOneRecord();


//**************************************************范涵之 main函数


void SoftInformation();
void Init();
void Set();
void PrintSet();
void PrizeGiftSet();
void RollSet();
void ChooseWhatToRoll();
void ChooseWhatResultToShow();
void PrintRollSet();
void Search();
int GetYesOrNo (char ask[]);

void Lottery();


int main()
{
    Init();  //程序中所有需要初始化的内容
    SoftInformation(); //抽奖程序介绍
    
    while(1){
        Set();      //设置函数        
        Lottery();  //抽奖函数
        OutputOneRecord();   //显示抽奖结果函数
        char s[]="你想退出程序吗 (y/n) ";
        if(GetYesOrNo(s)==1)
            break;
    }
    printf("程序结束\n");
}

void Init()
{
	FILE *fp;
      fp=fopen("data.txt","a");
	fclose(fp);

	InitPrize(pri);
      //InitRecord();

	char txt[]="data.txt";
	numdataline=CountLines(txt);
}



void SoftInformation()
{
    printf("*抽奖程序*\n");
    printf(">>>>即将开始<<<< \n");
   printf("(回车继续)");
   fflush(stdout);
   string str;
   //cin.ignore(100,'\n');//不这么做getline就自动跳过了（cin.ignore(a,ch)如果计数值达到 a 或者被抛弃的字符是 ch ，则cin.ignore() 函数执行终止）
   //cin.sync();//清空缓冲区
   getline(cin,str);

    printf("程序自带默认设置（方便使用）\n");
    PrintSet();
}


void PrintSet()
{
	Lovely();
	//printf("\33[s");
	printf("*************************************************");
	char txt[]="data.txt";
	int n=CountLines(txt);
	PrintStudents(stus,n);
      
  	OutputInit();

	PrintRollSet();
	
	printf("*************************************************\n");
	//printf("\33[u");	

}


void Set()
{
	
    char n[50]="100";//即使用户输入了奇怪的字符，程序仍能正常运行
    while(n!=0){
	  //printf("\33[2J");//清屏效果很可怕
        printf("\033[;36m设置:\033[0m\n");
        printf(" 1.录入 抽奖人信息\n");
        printf(" 2.设置 奖项奖品\n");
        printf(" 3.调整 滚动 & 抽奖结果显示格式\n\n");
        printf(" 4.查询 设置情况\n");
        printf(" 5.查询 抽奖历史记录\n\n");
        printf(" 0.退出设置(开始抽奖)\n");
	  char txt[]="data.txt";
 	  if(CountLines(txt) < TotalPrize)
          {
            printf("\033[;31m警告：当前各奖项分配人数总和(%d)已大于当前抽奖候选人数(%d)，建议继续录入候选人信息或者缩减奖项分配数量\033[0m\n",TotalPrize,CountLines(txt));
          }
	  if(N==0)printf("\033[;31m警告：没有奖项！\033[0m\n");
        printf("请选择你的数字: ");
        std::cin>>n;
        while(strcmp (n,"1") && strcmp (n,"2") && strcmp (n,"3") && strcmp (n,"4") && strcmp (n,"5")  && strcmp (n,"0")){
            printf("无效字符, 再试一次 ");
            std::cin>>n;
        }
        printf("OK\n");
        
        if(strcmp (n,"1")==0){     //张海军 输入抽奖人信息函数

		
            int i;
 		
		 FILE *fp;

		char txt[]="data.txt";
		 int n=CountLines(txt);
            
		 char s[50]="100";
   	 	while(s!=0){
			n=CountLines(txt);
			PrintStudents(stus,n);			
			printf("\033[;36m抽奖人信息设置:\033[0m\n");
			printf(" 1.添加抽奖人信息\n");
			printf(" 2.删除抽奖人信息\n");
			printf(" 3.清空抽奖人信息\n");
			printf(" 0.退出\n");
			printf("请选择你的数字: ");
				
			std::cin>>s;
			while(strcmp (s,"1") && strcmp (s,"2") && strcmp (s,"3")  && strcmp (s,"0")){
			    printf("无效字符, 再试一次 ");
				cin.sync();//清空缓冲区
				cin.clear();//复位状态位
			    std::cin>>s;
			  }
			printf("OK\n");
			if(strcmp (s,"1")==0){
				printf("请输入要添加的总抽奖人数(输0退出)\n");
				if((cin>>n)==0){
					printf("\033[;31m非法输入！\033[0m\n");
					cin.sync();//清空缓冲区
					cin.clear();//复位状态位
					continue;
				}
		  		  int err=0;
		   		 for(i=0;i<n;i++)
		  		  {
		      		  printf("请依次输入第%d个学生的学号.姓名.性别.年级.个人简介:\n",i+1);
					  if((cin>>stus[i].num>>stus[i].name>>stus[i].sex>>stus[i].nj>>stus[i].grjj)==0){
						printf("\033[;31m非法输入！(学号，年级只能是数字)\033[0m\n");
						cin.sync();//清空缓冲区
						cin.clear();//复位状态位
						err=1;
						break;
					   }
		      		  //scanf("%d %s %s %d %s",&stus[i].num,stus[i].name,stus[i].sex,&stus[i].nj,stus[i].grjj);
		  		  }
		  		  if(err==1)continue;

		   		 fp=fopen("data.txt","at+");
		  		  for(i=0;i<n;i++)
		  		  {
		      		  fprintf(fp,"%d %s %s %d %s\n",stus[i].num,stus[i].name,stus[i].sex,stus[i].nj,stus[i].grjj);
		   		 }
		   		 fclose(fp);
				//n=CountLines(txt);
				//PrintStudents(stus,n);		
				printf("\033[;32m抽奖人信息已添加\033[0m\n");
			  	 
			}else if(strcmp (s,"2")==0){   
				n=CountLines(txt);
				if(n==0){
					printf("\033[;31m当前没有候选人\033[0m\n");
					continue;
				}
				FILE *fp;
				fp=fopen("data.txt","r");
				int i;
				if(fp==0)
				    {
					printf("can not open the file!\n");
			 		    printf("当前没有抽奖人\n");
					//exit(1);
				    }
				    for(i=0;i<n;i++)
				    {
					fscanf(fp,"%d %s %s %d %s", &stus[i].num,stus[i].name,stus[i].sex,&stus[i].nj,stus[i].grjj);
				    }
					printf("当前抽奖人名单：\n");
				    for(i=0;i<n;i++)
				    {
					printf("**编号: %d ** ",i+1);
					printf("学号:%d 姓名:%s 性别:%s 年级:%d 个人简介：%s\n", stus[i].num, stus[i].name, stus[i].sex, stus[i].nj, stus[i].grjj);  
				    }
				 fclose(fp);
			      printf("请输入要删除的一个抽奖人编号(输0退出)\n");
				int id;

				if((cin>>id)==0 || (id-1)>=n || (id-1)<-1){
					
					printf("\033[;31m没有此编号！\033[0m\n");
					cin.sync();//清空缓冲区
					cin.clear();//复位状态位
					continue;
				}else{
					id=id-1;
					

			   		 fp=fopen("data.txt","wt+");
			  		  for(i=0;i<n;i++)
			  		  {
				      	if(i!=id)fprintf(fp,"%d %s %s %d %s\n",stus[i].num,stus[i].name,stus[i].sex,stus[i].nj,stus[i].grjj);
			   		 }
				}
				 fclose(fp);
				//n=CountLines(txt);
				//PrintStudents(stus,n);		
				printf("\033[;32m抽奖人信息已删除\033[0m\n");

			}else if(strcmp (s,"3")==0){   
			  	ofstream inFile;
				    
				inFile.open("data.txt", ios::trunc);  //ios::trunc 打开一个文件，然后清空内容
				inFile.close();//关闭文件

				//n=CountLines(txt);
				//PrintStudents(stus,n);		
				printf("\033[;32m抽奖人信息已清空\033[0m\n");
			}else if(strcmp (s,"0")==0){   
			    break;
				
			}else {   
			    printf("\033[;32m无效字符?\033[0m\n");
			}
		
  	  }  
    
		   
		n=CountLines(txt);
		PrintStudents(stus,n);		
           
           // char txt[]="data.txt";
           // if(CountLines(txt) < TotalPrize) printf("警告：当前抽奖候选人数小于各奖项分配人数总和，建议继续录入候选人信息或者缩减奖项分配数量\n");
            
        }else if(strcmp (n,"2")==0){   //肖平 奖项设置函数
             PrizeGiftSet();
        }else if(strcmp (n,"3")==0){   
            RollSet();
        }else if(strcmp (n,"4")==0){   
            PrintSet();
        }else if(strcmp (n,"5")==0){   
            Search();
        }else if(strcmp (n,"0")==0){   
            break;
        }else {   
            printf("\033[;32m无效字符?\033[0m\n");
        }
    }
}

void PrintStudents(Student stus[],int n)
{
		FILE *fp;
		 fp=fopen("data.txt","r");
		int i;
            if(fp==0)
            {
                printf("can not open the file!\n");
 		    printf("当前没有抽奖人\n");
                exit(1);
            }
            for(i=0;i<n;i++)
            {
                fscanf(fp,"%d %s %s %d %s", &stus[i].num,stus[i].name,stus[i].sex,&stus[i].nj,stus[i].grjj);
            }
		printf("\n\033[;36m当前抽奖人名单：\033[0m\n");
            for(i=0;i<n;i++)
            {
                printf("学号:%d 姓名:%s 性别:%s 年级:%d 个人简介：%s\n", stus[i].num, stus[i].name, stus[i].sex, stus[i].nj, stus[i].grjj);  
            }
		if(n==0)printf("当前没有抽奖人\n");
         fclose(fp);

}

void PrizeGiftSet()
{
    char n[50]="100";
    while(n!=0){
	  OutputInit();
        printf("\033[;36m奖项奖品设置:\033[0m\n");
        printf(" 1.改变抽奖标题\n");
	  printf(" 2.改变现有奖项 名字 人数 奖品 顺序\n");
        printf(" 3.增加奖项\n");
        printf(" 4.减少奖项\n");
        printf(" 0.退出\n");
	 

        printf("请选择你的数字: ");
        std::cin>>n;
        while(strcmp (n,"1") && strcmp (n,"2") && strcmp (n,"3") && strcmp (n,"4") && strcmp (n,"0")){
            printf("无效字符, 再试一次 ");
            std::cin>>n;
          }
        printf("OK\n");
        if(strcmp (n,"1")==0){
            	printf("请输入抽奖项目标题: （例：新年赢大奖啦啦啦）\n");
    			scanf("%s", pri.Name);
			printf("\033[;32m标题已更改\033[0m\n");
        }else if(strcmp (n,"2")==0){   
			string str1,str2;
          		for(int i=0;i<N;i++){
				printf("**编号: %d ** ",i+1);
				printf("%s %d名  奖品:%s \n",pri.sp[i].name, pri.sp[i].num,pri.sp[i].gift);
			}
			if(N==0)printf("没有奖项！\n");
			 printf("请输入要改变的一个奖项编号(输0退出)\n");
			 while(1)
   			 {
        			cin>>str1;
        			if(IsNum(str1)){
					if(StrToNum(str1)>=0 && StrToNum(str1)<=N) break;//
					else printf("没有这个编号，再试一次 \n");
       			 }else{
            			 printf("没有这个编号，再试一次 \n");
      				 }
		  	  }
			 int chooseNum=StrToNum(str1)-1;
			if(chooseNum+1==0)continue;
				    char s[50]="100";
				    while(n!=0){
					printf("\n\033[;36m奖项一览\033[0m\n",chooseNum);
					for(int i=0;i<N;i++){
						printf("**编号: %d ** ",i+1);
						printf("%s %d名  奖品:%s \n",pri.sp[i].name, pri.sp[i].num,pri.sp[i].gift);
					}
					printf("\033[;36m**编号: %d **  奖项改动\033[0m\n",chooseNum+1);
					printf(" 1.改变奖项 名称\n");
					printf(" 2.改变奖项 人数\n"); 
					printf(" 3.改变奖项 奖品\n");
					printf(" 4.改变奖项 顺序\n");
					printf(" 0.退出\n");
					printf("\033[;31m提示：奖项顺序与抽奖顺序一致\033[0m\n");
					printf("请选择你的数字: ");
					std::cin>>s;
					while(strcmp (s,"1") && strcmp (s,"2") && strcmp (s,"3") && strcmp (s,"4")  && strcmp (s,"0")){
					    printf("无效字符, 再试一次 ");
					    std::cin>>s;
					  }
					printf("OK\n");
					if(strcmp (s,"1")==0){
					   	 printf("请输入 奖项 名称：\n");
       					 scanf("%s", pri.sp[chooseNum].name);
					}else if(strcmp (s,"2")==0){   
					    	 printf("请输入 奖项 人数：\n");
						while(1)
        					{
         					   cin>>str2;
           					   if(IsNum(str2)){
           					     break;
           					   }else{
             				 	printf("非法输入，请输入数字: \n");
         					    }
       						}
						TotalPrize += (StrToNum(str2)-pri.sp[chooseNum].num);
					      pri.sp[chooseNum].num = StrToNum(str2);
						

					}else if(strcmp (s,"3")==0){   
					   	 printf("请输入 奖项 奖品：\n");
       					 scanf("%s", pri.sp[chooseNum].gift);
				
					}else if(strcmp (s,"4")==0){   
					   	string str3;
						int i;
          					for(i=0;i<N;i++){
							printf("**编号: %d ** \n",i+1);
							printf("%s %d名  奖品:%s \n",pri.sp[i].name, pri.sp[i].num,pri.sp[i].gift);
						}
						printf("**编号: %d ** \n",i+1);
						if(N==0)printf("没有奖项！\n");
						printf("请选择该奖项的位置(输0退出)\n");
			 			while(1)
   			 			{
        						cin>>str3;
        						if(IsNum(str3)){
								if(StrToNum(str3)>=0 && StrToNum(str3)<=N+1) break;//
								else printf("没有这个编号，再试一次 \n");
       			 				}else{
            							printf("没有这个编号，再试一次 \n");
      				 				}
		  	  			}
			 			int chooseNum2=StrToNum(str3);
						if(chooseNum2==0)continue;
						chooseNum2=chooseNum2-1;

						Prize tmp;
						tmp.sp = new Single[1];
						tmp.sp[0]=pri.sp[chooseNum];
						for(int i=N;i>chooseNum2;i--){
							pri.sp[i]=pri.sp[i-1];			
						}
						pri.sp[chooseNum2]=tmp.sp[0];
						for(int i=chooseNum;i<N;i++){
							pri.sp[i]=pri.sp[i+1];			
						}
						//chooseNum=chooseNum2-1;
						break;
					}
					printf("\033[;32m该奖项已更改\033[0m\n");
				}
				    
		printf("\033[;32m该奖项已更改\033[0m\n");
            
        }else if(strcmp (n,"3")==0){   
           	ChangePri();
             printf("\033[;32m奖项已添加\033[0m\n");
        }else if(strcmp (n,"4")==0){   
			string str1;
          		for(int i=0;i<N;i++){
				printf("**编号: %d ** ",i+1);
				printf("%s %d名  奖品:%s \n",pri.sp[i].name, pri.sp[i].num,pri.sp[i].gift);
			}
			if(N==0)printf("没有奖项！\n");
			 printf("请输入要删除的一个奖项编号(输0退出)\n");
			 while(1)
   			 {
        			cin>>str1;
        			if(IsNum(str1)){
					if(StrToNum(str1)>=0 && StrToNum(str1)<=N) break;//
					else printf("没有这个编号，再试一次 \n");
       			 }else{
            			 printf("没有这个编号，再试一次 \n");
      				 }
		  	  }
			 int chooseNum=StrToNum(str1);
			if(chooseNum==0)continue;
			TotalPrize = TotalPrize-pri.sp[chooseNum-1].num;

			N=N-1;
			for(int i=chooseNum-1;i<N;i++){
					//strcpy(pri[i].name,pri[i+1].name);
					//strcpy(pri[i].gift,pri[i+1].gift);
					
					pri.sp[i]=pri.sp[i+1];
					
			}
			printf("\033[;32m奖项已删除\033[0m\n");
            
        }else if(strcmp (n,"0")==0){  
		 OutputInit();
            break;
                
        }else {   
            printf("\033[;32m无效字符?\033[0m\n");
        }
        
    }  
}


void RollSet()
{
    char n[50]="100";
    while(n!=0){
	  PrintRollSet();
        printf("\033[;36m滚动 & 抽奖结果设置:\033[0m\n");
        printf(" 1.开启滚动\n");//开启滚动
        printf(" 2.关闭滚动\n");//关闭滚动
 	  printf(" \n");
        printf(" 3.滚动格式\n");//选择会被滚动的信息
	  printf(" 4.抽奖结果格式\n");
	  printf(" \n");
        printf(" 0.退出\n");
	 

        printf("请选择你的数字: ");
        std::cin>>n;
        while(strcmp (n,"1") && strcmp (n,"2") && strcmp (n,"3") && strcmp (n,"4") && strcmp (n,"0")){
            printf("无效字符, 再试一次 ");
            std::cin>>n;
          }
        printf("OK\n");
        if(strcmp (n,"1")==0){
            if(IsRoll == 1)printf("\033[;32m滚动已开启\033[0m\n");
            else {
                IsRoll = 1;
                printf("\033[;32m滚动将开启\033[0m\n");
            }    
        }else if(strcmp (n,"2")==0){   
            if(IsRoll == 0)printf("\033[;32m滚动已关闭\033[0m\n");
            else {
                IsRoll = 0;
                printf("\033[;32m滚动将关闭\033[0m\n");
            }
            
        }else if(strcmp (n,"3")==0){   
            ChooseWhatToRoll();
                
        }else if(strcmp (n,"4")==0){   
            ChooseWhatResultToShow();
        }else if(strcmp (n,"0")==0){  
		 PrintRollSet(); 
            break;
                
        }else {   
            printf("\033[;32m无效字符?\033[0m\n");
        }
        
    }  
    
}

void ChooseWhatToRoll()
{
    
    char n[50]="100";
    while(n!=0){
		printf("\n\033[;36m抽奖人信息滚动\033[0m\n");
		if(IsNj == 0 && IsSex==0) printf("*滚动格式: 学生姓名 学号\n");
        	else if(IsNj == 1 && IsSex==0)printf("*滚动格式: 学生姓名 学号 年级\n");
 	  	else if(IsNj == 0 && IsSex==1)printf("*滚动格式: 学生姓名 学号 性别\n");
		 else if(IsNj == 1 && IsSex==1)printf("*滚动格式: 学生姓名 学号 性别 年级\n");
        printf("\033[;36m滚动信息选择:\033[0m\n");
        printf(" 1.开启滚动学生 年级\n");
        printf(" 2.开启滚动学生 性别\n");
	  printf("\n");
	  printf(" 3.关闭滚动学生 年级\n");
        printf(" 4.关闭滚动学生 性别\n");
	 printf("\n");
        printf(" 0.退出\n");
 
        printf("\033[;31m提示：学生姓名 学号 默认滚动，你无法改变\033[0m\n");
              
        printf("请选择你的数字: ");
        std::cin>>n;
        while(strcmp (n,"1") && strcmp (n,"2")  && strcmp (n,"3") && strcmp (n,"4") && strcmp (n,"0")){
            printf("无效字符, 再试一次 ");
            std::cin>>n;
          }
        printf("OK\n");
        
        if(strcmp (n,"1")==0){
            if(IsNj == 1)printf("\033[;32m学生年级 已滚动\033[0m\n");
            else {
                IsNj = 1;
                printf("\033[;32m学生年级 将滚动\033[0m\n");
            }    
        }else if(strcmp (n,"3")==0){   
            if(IsNj == 0)printf("\033[;32m学生年级 已取消滚动\033[0m\n");
            else {
                IsNj = 0;
                printf("\033[;32m学生年级 将取消滚动\033[0m\n");
           	}
            
	}else if(strcmp (n,"2")==0){
		if(IsSex == 1)printf("\033[;32m学生性别 已滚动\033[0m\n");
            else {
                IsSex = 1;
                printf("\033[;32m学生性别 将滚动\033[0m\n");
            	}    
       }else if(strcmp (n,"4")==0){   
            if(IsSex == 0)printf("\033[;32m学生性别 已取消滚动\033[0m\n");
            else {
                IsSex = 0;
                printf("\033[;32m学生性别 将取消滚动\033[0m\n");
           	}
            

        }else if(strcmp (n,"0")==0){   
            break;
                
        }else {   
            printf("\033[;32m无效字符?\033[0m\n");
        }
        
    }
    
}

void ChooseWhatResultToShow()
{
    char n[50]="100";
    while(n!=0){
	 	 printf("\n\033[;36m抽奖结果显示格式:\033[0m\n");
		if(IsShowNj == 0 && IsShowSex==0 && IsShowGrjj==0) printf("*抽奖结果信息: 学生姓名 学号\n");
        	else if(IsShowNj == 1 && IsShowSex==0 && IsShowGrjj==0)printf("*抽奖结果信息: 学生姓名 学号 年级\n");
 	  	else if(IsShowNj == 0 && IsShowSex==1 && IsShowGrjj==0)printf("*抽奖结果信息: 学生姓名 学号 性别\n");
		else if(IsShowNj == 1 && IsShowSex==1 && IsShowGrjj==0)printf("*抽奖结果信息: 学生姓名 学号 性别 年级\n");
		else if(IsShowNj == 0 && IsShowSex==0 && IsShowGrjj==1)printf("*抽奖结果信息: 学生姓名 学号 个人简介\n");
		else if(IsShowNj == 1 && IsShowSex==0 && IsShowGrjj==1)printf("*抽奖结果信息: 学生姓名 学号 年级 个人简介\n");
 	  	else if(IsShowNj == 0 && IsShowSex==1 && IsShowGrjj==1)printf("*抽奖结果信息: 学生姓名 学号 性别 个人简介\n");
		else if(IsShowNj == 1 && IsShowSex==1 && IsShowGrjj==1)printf("*抽奖结果信息: 学生姓名 学号 性别 年级 个人简介\n");
        printf("\033[;36m抽奖结果显示格式选择:\033[0m\n");
        printf(" 1.开启显示学生 年级\n");
        printf(" 2.开启显示学生 性别\n");
	  printf(" 3.开启显示学生 个人简介\n");
	  printf("\n");
        printf(" 4.关闭显示学生 年级\n");
	  printf(" 5.关闭显示学生 性别\n");
        printf(" 6.关闭显示学生 个人简介\n");
	 printf("\n");
        printf(" 0.退出\n");
   
        printf("\033[;31m提示：学生姓名 学号 默认显示，你无法改变\033[0m\n");
         printf("\033[;31m显示结果与历史记录同步\033[0m\n");
 		
        printf("请选择你的数字: ");
        std::cin>>n;
        while(strcmp (n,"1") && strcmp (n,"2")  && strcmp (n,"3") && strcmp (n,"4") && strcmp (n,"5")&& strcmp (n,"6")&& strcmp (n,"0")){
            printf("无效字符, 再试一次 ");
            std::cin>>n;
          }
        printf("OK\n");
        
        if(strcmp (n,"1")==0){
            if(IsShowNj == 1)printf("\033[;32m学生年级 已增加\033[0m\n");
            else {
                IsShowNj = 1;
                printf("\033[;32m学生年级 将增加\033[0m\n");
            }    
        }else if(strcmp (n,"4")==0){   
            if(IsShowNj == 0)printf("\033[;32m学生年级 已取消\033[0m\n");
            else {
                IsShowNj = 0;
                printf("\033[;32m学生年级 将取消\033[0m\n");
           	}
            
	}else if(strcmp (n,"2")==0){
		if(IsShowSex == 1)printf("\033[;32m学生性别 已增加\033[0m\n");
            else {
                IsShowSex = 1;
                printf("\033[;32m学生性别 将增加\033[0m\n");
            	}    
       }else if(strcmp (n,"5")==0){   
            if(IsShowSex == 0)printf("\033[;32m学生性别 已取消\033[0m\n");
            else {
                IsShowSex = 0;
                printf("\033[;32m学生性别 将取消\033[0m\n");
           	}
            

        }else if(strcmp (n,"3")==0){   
            if(IsShowGrjj == 1)printf("\033[;32m学生个人简介 已增加\033[0m\n");
            else {
                IsShowGrjj = 1;
                printf("\033[;32m学生个人简介 将增加\033[0m\n");
           	}
            

        }else if(strcmp (n,"6")==0){   
            if(IsShowGrjj == 0)printf("\033[;32m学生个人简介 已取消\033[0m\n");
            else {
                IsShowGrjj = 0;
                printf("\033[;32m学生个人简介 将取消\033[0m\n");
           	}
            

        }else if(strcmp (n,"0")==0){   
            break;
                
        }else {   
            printf("\033[;32m无效字符?\033[0m\n");
        }
        
    }
    
}


void PrintRollSet()
{
	printf("\n\033[;36m抽奖人信息滚动 & 抽奖结果显示格式:\033[0m\n");
	if(IsRoll==1){
		printf("*滚动开启\n");
		if(IsNj == 0 && IsSex==0) printf("*滚动格式: 学生姓名 学号\n");
        	else if(IsNj == 1 && IsSex==0)printf("*滚动格式: 学生姓名 学号 年级\n");
 	  	else if(IsNj == 0 && IsSex==1)printf("*滚动格式: 学生姓名 学号 性别\n");
		 else if(IsNj == 1 && IsSex==1)printf("*滚动格式: 学生姓名 学号 性别 年级\n");
	}else printf("*滚动关闭\n");

	if(IsShowNj == 0 && IsShowSex==0 && IsShowGrjj==0) printf("*抽奖结果格式: 学生姓名 学号\n");
      else if(IsShowNj == 1 && IsShowSex==0 && IsShowGrjj==0)printf("*抽奖结果格式: 学生姓名 学号 年级\n");
 	else if(IsShowNj == 0 && IsShowSex==1 && IsShowGrjj==0)printf("*抽奖结果格式: 学生姓名 学号 性别\n");
	else if(IsShowNj == 1 && IsShowSex==1 && IsShowGrjj==0)printf("*抽奖结果格式: 学生姓名 学号 性别 年级\n");
	else if(IsShowNj == 0 && IsShowSex==0 && IsShowGrjj==1)printf("*抽奖结果格式: 学生姓名 学号 个人简介\n");
	else if(IsShowNj == 1 && IsShowSex==0 && IsShowGrjj==1)printf("*抽奖结果格式: 学生姓名 学号 年级 个人简介\n");
 	else if(IsShowNj == 0 && IsShowSex==1 && IsShowGrjj==1)printf("*抽奖结果格式: 学生姓名 学号 性别 个人简介\n");
	else if(IsShowNj == 1 && IsShowSex==1 && IsShowGrjj==1)printf("*抽奖结果格式: 学生姓名 学号 性别 年级 个人简介\n");
}

void Search()
{
    char n[50]="100";
    while(n!=0){
        printf("\033[;36m记录查询:\033[0m\n");
        printf(" 1.显示抽奖历史记录\n");
        printf(" 2.清空抽奖历史记录\n");
        printf(" 0.退出\n");
        printf("请选择你的数字: ");
        std::cin>>n;
        while(strcmp (n,"1") && strcmp (n,"2")  && strcmp (n,"0")){
            printf("无效字符, 再试一次 ");
            std::cin>>n;
          }
        printf("OK\n");
        if(strcmp (n,"1")==0){
		Lovely();
		OutputRecord();
        }else if(strcmp (n,"2")==0){   
            InitRecord();
		printf("\033[;32m历史记录已清空\033[0m\n");
            
        }else if(strcmp (n,"0")==0){   
            break;
                
        }else {   
            printf("\033[;32m无效字符?\033[0m\n");
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

	printf("\33[2J");//清屏效果很可怕

    char txt[]="data.txt";
    numdataline =CountLines(txt);//通过文件行数更新候选人数
	//printf("(%d)",numdataline);

	ofstream inFile;
    
     inFile.open("recordone.txt", ios::trunc);  //ios::trunc 打开一个文件，然后清空内容,清空单次记录文件
     inFile.close();//关闭文件

                   
    
    printf("\n");
   
    printf("*抽奖开始*\n");
	printf("（当前时间已保存）\n\n"); 
	InputTime();   //时间存取函数应用，读取当前时间存入文件 
    fflush(stdout);

    Student2 students[numdataline];
    GetAllData(students);
    for(int i=0; i<numdataline;i++){
       students[i].IsUsed=0;  //每次抽奖都重置，没有候选人已抽到奖
     }
	
    printf("抽奖项目:\n\033[1;35m%s\033[0m\n\n",pri.Name);
    fflush(stdout);

	

    int a=0;  //每次抽奖都重置，没有候选人已抽到奖

    for(int i=0; i<N; i++){
        printf("\33[1;34m%s\033[0m\n",pri.sp[i].name);
	  printf("\33[1;34m奖品:%s\033[0m\n",pri.sp[i].gift);
        InputPri(i, pri);
        fflush(stdout);
        for(int j=0;j<pri.sp[i].num;j++){
            printf("第%d位获奖者",j+1);
            fflush(stdout);

		printf("(回车继续)");
		fflush(stdout);
		string str;
		if(i==0)cin.ignore(100,'\n');//不这么做getline就自动跳过了（cin.ignore(a,ch)如果计数值达到 a 或者被抛弃的字符是 ch ，则cin.ignore() 函数执行终止）
		//cin.sync();//清空缓冲区
		getline(cin,str);

		if(a!=numdataline){
			Roll(students);
			a++;
		}else{
			printf("\033[;31m没有更多的候选人了！\033[0m\n");
		} 	
            printf("\n");
        }
    }


}


//*********************************************************************肖平 奖项设置函数

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
    strcpy(pri.sp[0].gift,"海南七日游");
    strcpy(pri.sp[1].gift,"苏州三日游");
    strcpy(pri.sp[2].gift,"重师一日游");

    return 1;
}

void PrizeSet()
{
    //PrizeInfornation();//抽奖信息介绍
    //PrizeNumber();//奖项组数和分配人数设置函数
    OutputInit();
    char s[]="\n是否要改变当前抽奖信息设置？(y/n)\n";
    if(GetYesOrNo(s)==1)
    {
        ChangePri();
    }
}


void ChangePri()
{
    string str2;
 
	
	  printf("请输入新奖项的名称：\n");
        scanf("%s", pri.sp[N].name);
        printf("请输入给%s分配的获奖人数：\n", pri.sp[N].name);
        while(1)
        {
            cin>>str2;
            if(IsNum(str2)){
                break;
            }else{
                printf("非法输入，请输入数字: \n");
            }
        }
        pri.sp[N].num = StrToNum(str2);

	  printf("请输入新奖项的奖品：\n");
        scanf("%s", pri.sp[N].gift);
	
      TotalPrize += pri.sp[N].num;
	N=N+1;
   
}

//该函数用于打印默认（已有）抽奖设置信息给用户
void OutputInit()
{
    printf("\n\033[;36m当前抽奖设置信息如下——\033[0m\n");
    printf("抽奖标题: \n");
    printf("%s \n", pri.Name);
    printf("奖项设置：\n");
    //printf("%s %d名, %s %d 名, %s %d名, \n",pri.sp[0].name, pri.sp[0].num, pri.sp[1].name, pri.sp[1].num, pri.sp[2].name, pri.sp[2].num);
    for(int i=0; i<N; i++){
	printf("%s %d名  奖品:%s \n",pri.sp[i].name, pri.sp[i].num,pri.sp[i].gift);
     }
   //printf("\n");
	if(N==0)printf("没有奖项！\n");
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
    
   
    for(int i=0; i<numdataline;i++){
        fscanf(fp,"%s %s %s %s %s",students[i].num,students[i].name,students[i].sex,students[i].nj,students[i].grjj);
	//printf("(%s %s %s %s %s %d)\n",students[i].num,students[i].name,students[i].sex,students[i].nj,students[i].grjj,students[i].IsUsed);
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
	       
		 for(int h=0;h<40;h++){
                        printf("\b");//不知道有多少个字符
		        printf(" ");
                         printf("\b");//不知道有多少个字符
		 }
		
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
 	    printf("恭喜 %s \n",students[b].name);
 
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

void Lovely()
{
	srand((unsigned int)time(NULL));
	int b;
	b=Rand(0, 6);
	if(b==0) printf("一大波输出即将来袭");
	else if(b==1) printf("查询ing");
	else if(b==2) printf("努力加载");
	else if(b==3) printf("广告植入");
	else if(b==4) printf("主人你好");
	else if(b==5) printf("亲，给个好评");
	else if(b==6) printf("广告植入");
	fflush(stdout);

	delay(lovelyms);
	printf(".");
	fflush(stdout);
	delay(lovelyms);
	printf(".");
	fflush(stdout);
	delay(lovelyms);
	printf(".");
	fflush(stdout);
	delay(lovelyms);

	
	for(int h=0;h<40;h++){   
		printf("\b");
		printf(" ");
		printf("\b");
	}
	
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
    inFile << "\n**************************************\n"<< "本项目抽奖开始时间： " << ctime(&timep) << "\n";
    inFile.close();//关闭文件

    ofstream inFile2;
    
    inFile2.open("recordone.txt", ios::app);  //ios::app 从文件末尾开始写
    time (&timep); 
    inFile2 << "\n**************************************\n"<< "本项目抽奖开始时间： " << ctime(&timep) << "\n";
    inFile2.close();//关闭文件
}

void InputPri(int i, Prize pri)
{
    ofstream inFile;
    
    inFile.open("record.txt", ios::app);  //ios::app 从文件末尾开始写
    inFile << pri.Name << " * " << pri.sp[i].name<< " * " << "奖品:"<< pri.sp[i].gift << " * " <<"获得者：" << "\n";
    //inFile << pri.sp[i].name << "\n";
    inFile.close();//关闭文件

    ofstream inFile2;
    
    inFile2.open("recordone.txt", ios::app);  //ios::app 从文件末尾开始写
    inFile2 << pri.Name << " * " << pri.sp[i].name<< " * " << "奖品:"<< pri.sp[i].gift << " * " <<"获得者：" << "\n";
    //inFile << pri.sp[i].name << "\n";
    inFile2.close();//关闭文件
}

void InputStudent(int b, Student2 students[])
{
    ofstream inFile;
    
    inFile.open("record.txt", ios::app);  //ios::app 从文件末尾开始写
    GetAllData(students);
    
	if(IsShowNj == 0 && IsShowSex==0 && IsShowGrjj==0) 
	inFile << students[b].num << " " << students[b].name  << "\n";
      else if(IsShowNj == 1 && IsShowSex==0 && IsShowGrjj==0)
	inFile << students[b].num << " " << students[b].name << " "  << students[b].nj  << "\n";
 	else if(IsShowNj == 0 && IsShowSex==1 && IsShowGrjj==0)
	inFile << students[b].num << " " << students[b].name << " " << students[b].sex  << "\n";
	else if(IsShowNj == 1 && IsShowSex==1 && IsShowGrjj==0)
	inFile << students[b].num << " " << students[b].name << " " << students[b].sex << " " << students[b].nj << "\n";
	else if(IsShowNj == 0 && IsShowSex==0 && IsShowGrjj==1)
	inFile << students[b].num << " " << students[b].name  << students[b].grjj << "\n";
	else if(IsShowNj == 1 && IsShowSex==0 && IsShowGrjj==1)
	inFile << students[b].num << " " << students[b].name <<  " " << students[b].nj << " " << students[b].grjj << "\n";
 	else if(IsShowNj == 0 && IsShowSex==1 && IsShowGrjj==1)
	inFile << students[b].num << " " << students[b].name << " " << students[b].sex <<  " " << students[b].grjj << "\n";
	else if(IsShowNj == 1 && IsShowSex==1 && IsShowGrjj==1)
	inFile << students[b].num << " " << students[b].name << " " << students[b].sex << " " << students[b].nj << " " << students[b].grjj << "\n";

    //inFile << students[b].num << " " << students[b].name << " " << students[b].sex << " " << students[b].nj << " " << students[b].grjj << "\n";
    inFile.close();//关闭文件

    ofstream inFile2;
    
    inFile2.open("recordone.txt", ios::app);  //ios::app 从文件末尾开始写
    GetAllData(students);
    	

	if(IsShowNj == 0 && IsShowSex==0 && IsShowGrjj==0) 
	inFile2 << students[b].num << " " << students[b].name  << "\n";
      else if(IsShowNj == 1 && IsShowSex==0 && IsShowGrjj==0)
	inFile2 << students[b].num << " " << students[b].name << " "  << students[b].nj  << "\n";
 	else if(IsShowNj == 0 && IsShowSex==1 && IsShowGrjj==0)
	inFile2 << students[b].num << " " << students[b].name << " " << students[b].sex  << "\n";
	else if(IsShowNj == 1 && IsShowSex==1 && IsShowGrjj==0)
	inFile2 << students[b].num << " " << students[b].name << " " << students[b].sex << " " << students[b].nj << "\n";
	else if(IsShowNj == 0 && IsShowSex==0 && IsShowGrjj==1)
	inFile2 << students[b].num << " " << students[b].name  << students[b].grjj << "\n";
	else if(IsShowNj == 1 && IsShowSex==0 && IsShowGrjj==1)
	inFile2 << students[b].num << " " << students[b].name <<  " " << students[b].nj << " " << students[b].grjj << "\n";
 	else if(IsShowNj == 0 && IsShowSex==1 && IsShowGrjj==1)
	inFile2 << students[b].num << " " << students[b].name << " " << students[b].sex <<  " " << students[b].grjj << "\n";
	else if(IsShowNj == 1 && IsShowSex==1 && IsShowGrjj==1)
	inFile2 << students[b].num << " " << students[b].name << " " << students[b].sex << " " << students[b].nj << " " << students[b].grjj << "\n";

    //inFile2 << students[b].num << " " << students[b].name << " " << students[b].sex << " " << students[b].nj << " " << students[b].grjj << "\n";
    inFile2.close();//关闭文件
}

void OutputRecord() //打印所有历史抽奖记录
{
	char buffer[256];
	fstream out;
		    
	out.open("record.txt",ios::in); //ios::in 读
	printf("\n");
	printf("\033[;36m具体结果如下——\033[0m\n");
	//printf("\n");
	int count=0;
	while(!out.eof())
	{
		out.getline(buffer,256,'\n');//getline(char *,int,char) 表示该行字符达到256个或遇到换行就结束
		cout<<buffer<<endl;
		count++;
	}
	out.close();
	if(count==1)printf("当前没有历史记录\n\n");
	//cin.get();//cin.get() 是用来读取回车键的,如果没这一行，输出的结果一闪就消失了
}

void OutputOneRecord() //打印单次抽奖记录
{
	char buffer[256];
	fstream out;
		    
	out.open("recordone.txt",ios::in); //ios::in 读
	printf("\n");
	printf("\033[;36m本次抽奖结果如下——\033[0m\n");
	
	while(!out.eof())
	{
		out.getline(buffer,256,'\n');//getline(char *,int,char) 表示该行字符达到256个或遇到换行就结束
		cout<<buffer<<endl;
		
	}
	out.close();
	//cin.get();//cin.get() 是用来读取回车键的,如果没这一行，输出的结果一闪就消失了

	ofstream inFile;
    
     inFile.open("recordone.txt", ios::trunc);  //ios::trunc 打开一个文件，然后清空内容
     inFile.close();//关闭文件
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
 
