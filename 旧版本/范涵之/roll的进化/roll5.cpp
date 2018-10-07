#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include<stdlib.h>
#include<time.h>


int ms = 100; //近似延迟的毫秒数
int numdataline = 10;//候选人数




void roll(char word[]);
unsigned int Rand(int min, int max);
int PrintPL(char pl[],int datalen,int i);
void delay(unsigned int xms);

int main()
{
   //--------------------------------------------------------
	FILE *fp;
	if((fp=fopen("data.txt","r"))==NULL){
	 	printf("open failed\n");
		//exit();
	}	
	char tmp[1000];
	for(int i=0;i<1000;i++)tmp[i]='#';
	char num[numdataline][100];
	for(int i=0;i<numdataline;i++){
		for(int j=0;j<100;j++){
			num[i][j]='#';
		}
	}
 	char name[numdataline][100]; 
	for(int i=0;i<numdataline;i++){
		for(int j=0;j<100;j++){
			name[i][j]='#';
		}
	}
	char sex[numdataline][100]; 
	for(int i=0;i<numdataline;i++){
		for(int j=0;j<100;j++){
			sex[i][j]='#';
		}
	}
	char nj[numdataline][100]; 
	for(int i=0;i<numdataline;i++){
		for(int j=0;j<100;j++){
			nj[i][j]='#';
		}
	}
	char grjj[numdataline][1000];
	for(int i=0;i<numdataline;i++){
		for(int j=0;j<1000;j++){
			grjj[i][j]='#';
		}
	}
	int k=0;
	int j=0;
	for(int i=0; i<numdataline;i++){
		fgets(tmp,500,fp);
		
		j=0;
		k=0;
		for(;tmp[j]!=' ';j++){	
			num[i][k]=tmp[j];
			k++;	
		}

		for(;tmp[j]==' ';j++){} //忽略空格
		k=0;
		for(;tmp[j]!=' ';j++){
			name[i][k]=tmp[j];
			k++;	
		}

		for(;tmp[j]==' ';j++){} //忽略空格
		k=0;
		for(;tmp[j]!=' ';j++){		
			sex[i][k]=tmp[j];	
			k++;
		}

		for(;tmp[j]==' ';j++){} //忽略空格
		k=0;
		for(;tmp[j]!=' ';j++){			
			nj[i][k]=tmp[j];
			k++;	
		}

		for(;tmp[j]==' ';j++){} //忽略空格
		k=0;
		for(;tmp[j]!=' '&& tmp[j]!='\n';j++){
			grjj[i][k]=tmp[j];
			k++;	
		}

			
	}
	fclose(fp);
//---------------------------------------------------------------
/*
	for(int i=0;i<numdataline;i++){
		for( j=0;num[i][j]!='#';j++){
			printf("%c",num[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for(int i=0;i<numdataline;i++){
		for(j=0;name[i][j]!='#';j++){
			printf("%c",name[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for(int i=0;i<numdataline;i++){
		for( j=0;sex[i][j]!='#';j++){
			printf("%c",sex[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for(int i=0;i<numdataline;i++){
		for( j=0;nj[i][j]!='#';j++){
			printf("%c",nj[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for(int i=0;i<numdataline;i++){
		for( j=0;grjj[i][j]!='#';j++){
			printf("%c",grjj[i][j]);
		}
		printf("\n");
	}

*/

   
  	
	
	srand((unsigned int)time(NULL));

	int a, b;
	for(int i=0;i<20;i++){
		b=Rand(0, numdataline-1);
/*
		for(a=0;num[b][a]!='#';a++){
			printf("%c",num[b][a]);
			fflush(stdout);
		}
*/

		for(a=0;name[b][a]!='#';a++){
			printf("%c",name[b][a]);
			fflush(stdout);
		}
/*
		for(a=0;sex[b][a]!='#';a++){
			printf("%c",sex[b][a]);
			fflush(stdout);
		}

		for(a=0;nj[b][a]!='#';a++){
			printf("%c",nj[b][a]);
			fflush(stdout);
		}

		for(a=0;grjj[b][a]!='#';a++){
			printf("%c",grjj[b][a]);
			fflush(stdout);
		}
*/
		delay(ms);

    		for(int h=0;h<a;h++){
      		printf("\b");
			printf(" ");
			printf("\b");
   		 }		
	}

/*
  		for(j=0;num[b][j]!='#';j++){
			printf("%c",num[b][j]);
			
		}
		printf("\n");
*/
  		for(j=0;name[b][j]!='#';j++){
			printf("%c",name[b][j]);
			
		}
		printf("\n");
/*
  		for(j=0;sex[b][j]!='#';j++){
			printf("%c",sex[b][j]);
			
		}
		printf("\n");
  		for(j=0;nj[b][j]!='#';j++){
			printf("%c",nj[b][j]);
			
		}
		printf("\n");
  		for(j=0;grjj[b][j]!='#';j++){
			printf("%c",grjj[b][j]);
			
		}
		printf("\n");
*/
    

    return 0;
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


