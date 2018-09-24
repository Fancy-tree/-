#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

#define MAX_NUM 9999 

//定义保存人名和电话的数据结构 
struct Person 
{ 
char name[20]; 
char telno[15]; 
char award; 
}; 

int num = 0; //统计人数 
FILE *fp; //文件指针 
Person persons[MAX_NUM]; //定义数组 

int awarder_1[1] = {-1}; //一等奖 
int awarder_2[2] = {-1, -1}; //二等奖 
int awarder_3[5] = {-1, -1, -1, -1, -1};//三等奖 

//读取文件 
void readdata() 
{ 
int i = 0; //数组下标 
Person person; 
//文件打开 
fp = fopen("data.txt", "r"); 
if (fp == NULL) 
{ 
printf("打开文件data.txt失败!\n"); 
return; 
} 
//当文件不为空 
while (!feof(fp)) 
{ 
num ++; 
fscanf(fp, "%s", person.telno); 
fscanf(fp, "%s", person.name); 
person.award = 'F'; 
persons[i++] = person; 
} 
} 

//初始化标识 
void init() 
{ 
for(int i = 0; i < num; i++) 
{ 
persons[i].award = 'F'; 
} 
} 

//显示单个中奖信息 
void info( int i) 
{ 
printf("手机号码: %s 姓名: %s\n", persons[i].telno, persons[i].name); 
} 

void main() 
{ 
char again = 'Y'; 
//读取文件 
readdata(); 

printf("简单抽奖程序\n"); 
srand((long)time(0)); 

while(again == 'Y' || again == 'y') 
{ 
//初始化标识 
init(); 

printf("\n开始抽第一等奖(1名)，按任意键开始...\n"); 
getchar(); 
awarder_1[0] = abs(rand() % num); 
while (persons[awarder_1[0]].award == 'T') 
{ 
awarder_1[0] = rand() % num; 
} 
persons[awarder_1[0]].award = 'T'; 

info(awarder_1[0]); 

printf("\n开始抽第二等奖(2名)\n"); 
for (int i = 0; i < 2; i++) 
{ 
printf("\n第%d个二等奖,按任意键开始...\n", i+1); 
getchar(); 
awarder_2[i] = rand() % num; 
while (persons[awarder_2[i]].award == 'T') 
{ 
awarder_2[i] = rand() % num; 
} 
persons[awarder_2[i]].award = 'T'; 
info(awarder_2[i]); 
} 

printf("\n\n开始抽第三等奖(5名)\n"); 
for (i = 0; i < 5; i++) 
{ 
printf("\n第%d个三等奖,按任意键开始...\n", i + 1); 
getchar(); 

awarder_3[i] = rand() % num; 
while (persons[awarder_3[i]].award == 'T') 
{ 
awarder_3[i] = rand() % num; 
} 
persons[awarder_3[i]].award = 'T'; 
info(awarder_3[i]); 
} 

printf("\n是否重新开始抽奖?(Y or N)...\n"); 
again = getchar(); 
} 

getchar(); 
return; 
} 
