#include <stdio.h>
#include "iostream"
#include "unistd.h"




void SoftInformation();
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
    int n=100;
    while(n!=0){
        printf("Set:\n");
        printf(" 1.Enter the lottery information\n");//输入抽奖人信息
        printf(" 2.Prize setting\n");//奖项设置
        printf(" 3.Candidate information scrolling\n");//候选人信息滚动
        printf(" 4.Sweepstakes Information\n");//抽奖项目信息
        printf(" 0.Exit set\n");
        printf("Please choose your number: ");
        std::cin>>n;
        while(n>=5 || n<0){
            printf("Illegal number, try again");
            std::cin>>n;
        }
        printf("OK");
        
        if(n==1){
            
            
        }else if(n==2){   
    
            
        }else if(n==3){   
    
            
        }else if(n==4){   
    
            
        }else if(n==0){   
            break;
            
        }else {   
            printf("?\n");
        }
        
    }
   
}
