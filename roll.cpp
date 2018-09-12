#include <stdio.h>
#include <unistd.h>

void roll(char* word, int n);
int main()
{
    char* word="Hello";
    roll(word, 5);
    
    return 0;
}


void roll(char* word, int n)
{
    int i, j;

     for(i=0;i<15;i++){
    	printf("%s",word);

	
        fflush(stdout);
	sleep(1);
           
    	for(j=0;j<n;j++){
            printf("\b");
        }

        printf(" ");
        
    }
    
}


