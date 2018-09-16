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
int GetYesOrNo (char* ask);
int main()
{
    SoftInformation();
    int n=100;
    while(n!=0){
        Set();
      //  Lottery();
      //  Search();
        
        if(GetYesOrNo("Do you want to try again? (y/n) ")==0)
            break;
       
    }
    printf("End\n");
}


void SoftInformation()
{
    printf("This is a Luky draw program\n");
}

void Set()
{
    char n[10]="100";//即使用户输入了奇怪的字符，程序仍能正常运行
    while(n!=0){
        printf("Set:\n");
        printf(" 1.Enter the lottery information\n");//输入抽奖人信息
        printf(" 2.Prize setting\n");//奖项设置
        printf(" 3.Candidate information scrolling\n");//候选人信息滚动
        printf(" 4.Sweepstakes Information\n");//抽奖项目信息
        printf(" 0.Exit Set\n");
        printf("Please choose your number: ");
        std::cin>>n;
        while(strcmp (n,"1") && strcmp (n,"2") && strcmp (n,"3") && strcmp (n,"4") && strcmp (n,"0")){
            printf("Illegal number, try again ");
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
            printf("Illegal number?\n");
        }
        
    }
   
}

void RollSet()
{
    char n[10]="100";
    while(n!=0){
        printf("RollSet:\n");
        printf(" 1.Open candidate information roll\n");//开启滚动
        printf(" 2.Close candidate information roll\n");//关闭滚动
        printf(" 3.Choose what candidate information to roll\n");//选择会被滚动的信息
        printf(" 0.Exit RollSet\n");
        printf("Please choose your number: ");
        std::cin>>n;
        while(strcmp (n,"1") && strcmp (n,"2") && strcmp (n,"3")  && strcmp (n,"0")){
            printf("Illegal number, try again ");
            std::cin>>n;
          }
        printf("OK\n");
        if(strcmp (n,"1")==0){
            if(IsRoll == 1)printf("Roll is already opened\n");
            else {
                IsRoll = 1;
                printf("Roll now opened\n");
            }    
        }else if(strcmp (n,"2")==0){   
            if(IsRoll == 0)printf("Roll is already closed\n");
            else {
                IsRoll = 0;
                printf("Roll now closed\n");
            }
            
        }else if(strcmp (n,"3")==0){   
            ChooseWhatToRoll();
                
        }else if(strcmp (n,"0")==0){   
            break;
                
        }else {   
            printf("Illegal number?\n");
        }
        
    }  
    
}

void ChooseWhatToRoll()
{
    
    char n[10]="100";
    while(n!=0){
        printf("ChooseWhatToRoll:\n");
        printf(" 1.Choose roll student grade\n");//开启滚动学生年级
        printf(" 2.Cancel roll student grade\n");//关闭滚动学生年级
        printf(" 0.Exit ChooseWhatToRoll\n");
        
        printf("Student's name and ID are defaulted output,you can't change it\n");
        
        if(IsRollSG == 0) printf("Now rolling: student's name student's ID \n");
        else printf("Now rolling: student's name student's ID student grade\n");
        
        printf("Please choose your number: ");
        std::cin>>n;
        while(strcmp (n,"1") && strcmp (n,"2")  && strcmp (n,"0")){
            printf("Illegal number, try again ");
            std::cin>>n;
          }
        printf("OK\n");
        
        if(strcmp (n,"1")==0){
            if(IsRollSG == 1)printf("Student grade is already rolling\n");
            else {
                IsRollSG = 1;
                printf("Student grade now rolling\n");
            }    
        }else if(strcmp (n,"1")==0){   
            if(IsRollSG == 0)printf("Student grade rolling is already canceled\n");
            else {
                IsRollSG = 0;
                printf("Student grade rolling now canceled\n");
            }
            
        }else if(strcmp (n,"0")==0){   
            break;
                
        }else {   
            printf("Illegal number?\n");
        }
        
    }
    
}


int GetYesOrNo (char* ask)
{
    char answer[10];
    while (1){
        printf("%s",ask);
        std::cin>>answer;
	//printf("%s", answer);
        if (strcmp (answer, "yes") && strcmp (answer, "no") && strcmp (answer, "y") && strcmp (answer, "n")){
            printf ("Please answer y(yes) or n(no).\n"); 
            continue;
        }    
        break;
    }
    return ( !strcmp(answer, "yes") || !strcmp(answer, "y") );//yes return 1
}	
