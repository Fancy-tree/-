#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include<stdlib.h>
#include<time.h>


int ms = 100; //近似延迟的毫秒数
int numdataline = 10;//候选人数

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
		//exit();
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
    
void Roll(Student students[])
{
	srand((unsigned int)time(NULL));

	int a, b, count;
	for(int i=0;i<20;i++){
		b=Rand(0, numdataline-1);

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


