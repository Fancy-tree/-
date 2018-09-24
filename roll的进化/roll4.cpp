#include <stdio.h>
#include <string.h>
#include <unistd.h>


int ms = 600; //近似延迟的毫秒数
int numdataline = 3;//候选人数




void roll(char word[], int datalen);
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

   
  	//int len=47;
	//int datalen=5;
	//char word[100]="00001 00002 00003 00004 00005 00006 00007 00008";
	//roll(word,datalen);
   
     
 
    

    return 0;
}




void roll(char word[], int datalen)
{
	int i=0, k=0;
	while(word[i]!=NULL && word[i+datalen]!=NULL){ 
		k=PrintPL(word,datalen,i);
		printf("\n");
		i=k;
	}
 	
    
}

int  PrintPL(char pl[],int datalen,int i)
{
    int h=i;
    for(;pl[h]==' ';h++){}
    int k=h;
    for(;k<h+datalen;k++){
        printf("%c",pl[k]);
        fflush(stdout);
      }
    //sleep(1);
    delay(ms);
    for(int j=0;j<datalen;j++){
       printf("\b");
     }
    return k;
}


void delay(unsigned int xms)  // xms近似代表需要延时的毫秒数
{
    unsigned int x,y;
    for(x=xms;x>0;x--)
        for(y=400000;y>0;y--);
}


