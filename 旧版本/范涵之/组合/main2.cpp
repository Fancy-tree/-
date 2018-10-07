#include <stdio.h>
#include "iostream"
#include "unistd.h"
#include <string.h>

int IsRoll = 1;//是否滚动
int IsRollSG = 0;//是否滚动学生年级


void SoftInformation();
void Set();
void RollSet();
void ChooseWhatToRoll();
int GetYesOrNo (char ask[]);
int main()
{
    SoftInformation();
    int n=100;
    while(n!=0){
        Set();
      //  Lottery();
      //  Search();
        
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
        printf(" 4.抽奖项目主题信息\n");//抽奖项目信息,主题
        printf(" 0.退出设置\n");
        printf("请选择你的数字: ");
        std::cin>>n;
        while(strcmp (n,"1") && strcmp (n,"2") && strcmp (n,"3") && strcmp (n,"4") && strcmp (n,"0")){
            printf("无效字符, 再试一次 ");
            std::cin>>n;
          }
        printf("OK\n");
        
        if(strcmp (n,"1")==0){
            //抽奖人信息函数
            
        }else if(strcmp (n,"2")==0){   
            //奖项设置函数
            
        }else if(strcmp (n,"3")==0){   
            RollSet();
            
        }else if(strcmp (n,"4")==0){   
            //更改主题（抽奖项目信息）函数
            
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
        printf(" 0.退出滚动信息选择\n");
        
        printf("\033[;31;5m提示：学生姓名 学号默认滚动，你无法改变\033[0m\n");
        
        if(IsRollSG == 0) printf("*现在会被滚动的信息: 学生姓名 学号\n");
        else printf("*现在会被滚动的信息: 学生姓名 学号 年级\n");
        
        printf("请选择你的数字: ");
        std::cin>>n;
        while(strcmp (n,"1") && strcmp (n,"2")  && strcmp (n,"0")){
            printf("无效字符, 再试一次 ");
            std::cin>>n;
          }
        printf("OK\n");
        
        if(strcmp (n,"1")==0){
            if(IsRollSG == 1)printf("\033[;32;5m学生年级 已滚动\033[0m\n");
            else {
                IsRollSG = 1;
                printf("\033[;32;5m学生年级 将滚动\033[0m\n");
            }    
        }else if(strcmp (n,"2")==0){   
            if(IsRollSG == 0)printf("\033[;32;5m学生年级 已取消滚动\033[0m\n");
            else {
                IsRollSG = 0;
                printf("\033[;32;5m学生年级 将取消滚动\033[0m\n");
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
