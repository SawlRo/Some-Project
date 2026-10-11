#include <stdio.h>   //C语言IO
#include <time.h>    //C语言时间库
#include <stdlib.h>  //系统命令

#ifdef _WIN32
#include <windows.h>  //windows系统API调用
#endif

//自定义类型
typedef enum {
    CHINESE,
    ENGLISH,
    RUSSIAN,
}LANGUAGE;  //自定义枚举，决定系统语言

typedef  const char* NAME;  //语言结构简称

typedef struct{
    NAME Cho_Beg_Tex[3];  //开始文本(开头选语言)
    NAME Cho_Tes_Tex[3];  //输入失败测试文本
    NAME Cho_End_Tex[3];  //结束输入文本(开头选语言)

    NAME Ope_cho[3];  //操作选择文本
    NAME Ope_cho_end[3];  //程序结束文本
    NAME Cho_Y_N[3];  //确认文本
    NAME Cho_Set[3];  //控制界面停留文本(键入以继续)

    NAME Year_Cho[3];  //年历系统选择文本
    NAME Year_Cin_Set[3];  //年历输入文本
    NAME Month_Cho[3];  //月历系统选择文本
    NAME Month_Cin_Set[3];  //月历系统输入文本
    NAME Month_Cho_Search[3];  //阅历系统搜索文本
    NAME Day_Cho[3];  //日历系统选择文本
    NAME Day_Cin_Set[3];  //日历系统输入文本
    NAME Day_Cho_Search[3];  //日历系统搜索文本
    NAME Day_Error[3];  //日历系统错误文本(日期越界)
    NAME TIME_SEE[3];//可视实时时间文本

    NAME Year_Title[3];  //年份展示视图文本
    NAME Month_Title[3];  //月份展示视图文本
    NAME Day_Title[3];  //日期展示视图文本
    NAME Week_Title[3];  //星期展示视图文本
    NAME Month_Week_Title[3][3];  //年历系统调用:月展示视图文本
    NAME Week_Set[3][7];  //年历系统和月历系统调用:星期展示视图文本

    NAME Fes_Text[3][10];  //节日信息文本:剩余天数
    NAME Fes_Tod_Text[3][10];  //节日信息文本:当天

}LangText;  //各语言文本存储


//声明部分
LANGUAGE lang;  //全局声明语言决定变量
int operation,key;  //全局声明系统选项与系统维持循环“key”
void (*Base_Fun[6])();  //选择性函数指针数组


void OPERATION_choose();  //核心关联系统函数，包含各函数实现
void language_choose();  //语言选择函数，初始化时选择语言

void Pro_Star();  //系统显示开始函数
void Pro_End();  //系统显示结束函数

void Year_Cal();  //核心函数:年历(默认显示年历，可根据选择决定显示具体年份，也可从此处跳转月历，日历等)
void Month_Cal();  //核心函数:月历(默认显示月历，可根据选择决定显示具体月份，也可从此处跳转年历，日历等)
void Day_Cal();  //核心函数:日历(默认显示日历，可根据选择决定显示具体日期，也可从此处跳转年历，月历等)
void time_see();  //时间显示函数:显示当前具体时间

void Year_Cho_Set();  //年历选择函数，在Year_Cal打印当前年历后进行选择年历函数等操作
void Month_Cho_Set(int);  //月历选择函数，在Month_Cal打印当前月历后进行选择月历函数等操作
void Day_Cho_Set(int, int, int);  //日历选择函数:在Day_Cal打印当前日期后进行选择日期函数等操作

int Year_Cin();  //年份输入函数
int Month_Cin();  //月份输入函数
int Day_Cin(int);  //日期输入函数(受闰年影响，于是要传递一个日期最大值变量)

int Find_Week(int , int, int);  //核心函数:年历总系统核心函数，根据得到的日期确定月中显示位置(首日对应星期)
void Year_View(int);  //年历显示视图函数，建立在Month_View基础上
void Month_View(int, int);  //月历显示视图函数
void Day_View(int, int, int);  //日期显示视图函数，单独打印
void Fes_View(int, int, int);  //节日视图函数，打印节日
int Fes_Cho_Ind(int, int, int);  //节日传递函数，返回对应节日天数下标
int Month_Judge(int, int);  //月期判断函数，根据年份与月份确定当月天数，作为月历打印基础


int Date_CH(int, int ,int);  //日期转化函数，将日期值转换为年中天数值
void Con_Text();  //控制停留函数
void Test_Failed();  //错误输入提示函数
void Cle_Scr();  //清屏函数，保证年历系统打印规整性
int numCin();  //输入函数，用以保证正确输入数字
int operation_choose_test();  //关键key转变函数，调用函数改变key值跳出循环结束程序
void language_setting();  //语言设置函数，用以后期改变系统语言
void CHANGE_UTF8();  //编码设置函数，避免出现乱码

LangText Dif_LANG_TEXT;  //语言库，载录三种不同语言(语言选择由用户决定)

int Fes_Mas[10] = {1, 67, 71, 121, 124, 152, 182, 213, 253, 274};//国内一年十个常见公历节日对应的年中天数


//主函数运行部分
int main()  //主函数，运行主体
{
    CHANGE_UTF8();  //保证编码正确
    operation = 1;  //初始化选择为1
    key = 1;  //关键运行key为1，使用了死循环使其运行(OPERATION_choose中可退出程序(改变key值))
    printf("%s"
                 "%s"
                 "%s",
                 Dif_LANG_TEXT.Cho_Beg_Tex[0],
                 Dif_LANG_TEXT.Cho_Beg_Tex[1],
                 Dif_LANG_TEXT.Cho_Beg_Tex[2]);  //初始打印，决定系统语言
    language_choose();  //调用语言选择函数
    Con_Text();//让用户键入以继续
    OPERATION_choose();  //主函数运行核心:操作选择函数，内置关键key死循环，由key决定退出
    return 0;  //结束代码
}


//各函数函数体,结构体,数组
void (*Base_Fun[6])()=
{
    Pro_End,
    Year_Cal,
    Month_Cal,
    Day_Cal,
    time_see,
    language_setting,
};    //定义函数指针数组，给予指针0到5，对应开头的数字0到5的六个操作，改变全局变量operation的值传入该数组，调用对应函数


void OPERATION_choose() //程序运行主体之一，占据绝大部分程序内容
{
    while (key) //全局变量key作为关键钥匙，对应operation为0时调用Pro_End函数可以将其赋值为0，结束程序
    {
        Pro_Star();  //程序循环标题及选择函数调用，让代码生生不息
        Base_Fun[operation]();  //函数指针数组使用每一个经由Pro_Star中所赋的operation值，调用对应函数
    }
}

void language_choose()  //语言选择函数
{
    while (1)  //死循环确保用户输入正确
    {
        //全局变量lang决定语言
        if (scanf("%d", &lang)==1 && (lang == CHINESE || lang == ENGLISH || lang == RUSSIAN))
        {
            while (getchar()!='\n');  //读取缓冲区
            printf("%s",Dif_LANG_TEXT.Cho_End_Tex[lang]);  //语言选择文本
            break;  //输入成功就跳出循环
        }
        //如果输入不对，自动进行下面的代码
            printf("%s%s%s",
                 Dif_LANG_TEXT.Cho_Tes_Tex[0],
                 Dif_LANG_TEXT.Cho_Tes_Tex[1],
                 Dif_LANG_TEXT.Cho_Tes_Tex[2]);
            while (getchar()!='\n'); //读取缓冲区
    }
}

void Pro_Star()  //主循环(第一循环)开始函数
{
    while (1)
    {
        Cle_Scr();  //清屏使得界面美观
        printf("%s",Dif_LANG_TEXT.Ope_cho[lang]);
        operation = numCin();  //调用输入函数赋予operation值，下方进行边界判断
        if (operation >= 0 && operation <= 5) break;
        Test_Failed();
    }
}

void Pro_End()  //主循环结束函数，给key赋值以达到目标
{
    key = operation_choose_test();  //主要赋值，并给用户确定是否退出
    if (key == 0) printf("%s",Dif_LANG_TEXT.Ope_cho_end[lang]);
}

void Year_Cal()  //年历系统函数
{
    Cle_Scr();
    time_t now = time(NULL);  //调用了time.h头文件内的类型声明变量，后面直接返回时间存入时间戳
    struct tm *time_now = localtime(&now);  //调用time.h内的结构体得到当前时间"localtime"
    int year = time_now->tm_year + 1900;  //给年份赋值
    Year_View(year);  //调用年份视图函数
    Con_Text();  //键入文本
    Year_Cho_Set();  //进入年历选择函数
}

void Month_Cal()  //月历系统函数
{
    Cle_Scr();
    const time_t now = time(NULL);  //同上调用
    const struct tm *time_now = localtime(&now);
    int year = time_now->tm_year + 1900,month = time_now->tm_mon + 1;
    Month_View(year, month);
    Con_Text();
    Month_Cho_Set(year);
}

void Day_Cal()  //日历系统函数，内置框架逻辑同上
{
    Cle_Scr();
    const time_t now = time(NULL);
    const struct tm *time_now = localtime(&now);
    int year = time_now->tm_year + 1900,month = time_now->tm_mon + 1,day = time_now->tm_mday;
    Day_Cho_Set(year, month,day);
}

void time_see()  //显示当前时间函数
{
    Cle_Scr();
    const time_t now = time(NULL);
    const struct tm *t = localtime(&now);
    printf("%s:%d-%02d-%02d %02d:%02d:%02d\n\n",
           Dif_LANG_TEXT.TIME_SEE[lang],
           t->tm_year + 1900,  // 年
           t->tm_mon + 1,      // 月
           t->tm_mday,         // 日
           t->tm_hour,         // 时
           t->tm_min,          // 分
           t->tm_sec);         // 秒
    Con_Text();
}

void Year_Cho_Set()  //年历选择函数，年历系统函数主要功能
{
    int Year_Key = 1,year;  //声明两个变量，一个是程序内主循环(第二主循环)变量Year_Key，控制程序持续
    char choice;  //字符型选择变量，这里不用函数指针数组是因为调用函数格式不一，不便于利用函数指针数组
    while (Year_Key)
    {
        printf("%s",Dif_LANG_TEXT.Year_Cho[lang]);
        scanf(" %c",&choice);  //scanf函数内置的输入格式前加上一个空格，方便跳出一些无法读取的字符，于是避免之前缓冲输入的影响
        if (choice == 'S' || choice == 's')
        {
            year = Year_Cin();  //选择搜索指定年份时，输入年份后再调用年历视图函数
            Cle_Scr();  //清屏保证显示清晰美观
            Year_View(year);
        }
        else if (choice == 'B' || choice == 'b') break;
        else Test_Failed();
    }
}

void Month_Cho_Set(int year)  //月历选择函数，月历系统函数主要功能
{
    int Month_Key = 1,month,temp_year = year;  //同上声明一个第二主循环的控制变量
    char choice;
    while (Month_Key)
    {
        printf("%s",Dif_LANG_TEXT.Month_Cho[lang]);
        scanf(" %c",&choice);  //格式同上，输入格式前面加上空格以避免前面缓冲残留区影响
        if (choice == 'S' || choice == 's') {  //选择搜索后可以进行选择指定搜索或当月搜索
            Cle_Scr();
            printf("%s",Dif_LANG_TEXT.Month_Cho_Search[lang]);
            scanf(" %c",&choice);
            if (choice == 'S' || choice == 's') {
                year = Year_Cin();
                month = Month_Cin();
                Cle_Scr();
                Month_View(year,month);
                year = temp_year;  //返回年份原值，这样在返回第二主循环时，显示的仍是前面的月份
            }
            else if (choice == 'W' || choice == 'w')  //当月查找直接改变month值调用即可
            {
                month = Month_Cin();
                Cle_Scr();
                Month_View(year,month);
            }
            else Test_Failed();
        }
        else if (choice == 'B' || choice == 'b') Month_Key = 0;
        else Test_Failed();
    }
}

void Day_Cho_Set(int year, int month, int day)  //日历系统选择函数
{
    //声明了多个int变量，记录年月日以及最大日的副本，同样使用Day_Key来控制第二主循环
    int Day_Key = 1,year_temp = year, month_temp = month,Day_Max = Month_Judge(year,month),day_temp = day;
    int day_max_temp = Day_Max;
    char choice;
    Cle_Scr();
    while (Day_Key)
    {
        Day_View(year,month,day);  //每次步入循环都进行一次视图展示
        printf("%s",Dif_LANG_TEXT.Day_Cho[lang]);
        scanf(" %c",&choice);
        if (choice == 'A' || choice == 'a')  //用户选择A就展示上一天视图
        {
            day -= 1;  //将对应天数减一
            if (day < 1)  //边界判断当天数为0时，证明到达上个月
            {
                if (month == 1) //边界判断当月份为1时，证明上个月在上一年，此时将年份减一，月份改为十二
                {
                    year--;
                    month = 12;
                }
                else month--; //如果未到达年份边界，就只将月份减一
                day = Month_Judge(year,month);  //到达上个月，天数刷新为该月最大值
                Day_Max = Month_Judge(year,month);  //刷新最大月的值
                Cle_Scr();
            }
            while (getchar() != '\n');  //清空缓冲区残留
            Cle_Scr();  //清屏
        }
        else if (choice == 'B'|| choice == 'b')
        {
            Cle_Scr();
            Day_Key = 0;
        }
        else if (choice == 'D' || choice == 'd')  //用户选择下一天，就将天数对应加一
        {
            day += 1;
            if (day > Day_Max)  //边界判断当天数大于该月最大值时，就将其赋为1，对应一号
            {
                day = 1;
                if (month == 12)  //边界判断当月份为12，证明下一天在第二年，于是将年份加1，月份改为1月
                {
                    year++;
                    month = 1;
                }
                else month++; //如果不满足上面分支，就只将月份加1
                Day_Max = Month_Judge(year,month);  //刷新最大日的值
            }
            while (getchar() != '\n');  //清空缓冲区残留
            Cle_Scr();
        }
        else if (choice == 'S' || choice == 's')  //用户选择搜索日期，这里我们使用递归
        {
            Cle_Scr();
            printf("%s",Dif_LANG_TEXT.Day_Cho_Search[lang]);
            scanf(" %c",&choice);
            if (choice == 'S' || choice == 's')  //当选择指定搜索时，需要重置年月日及日期最大值，该函数开头的年月日及最大值副本边起作用了
            {
                year = Year_Cin();
                month = Month_Cin();
                Day_Max = Month_Judge(year,month);  //得到年月后先刷新月最大值，再给日期赋值
                day = Day_Cin(Day_Max);
                Cle_Scr();
                Day_Cho_Set(year,month,day); //递归调用Day_Cho_Set
                year = year_temp;
                month = month_temp;
                day = day_temp;
                Day_Max = day_max_temp;
            }
            else if (choice == 'W' || choice == 'w')  //如果选择当月查找日期，就直接刷新日期即可
            {
                day = Day_Cin(Day_Max);
                Cle_Scr();
            }
            else Test_Failed();
        }
        else
        {
            Cle_Scr();
            Test_Failed();
        }
    }
}

int Year_Cin()  //年份输入函数
{
    int year;
    printf("%s",Dif_LANG_TEXT.Year_Cin_Set[lang]);
    while (1)
    {
        //当输入年份成功且满足条件时，返回年份值，否则显示失败
        if (scanf(" %d",&year) == 1 && year >= 1900 && year <= 99999) return year;
        Test_Failed();
    }
}

int Month_Cin()  //月份输入函数，逻辑与年份输入函数基本相同
{
    int month;
    printf("%s",Dif_LANG_TEXT.Month_Cin_Set[lang]);
    while (1)
    {
        if (scanf(" %d",&month) == 1 && month >=1 && month <= 12) return month;
        Test_Failed();
    }
}

int Day_Cin(int Day_Max)  //日期输入函数，逻辑也与上面相同
{
    int day;
    printf("%s",Dif_LANG_TEXT.Day_Cin_Set[lang]);
    while (1)
    {
        if (scanf(" %d",&day) == 1 && day >= 1 && day <= Day_Max) return day;
        printf("%s",Dif_LANG_TEXT.Day_Error[lang]);
        Test_Failed();
    }
}

int Find_Week(int year, int month , int day) //Kim Larsen计算公式，得到日期对应星期
{
    if (month < 3)  //1月和2月按上月算
    {
        month += 12;
        year -= 1;
    }
    int week = (day + 2 * month + 3 * (month + 1) / 5 +
                year + year / 4 - year / 100 + year / 400 + 1) % 7;
    return week;  //返回星期值，周日，周一...周六对应0到6
}

void Year_View(int year)  //年份视图函数，年历核心函数
{
    //先创建行列变量，以及年历视图数组，数组存入对应日期，按照三行四列对应三行每行四个月的格式，视图数组初始化为0，后面打印要用到
    int Date, i, j, month = 1, row = 0, col = 0, Year_Map[18][28] = {0}, Day_Max;
    printf(" %s%d\n",Dif_LANG_TEXT.Year_Title[lang],year);
    while (month != 13)  //核心循环，当赋值满12各月就跳出
    {
        Date = 1;  //每次初始化日期为1，因为需要从1开始赋日期
        i = 0;  //这里有两个行列对应数组的值，一个是增量，一个是差量。i，j代表原值增量，row和col代表邻月差量
        j = Find_Week(year, month,1);  //调用函数得到每个月第一天对应的视图位置
        Day_Max = Month_Judge(year,month);  //获取每个月最大值
        while (1)  //关键循环，赋值阶段
        {
            Year_Map[i+row][j+col] = Date;  //这里的逻辑就是利用增量与差量来分别给12个月按月序赋值
            j++;  //j代表列，也就是对应的每个月每一周正常顺序
            if (j == 7)   //当j为7(证明0到6赋完值)，刷新j的值并跳到下一周
            {
                j = 0;
                i++;
            }
            if (Date == Day_Max) break;  //当赋值日期达到最大，跳出当月循环
            Date++;
        }
        col += 7;  //当每个月赋值循环结束，将对应列差量右移7，于是跳到下一个月开头
        if (col == 28)  //当列差量到达28，证明一大行四个月都赋完值了，于是跳到下一大行赋值，将列差量刷新为0并令行差量下移6个单位
        {
            col = 0;
            row += 6;
        }
        month ++;  //每次循环给月份加一
    }
    row = 0;  //结束后将行列差量和月份赋为0，下面打印视图时直接使用其作为对应下标
    col = 0;
    month=0;
    while (1)  //打印视图循环
    {
        if ((row == 0 || row == 6 || row == 12) && col == 0)
        {
            //判断开头，第二大行(对应五月)，第三大行(对应九月)打印月份标题与星期标题
            printf("\n%s\n%s   %s   %s   %s\n",
                      Dif_LANG_TEXT.Month_Week_Title[lang][month],
                      Dif_LANG_TEXT.Week_Title[lang],
                      Dif_LANG_TEXT.Week_Title[lang],
                      Dif_LANG_TEXT.Week_Title[lang],
                      Dif_LANG_TEXT.Week_Title[lang]);
            month++;
        }
        //判断当视图数组值为0，证明该位置无对应日期，为保证打印格式，于是输出三个空格；而若有值，输出值并携带空格
        Year_Map[row][col] == 0 ? printf("   ") : printf("%d ", Year_Map[row][col]);
        //判断当视图数组值小于10，此时1-9这几个数字仅占一个字符格，所以输出一个空格保证格式规整
        if (Year_Map[row][col] < 10 && Year_Map[row][col] != 0) printf(" ");
        if ((col + 1) % 7 == 0 ) printf("  ");  //每当换月输出空格隔开
        col++;
        if (col == 28)  //每当换行输出换行符并刷新col的值，下移行的值
        {
            printf("\n");
            col = 0;
            row++;
        }
        if (row == 18) break;  //判断当行数达到18，证明0-17赋值完毕，结束循环
    }
}

void Month_View( int year,int month)
{
    //声明月历视图数组，这里与年历不同的是赋值与打印过程结合，因为只需要处理一个月，逻辑基本被上面涵盖
    int i = 0, j = 0, Day = 1, month_day = Month_Judge(year , month), Month_Map[6][7] = {0};
    j = Find_Week(year, month,1);
    printf("%s%d\n%s%d\n\n%s\n",Dif_LANG_TEXT.Year_Title[lang],year,Dif_LANG_TEXT.Month_Title[lang],month,Dif_LANG_TEXT.Week_Title[lang]);
    while (1)
    {
        if(i == j)break;
        printf("   ");
        i++;
    }
    i = 0;
    while (1)
    {
        Month_Map[i][j] = Day;
        printf("%d ",Month_Map[i][j]);
        if (Day < 10) printf(" ");
        j++;
        if (j == 7)
        {
            j = 0;
            i++;
            printf("\n");
        }
        if (Day == month_day)
        {
            printf("\n\n");
            break;
        }
        Day++;
    }
}

void Day_View(int year,int month,int day)  //日历视图函数，格式化打印输出对应日期，星期，节日等
{
    int week = Find_Week(year, month,day);
    printf("%s%d.%d.%d      %s      ",Dif_LANG_TEXT.Day_Title[lang],year,month,day,Dif_LANG_TEXT.Week_Set[lang][week]);
    Fes_View(year,month,day);  //调用节日视图函数打印节日信息
}

void Fes_View(int year,int month,int day)  //节日视图函数
{
    //创建多个变量并且初始化
    //Date获取当前日期对应天数，index为节日数组序列下标，distance利用index决定距离下一节日还有多少天，judge_num用以判断当天是否为节日
    int Date = Date_CH(year,month,day),index = Fes_Cho_Ind(year, month, Date),distance,judge_num,
        Feb_temp = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;  //闰年判断，是闰年Feb_temp才有效
    distance = (index > 0 ? Fes_Mas[index] : 366) - Date + Feb_temp;
        //调用Fes_Mas函数，index大于0证明下一节日不是元旦节，减去当前日期再加上二月差值即可；但若下一节日为元旦节，就按国庆节274天算
    judge_num = (index > 0 ? Fes_Mas[index - 1] : 274) - Date + Feb_temp;
        //理论同上，但目的是为检测当天是否为节日，是则其值必为0，那么打印当天节日
        //对于数组访问越界问题，由于index的值在节日与日期相等时必定大于0，所以不会发生越界
    if(judge_num == 0 && index > 0) printf("%s      ",Dif_LANG_TEXT.Fes_Tod_Text[lang][index - 1]);
    if (judge_num == 0 && index == 0)printf("%s      ",Dif_LANG_TEXT.Fes_Tod_Text[lang][9]);
    printf("%d %s\n",distance,Dif_LANG_TEXT.Fes_Text[lang][index]);
}

int Fes_Cho_Ind(int year, int month, int date)  //节日数组序列返回函数
{
    int index = 1,Feb_temp = (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) && month > 2; //调制二月差值
    while (1)
    {
        if (date - Fes_Mas[index] -Feb_temp < 0) break;  //当天数小于对于数组内天数时，证明此时刚好下一个节日为对于序列
        index++;
        if (index == 10)  //倘若数组末端也不满足，则证明下一个节日为次年元旦，赋值i=0并返回
        {
            index = 0;
            break;
        }
    }
    return index;
}

int Month_Judge(int year,int month)  //闰年判断函数，返回月份对于最大值
{
    int month_day[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if ( (year % 4 == 0 && year % 100 != 0)  || year % 400 == 0) month_day[1] = 29;
    return month_day[month - 1];
}

int Date_CH(const int year, const int month,const int day)  //月份累加，返回对于日期年中天数
{
    int month_date[12]={0,31,59,90,120,151,181,212,243,273,304,334},days = month_date[month - 1] + day;
    days += (year%4 == 0 && year%100 != 0 || year % 400 == 0) && month > 2;
    return days;
}

void Con_Text()
{
    printf("%s",Dif_LANG_TEXT.Cho_Set[lang]);
    while(getchar() != '\n');
}

void Test_Failed()
{
    printf("%s",Dif_LANG_TEXT.Cho_Tes_Tex[lang]);
    while (getchar()!='\n');
}

void Cle_Scr()  //关键清屏函数
{
    #ifdef _WIN32  //当系统为windows，执行windows命令
        system("cls");
    #else  //倘若操作系统为Mac或Linux，执行对应可执行命令
        system("clear");
    #endif
}

int numCin()
{
    int num;
    while (1)
    {
        if (scanf(" %d", &num)==1)
        {
            while (getchar()!='\n');
            break;
        }
            printf("%s",Dif_LANG_TEXT.Cho_Tes_Tex[lang]);
            while (getchar()!='\n');
    }
    return num;
}

int operation_choose_test()
{
    char choice;
    while (1)
    {
        printf("%s",Dif_LANG_TEXT.Cho_Y_N[lang]);
        scanf("%c", &choice);
        while (getchar()!='\n');
        if (choice == 'Y' || choice == 'y') return 0;
        if (choice == 'N' || choice == 'n') return 1;
        printf("%s",Dif_LANG_TEXT.Cho_Tes_Tex[lang]);
    }
}

void language_setting()
{
    Cle_Scr();
    printf("%s"
                 "%s"
                 "%s",
                 Dif_LANG_TEXT.Cho_Beg_Tex[0],
                 Dif_LANG_TEXT.Cho_Beg_Tex[1],
                 Dif_LANG_TEXT.Cho_Beg_Tex[2]);
    language_choose();
}

void CHANGE_UTF8()  //关键编码函数，防止程序将来打包或者在其他环境中运行出现错误，强制转换为UTF-8编码
{
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif
}

//总文本
LangText Dif_LANG_TEXT =
{
    {
        "语言(中文:请输入数字0)\n",
        "Language(English: Please enter 1)\n",
        "Язык(Русский: Пожалуйста, введите 2)\n\n"},

    {
        "\n请正确输入\n",
        "\nPlease enter correctly\n",
        "\nПожалуйста, вводите корректно\n\n"},

    {
        "语言:中文\n\n",
        "Language: English\n\n",
        "Язык: Русский\n\n"},

    {
        "\n请输入数字以进行选择:\n0:退出程序\n1:显示年历\n"
        "2:显示月历\n3:显示日期\n4:显示当前时间\n5:语言(Language/Язык)\n\n",

        "\nPlease enter a number to make a selection:\n"
        "0:Exit the program\n1:Display yearly calendar\n"
        "2:Display monthly calendar\n3:Display date\n4:Display current time\n"
        "5:Language(语言/Язык)\n\n",

        "\nПожалуйста, введите цифру для выбора:\n0:Выход из программы\n"
        "1:Отобразить годовой календарь\n"
        "2:Отобразить месячный календарь\n3:Отобразить дату\n"
        "4:Отобразить текущее время\n5:Язык(语言/Language)\n\n"
    },

    {"\n\n程序结束\n","\n\nProgram End\n","\n\nПрограмма завершена\n"},

    {"\n\n确认？\n是(Y)否(N)\n\n","\nConfirm?\nYes(Y)No(N)\n","\n\nПодтвердить?\nДа(Y)Нет(N)\n"},

    {"\n请按回车以继续...\n",
        "\nPress Enter to continue...\n",
        "\nНажмите Enter для продолжения...\n"
    },

    {
        "\n请选择操作:\nS.搜索年份    B.返回主程序\n\n",
        "\nPlease select operation:\nS.Search Year    B.Return to Main Program\n\n",
        "\nВыберите операцию:\nS.Поиск года    B.Вернуться в главную программу\n\n"},

    {
        "\n请输入年份(1900-99999)\n\n",
        "\nPlease enter the year(1900-99999)\n\n",
        "\nПожалуйста, введите год(1900-99999)\n\n"
    },

    {
        "\n请选择操作:\nS.搜索月份    B.返回\n\n",
        "\nPlease select operation:\nS.Search Month    B.Return\n\n",
        "\nВыберите операцию:\nS.Поиск месяца    B.Вернуться\n\n"
    },

    {
        "\n请输入月份(1-12)\n\n","\nPlease enter the month(1-12):\n\n","Пожалуйста, введите месяц(1-12):\n\n"
    },

    {"\n请选择操作:\nW.今年某月    S.某年某月\n\n",
        "\nPlease select operation:\nW.Current month    S.Specified month\n\n",
        "\nВыберите операцию:\nW.Текущий месяц    S.Заданный месяц\n\n"
    },

    {"\n请选择操作:\nA.上一天    B.返回    S.搜索日期    D.下一天\n\n",
        "\nPlease select operation:\nA.Previous Day    B.Return    S.Search Date    D.Next Day\n\n",
        "\nВыберите операцию:\nA.Предыдущий день    B.Вернуться    S.Поиск даты    D.Следующий день\n\n"
    },

    {
        "\n\n请输入日期:(1-31)\n\n","\n\nPlease enter the date(1-31)\n\n","\n\nПожалуйста, введите дату(1-31)\n\n"
    },

    {"\n请选择操作\nW.当月查找    S.指定查找\n\n",
        "\nPlease select operation:\nW.Current Month Search    S.Specified Search\n\n",
        "\nВыберите операцию:\nW.Поиск Текущего Месяца    S.Заданный Поиск\n\n"
    },

    {"\n不存在的日期\n\n","\nInvalid date\n\n","\nНеверная дата\n\n"},

    {"\n时间","\nTime","\nВремя"},

    {"\n年份:","\nYear:","\nГод:"},

    {"\n月份:","\nMonth:","\nМесяц:"},

    {"\n日期:","\nDate:","\nДата:"},

    {"日 一 二 三 四 五 六","Su Mo Tu We Th Fr Sa","Вс Пн Вт Ср Чт Пт Сб"},

    {
        {"一月                   二月                   三月                   四月",
            "五月                   六月                   七月                   八月",
            "九月                   十月                   十一月                 十二月"
        },
        {"Jan                    Feb                    Mar                    Apr",
            "May                    Jun                    Jul                    Aug",
            "Sep                    Oct                    Nov                    Dec"
        },
        {"ЯНВ                    ФЕВ                    МАР                    АПР",
            "МАЙ                    ИЮН                    ИЮЛ                    АВГ",
            "СЕН                    ОКТ                    НОЯ                    ДЕК"
        }
    },
    {
        {"周日","周一","周二","周三","周四","周五","周六"
        },
        {"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"
        },
        {"Воскресенье","Понедельник","Вторник","Среда","Четверг","Пятница","Суббота"
        }
    },

    {
        {"天后:元旦","天后:妇女节","天后:植树节","天后:劳动节","天后:青年节",
            "天后:儿童节","天后:建党节","天后:建军节","天后:教师节","天后:国庆节"},

        {"days left: New Year's Day","days left: Women's Day",
            "days left: Arbor Day","days left: Labour Day",
            "days left: Youth Day","days left: Children's Day",
            "days left: CPC Founding Day","days left: PLA Founding Day",
            "days left: Teachers' Day","days left: National Day"},

        {"дней осталось: Новый год","дней осталось: Женский день",
            "дней осталось: День посадки деревьев","дней осталось: День Труда",
            "дней осталось: День молодёжи","дней осталось: День защиты детей",
            "дней осталось: День образования КПК","дней осталось: День образования НОАК",
            "дней осталось: День учителя","дней осталось: Национальный день"}
    },
    {{"今天是元旦节","今天是妇女节","今天是植树节","今天是劳动节",
        "今天是青年节","今天是儿童节","今天是建党节","今天是建军节","今天是教师节","今天是国庆节"},

        {"Today is New Year's Day","Today is Women's Day","Today is Arbor Day",
            "Today is Labour Day","Today is Youth Day","Today is Children's Day",
            "Today is CPC Founding Day","Today is PLA Founding Day",
            "Today is Teachers' Day","Today is National Day"},

        {"Сегодня Новый год","Сегодня Женский день","Сегодня День посадки деревьев",
            "Сегодня День Труда","Сегодня День молодёжи","Сегодня День защиты детей",
            "Сегодня День образования КПК","Сегодня День образования НОАК",
            "Сегодня День учителя","Сегодня Национальный день"}
    }
};