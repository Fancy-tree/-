
//分配任务：完成历史记录查询函数

//完成任务：
//1.完成了历史记录存取函数
//2.统计文件中换行数函数,程序需要靠换行统计抽奖人数
//3.判断字符串是否全为数字函数，将字符串类型转换为整型函数，提高了程序健壮性，阻止非法输出
//4.改进了奖项设置函数，程序输出对用户更友好，设置更灵活



using namespace std;


int InitPrize(Prize &pri); //初始化奖项设置
void InitRecord();
bool IsNum(string str); //判断字符串是否全为数字
int StrToNum(string str); //将字符串类型转换为整型
void InputTime(void);
void InputPri(int i, Prize pri);
void InputStudent(int b, Student2 students[]);
void OutputRecord(); //打印抽奖记录
int CountLines(char *filename); //统计文本行数



int main () 
{
    InputTime();
    OutputTime();
    
    return 0;
}


void InitRecord()
{
    ofstream inFile;
    
    inFile.open("record.txt", ios::trunc);  //ios::trunc 打开一个文件，然后清空内容
    inFile.close();//关闭文件
}

void InputTime(void)
{
    ofstream inFile;
    
    inFile.open("record.txt", ios::app);  //ios::app 从文件末尾开始写
    time_t timep; 
    time (&timep); 
    inFile << "本项目抽奖开始时间： " << ctime(&timep) << "\n";
    inFile.close();//关闭文件
}

void InputPri(int i, Prize pri)
{
    ofstream inFile;
    
    inFile.open("record.txt", ios::app);  //ios::app 从文件末尾开始写
    inFile << pri.Name << " * " << pri.sp[i].name << "获得者：" << "\n";
    //inFile << pri.sp[i].name << "\n";
    inFile.close();//关闭文件
}

void InputStudent(int b, Student2 students[])
{
    ofstream inFile;
    
    inFile.open("record.txt", ios::app);  //ios::app 从文件末尾开始写
    GetAllData(students);
    
    inFile << students[b].num << " " << students[b].name << " " << students[b].sex << " " << students[b].nj << " " << students[b].grjj << "\n";
    inFile.close();//关闭文件
}

void OutputRecord() //打印抽奖记录
{
    char buffer[256];
    fstream out;
    
    out.open("record.txt",ios::in); //ios::in 读
    printf("\n");
    printf("该项目抽奖已完成，具体结果如下——\n");
    printf("\n");
    while(!out.eof())
    {
        out.getline(buffer,256,'\n');//getline(char *,int,char) 表示该行字符达到256个或遇到换行就结束
        cout<<buffer<<endl;
    }
    out.close();
    //cin.get();//cin.get() 是用来读取回车键的,如果没这一行，输出的结果一闪就消失了
}

int CountLines(char *filename) //统计文本行数
{
    ifstream ReadFile;
    int n=0;
    string tmp;
    ReadFile.open(filename,ios::in);//ios::in 表示以只读的方式读取文件
    if(ReadFile.fail())//文件打开失败:返回0
    {
        return 0;
    }
    else//文件存在
    {
        while(getline(ReadFile,tmp,'\n'))
        {
            n++;
        }
        ReadFile.close();
        return n;
    }
}
 

bool IsNum(string str)
{
    int i ;
    for(i = 0; i != str.length(); i++)
    {
        if(!isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}

int StrToNum(string str)
{
    int num;
    stringstream ss(str);
    ss >> num;
    return num;
}


//***********************************************************
//向祯 改进 肖平的奖项设置函数 //改结构体，使它相对 灵活扩大奖项数量上限 使输出更人性化，阻止非法输入


#define max 100

typedef struct 
{
   char name[max];
   int num;
 
}Single;

typedef struct 
{
    char Name[max];
    Single *sp;
}Prize;

Prize pri;  
int N = 3;
int TotalPrize = 6;

int initial=0;//判断是否遵从初始设置
//int group[]={1,0,0,0,0,0};        //抽奖默认设置选择第一组

void PrizeSet();
void PrizeInfornation();    //待写
void PrizeNumber(int group[]);
void single(int group[]);
void multiple(int group[]);
void OutputInit();
void ChangePri();
int InitPrize(Prize &pri);     

int InitPrize(Prize &pri) //初始化奖项设置
{
    pri.sp = new Single[max];
    if(!pri.sp) exit(0);
    
    strcpy(pri.Name,"新年赢大奖啦啦啦");
    strcpy(pri.sp[0].name,"一等奖");
    strcpy(pri.sp[1].name,"二等奖");
    strcpy(pri.sp[2].name,"三等奖");
    pri.sp[0].num = 1;
    pri.sp[1].num = 2;
    pri.sp[2].num = 3;
 
    return 1;
}


void PrizeSet()
{
    //PrizeInfornation();//抽奖信息介绍
    //PrizeNumber();//奖项组数和分配人数设置函数
    OutputInit();
    char s[]="是否要改变默认抽奖信息设置？(y/n)\n";
    if(GetYesOrNo(s)==1)
    {
        ChangePri();
    }
}

//这个函数用于修改默认的抽奖信息设置
void ChangePri()
{
    string str1, str2;
    int i;
    
    TotalPrize = 0;
    printf("请输入需要设置的抽奖项目名称: \n");
    scanf("%s", pri.Name);
    printf("请输入需要设置的奖项数量: \n");
    while(1)
    {
        cin>>str1;
        if(IsNum(str1)){
            break;
        }else{
             printf("非法输入，请输入数字: \n");
        }
    }

    N = StrToNum(str1);
    char txt[]="data.txt";
    
    for(i=0; i<N; i++)
    {
        printf("请输入第%d个奖项的名称：\n", i+1);
        scanf("%s", pri.sp[i].name);
        printf("请输入给%s分配的获奖人数：\n", pri.sp[i].name);
        while(1)
        {
            cin>>str2;
            if(IsNum(str2)){
                break;
            }else{
                printf("非法输入，请输入数字: \n");
            }
        }
        pri.sp[i].num = StrToNum(str2);
        TotalPrize += pri.sp[i].num;
        if(CountLines(txt) < TotalPrize)
        {
            printf("当各奖项分配人数总和已大于前抽奖候选人数，系统将自动丢弃对%s及以后奖项的设置\n", pri.sp[i].name);
            N = i;
            printf("若对系统作出的判决不满意，请在设置下—2.奖项设置处重新设置抽奖信息\n");
            break;
        }
    }

    printf("最终的抽奖设置信息如下——\n");
    printf("抽奖项目: \n");
    printf("%s \n", pri.Name);
    printf("奖项设置：\n");
    for(i=0; i<N; i++)
    {
        printf("%s %d名\n", pri.sp[i].name, pri.sp[i].num);
    }
}

//该函数用于打印默认抽奖设置信息给用户
void OutputInit()
{
    printf("默认抽奖设置信息如下——\n");
    printf("抽奖项目: \n");
    printf("%s \n", pri.Name);
    printf("奖项设置：\n");
    printf("%s %d名, %s %d 名, %s %d名, \n",pri.sp[0].name, pri.sp[0].num, pri.sp[1].name, pri.sp[1].num, pri.sp[2].name, pri.sp[2].num);
}

