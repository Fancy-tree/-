#include <stdio.h>
 
int main(int argc,char **argv)
{
    	printf("\033[;30m  hello world\033[0m\n");
	printf("\033[;31m  hello world\033[0m\n");
	printf("\033[;32m  hello world\033[0m\n");
	printf("\033[;33m  hello world\033[0m\n");
	printf("\033[;34m  hello world\033[0m\n");
	printf("\033[;35m  hello world\033[0m\n");
	printf("\033[;36m  hello world\033[0m\n");
	printf("\033[;37m  hello world\033[0m\n");

	printf("\033[40;37;5m 40;37; hello world\033[0m\n");//5m为闪烁
	printf("\033[41;37;5m 41;37; hello world\033[0m\n");
	printf("\033[42;37;5m 42;37; hello world\033[0m\n");
	printf("\033[43;37;5m 43;37; hello world\033[0m\n");
	printf("\033[44;37;5m 44;37; hello world\033[0m\n");
	printf("\033[45;37;5m 45;37; hello world\033[0m\n");
	printf("\033[46;37;5m 46;37; hello world\033[0m\n");
	printf("\033[47;37;5m 47;37; hello world\033[0m\n");
	
    return 0;
}
