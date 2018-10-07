#include <stdio.h>
struct Student{
int  num;
char name[20];
char  sex[20]; //性别
int  nj;       //年级
char grjj[100];//简介

};
int main(int argc,const char *argv[])
{
	int n;
	int i;
	printf("请输入总的抽奖人数\n");
        scanf("%d",&n);

struct Student stus[n];



 
FILE *fp;
    for(i=1;i<=n;i++)
{
 printf("请依次输入第%d个学生的学号.姓名.性别.年级.个人简介:\n",i);
 scanf("%d %s %s %d %s",&stus[i].num,&stus[i].name,&stus[i].sex,&stus[i].nj,&stus[i].grjj);
}
    fp=fopen("xx.txt","wt+");
    for(i=1;i<=n;i++)
{
 fprintf(fp,"%d %s %s %d %s\n",stus[i].num,stus[i].name,stus[i].sex,stus[i].nj,stus[i].grjj);
}
fclose(fp);
	fp=fopen("xx.txt","r");
      if(fp==0)
	 {
		 printf("can not open the file!\n");
	 	 return 0;
	 }
	 for(i=1;i<=n;i++)
	 {
 		 fscanf(fp,"%d %s %s %d %s", &stus[i].num,&stus[i].name,&stus[i].sex,&stus[i].nj,&stus[i].grjj);
	 }
 for(i=1;i<=n;i++)
{
 printf("学号:%d 姓名:%s 性别:%s 年级:%d 个人简介：%s\n",stus[i].num,stus[i].name,stus[i].sex,stus[i].nj,stus[i].grjj);
}
 fclose(fp);
return 0;
} 
