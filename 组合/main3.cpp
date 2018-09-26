#include <stdio.h>
#include "iostream"
#include "unistd.h"
#include <string.h>
#include<stdlib.h>
#include<time.h>
#include <fstream>

//**************************************张海军 输入抽奖人信息函数
struct Student{
int  num;
char name[20];
char  sex[20]; //性别
int  nj;       //年级
char grjj[100];//简介
};

//**************************************肖平 奖项设置函数

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


int initial=0;//判断是否遵从初始设置
int group[]={1,0,0,0,0};	//抽奖默认设置选择第一组

void PrizeSet(Prize pri[],int group[]);
void PrizeInfornation();
void PrizeNumber(Prize pri[],int group[]);
void single(Prize pri[],int group[]);
void multiple(Prize pri[],int group[]);
void tacitiy(Prize pri[]);
void chooseNumber(Prize pri[],int num,int group[]);
    
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

}Student2;

void GetAllData(Student2 student[] );
void Roll(Student2 students[]);
unsigned int Rand(int min, int max2);//max2 为不与max重名
void delay(unsigned int xms);
//**************************************************向祯 时间存取函数

using namespace std;

void InputTime(void);
void OutputTime(void);


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
    int n=100;
    while(n!=0){
        Set();      //设置函数
        Lottery();  //抽奖函数
        Search();   //查询函数
        
        if(GetYesOrNo("你想退出程序吗 (y/n) ")==1)
            break;
       
    }
    printf("程序结束\n");
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
       	 scanf("%d",&n);

		struct Student stus[n];

		FILE *fp;
    		for(i=0;i<n;i++)
		{
 			printf("请依次输入第%d个学生的学号.姓名.性别.年级.个人简介:\n",i+1);
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
			 printf("学号:%d 姓名:%s 性别:%s 年级:%d 个人简介：%s\n",stus[i].num,stus[i].name,stus[i].sex,stus[i].nj,stus[i].grjj);
		}
 		fclose(fp);
	
            
        }else if(strcmp (n,"2")==0){   //肖平 奖项设置函数
       
   		Prize pri[5]=
   		{
        		{"阳光奖","一等奖","二等奖","三等奖","","",1,2,3,0,0},
        		{"最佳气质奖","一等奖","二等奖","三等奖","","",1,2,3,0,0},
        		{"最搞笑人物奖","一等奖","二等奖","三等奖","","",1,2,3,0,0},
        		{"最暖笑容奖","一等奖","二等奖","三等奖","","",1,2,3,0,0},
        		{"最奋斗忘我奖","一等奖","二等奖","三等奖","","",1,2,3,0,0},
   		};
  
   		PrizeSet(pri,group);//奖项设置函数
   
            
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
	printf("\n");
	printf("抽奖开始\n");
							//滚动函数应用
	Student2 students[numdataline];

	GetAllData(students);
   	Roll(students);
							//滚动函数应用结束

 	InputTime();				//时间存取函数应用，读取当前时间存入文件 
	printf("已保存当前时间\n");

}

void Search()
{
	printf("\n");
	printf("查询函数\n");
	printf("输出保存时间 ");
	OutputTime();				//时间读取函数应用 
	printf("\n");
}


//*********************************************************************肖平 奖项设置函数
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
    
    printf("需要设置选择1.其他输入默认初始设置: ");
    scanf("%d",&n);
    switch(n)
    {
        case 1: single(pri,group); break;//单组函数;

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


//*********************************************************************范涵之 滚动函数



void GetAllData(Student2 students[])
{
	FILE *fp;
	if((fp=fopen("data.txt","r"))==NULL){
	 	printf("open failed\n");
		fflush(stdout);
		exit(1);
	}	
	char tmp[1000];
	for(int i=0;i<1000;i++)tmp[i]='#';
	//char num[numdataline][100];
	for(int i=0;i<numdataline;i++){
		for(int j=0;j<100;j++){
			students[i].num[j]='#';
		}
	}
 	//char name[numdataline][100]; 
	for(int i=0;i<numdataline;i++){
		for(int j=0;j<100;j++){
			students[i].name[j]='#';
		}
	}
	//char sex[numdataline][100]; 
	for(int i=0;i<numdataline;i++){
		for(int j=0;j<100;j++){
			students[i].sex[j]='#';
		}
	}
	//char nj[numdataline][100]; 
	for(int i=0;i<numdataline;i++){
		for(int j=0;j<100;j++){
			students[i].nj[j]='#';
		}
	}
	//char grjj[numdataline][1000];
	for(int i=0;i<numdataline;i++){
		for(int j=0;j<1000;j++){
			students[i].grjj[j]='#';
		}
	}

	int k=0;
	int j=0;
	for(int i=0; i<numdataline;i++){
		fgets(tmp,500,fp);
		
		j=0;
		k=0;
		for(;tmp[j]!=' ';j++){	
			students[i].num[k]=tmp[j];
			k++;	
		}

		for(;tmp[j]==' ';j++){} //忽略空格
		k=0;
		for(;tmp[j]!=' ';j++){
			students[i].name[k]=tmp[j];
			k++;	
		}

		for(;tmp[j]==' ';j++){} //忽略空格
		k=0;
		for(;tmp[j]!=' ';j++){		
			students[i].sex[k]=tmp[j];	
			k++;
		}

		for(;tmp[j]==' ';j++){} //忽略空格
		k=0;
		for(;tmp[j]!=' ';j++){			
			students[i].nj[k]=tmp[j];
			k++;	
		}

		for(;tmp[j]==' ';j++){} //忽略空格
		k=0;
		for(;tmp[j]!=' '&& tmp[j]!='\n';j++){
			students[i].grjj[k]=tmp[j];
			k++;	
		}

			
	}

	fclose(fp);
}
    
void Roll(Student2 students[])
{
	srand((unsigned int)time(NULL));

	int a, b, count;

	for(int i=0;i<20;i++){
		b=Rand(0, numdataline-1);
		if(IsRoll==1){
			for(a=0;students[b].num[a]!='#';a++){
				printf("%c",students[b].num[a]);
			
				fflush(stdout);
			}
			printf(" ");
			count=a+1;
		
			for(a=0;students[b].name[a]!='#';a++){
				printf("%c",students[b].name[a]);
				fflush(stdout);
			}

			count=count+a;


			if(IsSex ==1){
				printf(" ");
				for(a=0;students[b].sex[a]!='#';a++){
					printf("%c",students[b].sex[a]);
					fflush(stdout);
				}
				count=count+a+1;
			}
			if(IsNj ==1){
				printf(" ");
				for(a=0;students[b].nj[a]!='#';a++){
					printf("%c",students[b].nj[a]);
					fflush(stdout);
				}
				count=count+a+1;
			}


			delay(ms);

	    		for(int h=0;h<count;h++){
	      		printf("\b");
				printf(" ");
				printf("\b");
	   		 }		
		}	
	}

		int j=0;
		for(j=0;students[b].num[j]!='#';j++){
			printf("%c",students[b].num[j]);
			
		}
		printf(" ");
  		for(j=0;students[b].name[j]!='#';j++){
			printf("%c",students[b].name[j]);
			
		}
		


		if(IsSex ==1){
			printf(" ");
			for(j=0;students[b].sex[j]!='#';j++){
				printf("%c",students[b].sex[j]);
			}
		}
		if(IsNj ==1){
			printf(" ");
			for(j=0;students[b].nj[j]!='#';j++){
				printf("%c",students[b].nj[j]);
			}
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




//*******************************************************向祯 时间存取函数

void InputTime(void)

{
    ofstream OutFile("Time.txt"); //利用构造函数创建txt文本，并且打开该文本
    time_t timep; 
    time (&timep); 
    OutFile << ctime(&timep);  //写入Time.txt文件
    OutFile.close(); //关闭Time.txt文件
}

void OutputTime(void)
{
    ifstream readFile("Time.txt");
    char temp[1024] = {0};
    readFile.getline(temp, 25);
    //可以输出空格，遇到delim符号才截止。 最后一个参数0表示文本框遇到空字符（ASCLL码为32，文本框不可能有空字符）截止符。不加第三个参数0时，表示'\n'为截止符('\n'也是换行符)
    cout << temp << endl;
    //system("PAUSE");
}


