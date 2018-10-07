#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include<stdlib.h>
#include<time.h>


int ms = 100; //近似延迟的毫秒数
int numdataline = 9;//候选人数

int IsSex =1;
int IsNj =0;


typedef struct {
	char  num[100];
	char name[100];
	char  sex[100]; //性别
	char  nj[100];       //年级
	char grjj[1000];//简介

}Student;



void GetAllData(Student student[] );
void Roll(Student students[]);
unsigned int Rand(int min, int max);
void delay(unsigned int xms);

int main()
{
	Student students[numdataline];

	GetAllData(students);
   	Roll(students);
   

    return 0;
}

void GetAllData(Student students[])
{
	FILE *fp;
	if((fp=fopen("data.txt","r"))==NULL){
	 	printf("open failed\n");
		exit(1);
	}	
	
	
	for(int i=0; i<numdataline;i++){

		fscanf(fp,"%s %s %s %s %s",students[i].num,students[i].name,students[i].sex,students[i].nj,students[i].grjj);

	}

	fclose(fp);
}
    
void Roll(Student students[])
{
	srand((unsigned int)time(NULL));
	int b;
	for(int i=0;i<20;i++){
		b=Rand(0, numdataline-1);

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


unsigned int Rand(int min, int max)
{
	return((rand()%((max+1)-min))+min);  
}




void delay(unsigned int xms)  // xms近似代表需要延时的毫秒数
{
    unsigned int x,y;
    for(x=xms;x>0;x--)
        for(y=400000;y>0;y--);
}


