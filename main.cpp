#include <stdio.h>
#include "iostream"
#include "unistd.h"

int IsRoll = 1;//是否滚动
int IsRollSG = 0;//是否滚动学生年级


void SoftInformation();
void Set();
void RollSet();
void ChooseWhatToRoll();
int main()
{
    SoftInformation();
    int n=100;
    while(n!=0){
        Set();
        Lottery();
        Search();
        
        if(YesOrNo("Do you want to try again? (y/n) ")==0)//待确定
            break;
       
    }
    
}


void SoftInformation()
{
    printf("This is a Luky draw program");
}

void Set()
{
    double n=100;//double 使用户输入浮点数时不会立即结束程序
    while(n!=0){
        printf("Set:\n");
        printf(" 1.Enter the lottery information\n");//输入抽奖人信息
        printf(" 2.Prize setting\n");//奖项设置
        printf(" 3.Candidate information scrolling\n");//候选人信息滚动
        printf(" 4.Sweepstakes Information\n");//抽奖项目信息
        printf(" 0.Exit Set\n");
        printf("Please choose your number: ");
        std::cin>>n;
        while(n!=1 && n!=2 && n!=3 && n!=4 && n!=0){
            printf("Illegal number, try again ");
            std::cin>>n;
        }
        printf("OK\n");
        
        if(n==1){
            //抽奖人信息函数
            
        }else if(n==2){   
            //奖项设置函数
            
        }else if(n==3){   
            RollSet();
            
        }else if(n==4){   
            //更改主题（抽奖项目信息）函数
            
        }else if(n==0){   
            break;
            
        }else {   
            printf("Illegal number?\n");
        }
        
    }
   
}

void RollSet()
{
    double n=100;
    while(n!=0){
        printf("RollSet:\n");
        printf(" 1.Open candidate information roll\n");//开启滚动
        printf(" 2.Close candidate information roll\n");//关闭滚动
        printf(" 3.Choose what candidate information to roll\n");//选择会被滚动的信息
        printf(" 0.Exit RollSet\n");
        printf("Please choose your number: ");
        std::cin>>n;
        while(n!=1 && n!=2 && n!=3 && n!=0){
            printf("Illegal number, try again ");
            std::cin>>n;
        }
        printf("OK\n");
        if(n==1){
            if(IsRoll == 1)printf("Roll is already opened\n");
            else {
                IsRoll = 1;
                printf("Roll now opened\n");
            }    
        }else if(n==2){   
            if(IsRoll == 0)printf("Roll is already closed\n");
            else {
                IsRoll = 0;
                printf("Roll now closed\n");
            }
            
        }else if(n==3){   
            ChooseWhatToRoll();
                
        }else if(n==0){   
            break;
                
        }else {   
            printf("Illegal number?\n");
        }
        
    }  
    
}

void ChooseWhatToRoll()
{
    
    double n=100;
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
        while(n!=1 && n!=2 && n!=0){
            printf("Illegal number, try again ");
            std::cin>>n;
        }
        printf("OK\n");
        
        if(n==1){
            if(IsRollSG == 1)printf("Student grade is already rolling\n");
            else {
                IsRollSG = 1;
                printf("Student grade now rolling\n");
            }    
        }else if(n==2){   
            if(IsRollSG == 0)printf("Student grade rolling is already canceled\n");
            else {
                IsRollSG = 0;
                printf("Student grade rolling now canceled\n");
            }
            
        }else if(n==0){   
            break;
                
        }else {   
            printf("Illegal number?\n");
        }
        
    }
    
}
