#include <stdio.h>
#include <string.h>
#include <unistd.h>

void roll(char* word, int len);
int main()
{
    char* word="Hello";
    int len = strlen(word);
    roll(word, len);

    
    return 0;
}


void roll(char* word, int len)
{
    int i, j;
  //  pid_t pid;
  //  if((pid = fork()) < 0)
  //      printf("fork fail");

     for(i=0;;i++){
    	printf("%s",word);
	
        fflush(stdout);
	sleep(1);
           
    	for(j=0;j<len;j++){
            printf("\b");
        }
        for(j=0;j<len;j++){
            printf(" ");
        }
        for(j=0;j<len;j++){
            printf("\b");
        }
       
        printf(" ");
        
        if(i==20){
            printf("\r");
            
        }
        
    }
    
}


