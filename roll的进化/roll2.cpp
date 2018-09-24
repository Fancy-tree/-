#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include<sys/wait.h>

int PL = 50; //显示在屏幕上的数组的长度
int ms = 100; //近似延迟的毫秒数

void roll(char word[],int len);
void PrintPL(char pl[],int L);
void delay(unsigned int xms);
int main()
{
    int len = 54;
    char word[ ]="Happy Mid Autumn Festival!  Happy Mid Autumn Festival!";

   printf("        ");
     	roll(word,len);
 

    return 0;
}








void roll(char word[],int len)//len：word[]实际的有效字符数
{
    int L=len+2;//新数组的长度
    char pl[L];
    for(int k=0; k<L; k++) pl[k]=' ';

    
    for(int j=0;j<len;j++){
        pl[L-1]=word[j];
        PrintPL(pl,L);
        for(int h=0;h<L-1;h++)
            pl[h]=pl[h+1];
     }
     	
    for(int h=0; h<1000; h++){	
 	
	 char tmp=pl[0];
	 

	 if(h!=0)
	   for(int i=0;i<L-1;i++)
		pl[i]=pl[i+1];

 	 pl[L-1]=tmp;


	  PrintPL(pl,L);

     }
   
 
    
}

void PrintPL(char pl[],int L)
{
    for(int i=L-PL;i<L;i++){
        printf("%c",pl[i]);
        fflush(stdout);
    }
    //sleep(1);
    delay(ms);
	for(int j=0;j<PL;j++)
    		printf("\b");
}


void delay(unsigned int xms)  // xms近似代表需要延时的毫秒数
{
    unsigned int x,y;
    for(x=xms;x>0;x--)
        for(y=400000;y>0;y--);
}


