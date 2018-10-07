#include <stdio.h>
#include <time.h>
#include <iostream>
#include <fstream>

using namespace std;

void InputTime(void);
void OutputTime(void);


int main () 
{
    InputTime();
    OutputTime();
    
    return 0;
}

void InputTime(void)
{
    ofstream OutFile("Time.txt"); //利用构造函数创建txt文本，并且打开该文本
    time_t timep; 
    time (&timep); 
    OutFile << ctime(&timep);  //写入Time.txt文件
    OutFile.close(); //关闭Time.txt文件
}

void OutputTime(void)
{
    ifstream readFile("Time.txt");
    char temp[1024] = {0};
    readFile.getline(temp, 25);
    //可以输出空格，遇到delim符号才截止。 最后一个参数0表示文本框遇到空字符（ASCLL码为32，文本框不可能有空字符）截止符。不加第三个参数0时，表示'\n'为截止符('\n'也是换行符)
    cout << temp << endl;
    //system("PAUSE");
}
