#define _CRT_SECURE_NO_WARNINGS 1

#include<stdio.h>
#include<string.h>
//c语言预处理章
//翻译环境和执行环境
//翻译环境--1.预编译 2.编译 3.汇编阶段
//预编译就是文本操作 把头文件里的链接整过来，包括在预处理阶段把注释行变为空格代替  把test.c---test.i文件
//编译就是把c语言代码翻译成汇编代码   test.i--test.s 转换成了汇编语言
//汇编就是test.s--转换为test.o文件   把汇编语言转换为二进制代码  这一阶段会形成符号表---Add  0x200  即放符号也放地址
//在执行环境下 会形成test.o---test.exe文件                                    符号表下只会放置有效的地址
//链接 -- 1.合并段表  2.符号表的合并和符号表的重定位

//这里可能第一次没有听懂，但是不要灰心，在下面仔细的查找资料 好好的慢慢感受这些
//这里有一本书叫《程序员的自我修养》  可以好好看一下


//预定义符号
//int main()
//{
//	printf("%s\n", __FILE__);  //文件的路径
//	printf("%d\n", __LINE__);  //打印行号
//	printf("%s\n", __DATE__);  //打印日期
//	printf("%s\n", __TIME__); // 打印时间
//	printf("%s\n", __FUNCTION__); // 函数名
//  printf("%d\n", __STDC__);  //这里你会发现VS编译器并不满足这个c语言标准库  在这里他会报错，但是在gcc编译器下可以很好的运行起来
//	return 0;
//}


//为什么我在这里运行完以后我并不知道在哪里去找到我所开辟的这个log.txt文档 
//int main()
//{
//	int arr[10] = { 0 };
//	FILE* pf = fopen("log.txt", "w");
//	int i = 0;
//	for (i = 0;i < 10;i++)
//	{
//		arr[i] = i;
//		fprintf(pf, "file:%s line:%d date:%s time:%s i=%d\n", __FILE__, __LINE__, __DATE__, __TIME__, i);  //以格式化的形式往文件中打印
//	}
//	fclose(pf);
//	pf = NULL;
//	for (i = 0;i < 10;i++)
//	{
//		printf("%d ", arr[i]);
//	}
//	return 0;
//}

//#define  #include 这些都是预处理指令
//#define 可以定义标识符 和 宏

//#define 在定义标识符的时候是否需要在结尾添加";" ???
//答案是尽量不要在后面添加";"
//#define MAX 100
////#define STR "hehe"
//int mian()
//{
//	int max = MAX;
//	printf("%d\n", max);
//	//printf("%s\n", STR);
//	return 0;
//}

//#define SQUARE(X) X*X
//int main()
//{
//	/*int ret = SQUARE(5);
//	printf("ret = %d\n", ret);*/
//
//	int ret = SQUARE(5 + 1);
//	printf("ret = %d\n", ret);    //宏是替换的  不是传参的   5+1*5+1  根据乘法运算就是 11  这里的改变方法就是在宏定义哪里给X带上()
//	//所以告诉我们在这里定义宏的时候不要吝啬(),因为很有可能会出错  因为他只是替换 对于一些运算他就改变了原本的意思
//	return 0;  //  这里的意思是相当于把5替换SQUARE(X)里的X ， 然后在转换成5*5
//}
//
//#define DOUBLE(X) ((X)+(X))
//int main()
//{
//	int a = 5;
//	int ret = 10 * DOUBLE(a);
//	printf("%d\n", ret);
//	return 0;
//}

//避免在使用宏时由于参数中的操作符或链接操作符之间不可预料的相互作用
//在程序中扩展#define定义符号和宏时，需要设计几个步骤
//1.在调用宏时，首先对参数进行检查，看看是否包含任何由#define定义的符号，如果是，他们首先被替换
//2.替换文本随后被插入到程序中原来文本位置。对于宏，参数名被他们的值替换
//3.最后，再次对结果文本进行扫描，看看它是否包含任何由#define定义的符号，如果是，就重复上述处理过程
//注意：

//#define的定义的标识符 和 宏之间最大的区别就是 宏定义里面是要有参数的
//1.宏参数和#define定义中可以出现其他#define定义的变量，但是对于宏，不能出现递归
//2.当预处理器搜索#define定义的符号的时候，字符串常量的内容并不被搜索  printf("MAX = %d\n",MAX); 这里的MAX是宏定义的，字符串内的MAX不替换

// # 和 ##
//约定俗称 在定义宏的时候要把名字全部写成大写字母好和 #define定义标识符分开

//#define PRINT(X) printf("the value of X is %d\n",X);  //这里我希望字符串里的X被传过来的参数所替换掉 但是你会发现没有用
//#define PRINT(X) printf("the value of" "#X ""is %d\n",X) // 这里我们希望可改变字符串里的那个数也变为我传的参数
/////PRINT(a) 传了一个a  在#define PRINT(X) 这个X也是a  "#X" 变成了 "a" 


//int main()
//{
//	/*printf("hello world\n");
//	printf("hello " "world\n");
//	printf("hel" "lo " "world\n");
//	return 0;*/
//	//在C语言编译器下你会发现在printf函数下 里面的字符串自动的就会连在一起
//	int a = 10;
//	int b = 20;
//	PRINT(a);
//	PRINT(b);
//	return 0;
//}


//##     可以把位于它两边的符号合成一个符号，它允许宏定义从分离的文本片段创建标识符
//#define CAT(X,Y) X##Y
//int main()
//{
//	int Class84 = 2019;
//	printf("%d\n", CAT(Class, 84));
//	//printf("%d\n",Class##84);   Class 传给了X    84传给了Y    ##把他们给连接在了一起
//	//printf("%d\n",Class84);  
//	return 0;
//}

//当你宏定义的参数是会具有副作用的
// 在申明一次宏定义并不是计算完传上去的，而是彻彻底底☆☆☆替换的
//#define MAX(X,Y)  ((X)>(Y)?(X):(Y))
//int main()
//{
//	int a = 10;
//	int b = 11;
//	int max = MAX(a++, b++);
//	//int max = ((a++)>(b++)?(a++):(b++))   在前面b先使用过一次完后+1了  后面的（b++）里面的b是
//	printf("%d\n", max);   //   12
//	printf("%d\n", a);  //  11
//	printf("%d\n", b);  //  这里在上面的b用完必须声明后又会+1  所以这里答案应该是13
//}


//学到这里你可能会发现宏和函数在一定情况下是很相似的
//那为什么不用函数来完成这个任务呢？
//1.用于调用函数和从函数返回的代码可能比实际执行这个小型计算工作所需的时间更多。所以宏比函数在程序的规模和速度方面更胜一筹
//2.更为重要的是函数的参数必须声明为特定的类型。所以函数只能在类型合适的表达式上使用。反而这个宏怎可以适用于整形，长整形，浮点型等。
//宏与类型无关
//int Max(int x, int y) // 函数作用方式
//{
//	return (x > y ? x : y);
//}
//int Max(float x, float y) // 这里你每换一个参数的类型 就要重新定义一个函数
//{
//	return (x > y ? x : y);
//}
//#define MAX(X,Y)  ((X)>(Y)?(X):(Y))  //宏
//int main()
//{
//	int a = 10;
//	int b = 20;
//	float c = 3.0f;
//	float d = 4.0f;
//	float max = Max(c, d);
//	printf("%d\n", max);// 你的变量是float型 但是你要付给一个int型会发生警告 所以你的重新定义一个函数的参数变量
//	max = MAX(c, d);
//	printf("%d\n", max);
//	//int max = Max(a, b);
//	/*int max = MAX(a, b);
//	printf("%d\n", max);*/
//	return 0;
//}

//当然宏和函数相比也有一定的劣势
//1.每次使用宏的时候，一份宏定义的代码将插入到程序中。除非宏比较短，否则可能会大幅度增加程序的长度  简单点说就是 多次插入重复的代码
// 然而函数就不会了，他只会在外部调用一次进来，省略很多不必要的代码
//2.宏是没办法调试的
//因为在预编译的时候就已经把宏的内容进行了替换， 但是你的调试其实是在对test.exe文件操作，所以你并不是很清楚这个宏你到底写错了没有
//3.宏由于类型无关，也不够严谨
//4.宏可能会带来运算符优先级的问题，导致程序容易出错


//#define MALLOC(num,type) (tpye*)malloc(num*sizeof(type))
//int main()
//{
//	//int* p = (int*)malloc(10 * sizeof(int));
//	int* p = MALLOC(10,int);
//	return 0;
//}
//宏和函数的不同能不能讲清楚
//undef  可以移除一个已经定义完的

//命令行定义     可以在编译的过程中对参数进行定义  而不是在最开始的时候直接定义 当然这是在gcc编译器下进行定义

//条件编译 ：在编译一个程序的时候我们如果要将一条语句编译或者放弃是很方便的，因为我们有条件编译指令
//比如说：调试性的代码，☆删除可惜，保留又碍事，所以我们可以选择性的编译

//#define DEBUG 1
//int main()
//{
//	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
//	int i = 0;
//	for (i = 0;i < 10;i++)
//	{
//		arr[i] = 0;
//#ifdef DEBUG            //  如果你定义了DEBUG 那就执行下面的语句  如果没有就不执行这条语句
//		printf("%d ", arr[i]);
//#endif
//	}
//}


//条件编译指令
//第一种  #if   常量表达式（如果为真）后面的语句参与编译  
//#endif

//第二种  
//int main()
//{
//#if 2==1  //(这里也都是常量表达式，如果为真就直接会执行下面的语句，后面的将不会执行了)
//	printf("haha\n");
//#elif 2==1
//	printf("hehe\n");
//#else
//	printf("嘿嘿\n");
//#endif
//
//	return 0;
//}



//int main()
//{ 
//#if defined(DEBUG)   如果定义过DEBUG那就执行下面的语句
//    printf("hehe\n");
//#endif
//	return 0;
//}
//它和上面的意思是一样的
//#ifdef  DEBUG
//printf("hehe\n");
//#endif


//int main()
//{ 
//#if !defined(DEBUG)   如果定义过DEBUG那就执行下面的语句
//    printf("hehe\n");
//#endif
//	return 0;
//}
//它和上面的意思是一样的
//#ifndef  DEBUG
//printf("hehe\n");
//#endif

//嵌套指令


//#include  如果你包含的是库函数用<> 
//如果是本地文件 用""   这个表示现在先在这个原文件查询，如果没有查找到就会去标准库下去查找   如果还是没有找到就会报错
//所以意思是说就算在标准库下的本间stdio.h依旧可以使用"来包含，但是问题就是会增加你代码运行的速度

//头文件就是把函数拷贝一份 在test.c文件下显示
//这个在写的时候在头文件内使用，避免多次的重复使用同一个头文件
//#ifndef   __TEST_H__
//#define   __TEST_H__
//#endif
//这里的意思是一样的
//#pragma once  也可以避免头文件多次的被重复使用

//#pragma pack()  在结构体部分讲解过了
//C语言深度解刨这本书


//offsetof  
//所需要包含的头文件是#include<stddef.h>
//请编写宏，计算结构体中某变量相对于首地址的偏移
#include<stddef.h>
//struct S
//{
//	char c1;
//	int a;
//	char c2;
//};
//int main()
//{
//	//struct S s;
//	printf("%d\n", offsetof(struct S, c1));  // 0
//	printf("%d\n", offsetof(struct S, a));   // 4
//	printf("%d\n", offsetof(struct S, c2));  // 8
//	return 0;
//}
//在分析一次结构体内变脸的偏移
//首先c1放在偏移地址为0的地方，其次a是一个整形其大小为4 而默认的对齐数是8（取两者的较小值4），所以a放在了偏移地址为4的地方 然后直接放c2 之战一个字节
// 这时候c2的偏移地址为8   但是整个结构体的所占大小为12   因为所占的9个格子并不是最大对齐数（4）的整数倍  所以9+3才是

//在这里我们手动实现一个offsetof的宏定义
//这里假设我们把结构体放在偏移量为0的地方    //   offsetof 求得是偏移量所以要强制类型转换一下
//#define OFFSETOF(struct_name,member_name) (int)&(((struct_name*)0)->member_name)  //   相当于把0强制类型转换为了偏移量为0的结构体指针
////                                               ((struct_name*)0)->member_name  因为你得到的这个是一个变量 所以要&
//
//struct S
//	{
//		char c1;
//		int a;
//		char c2;
//	};
//	int main()
//	{
//		//struct S s;
//		printf("%d\n", OFFSETOF(struct S, c1));  // 0
//		printf("%d\n", OFFSETOF(struct S, a));   // 4
//		printf("%d\n", OFFSETOF(struct S, c2));  // 8  
//		return 0;
//	}

// x表示以16进制形式输出  02表示不足两位，前面补0输出；超过两位不影响


//算一个联合体大小 对于联合体来说最小也是其中最大一个的大小  但是对于联合体来说也是具有对齐的

enum
{
	X1,  //  0
    Y1, // 1
	Z1= 255,
	A1,//  256
	B1,  // 257    且这里面的书写形式是，隔开的
};
//结构体里面的成员是顺序排序的

//提醒：malloc函数申请的空间不初始化，calloc函数申请的空间会被初始化为0
//只要不想内存申请动态空间就不会存在内存泄漏的问题  就不需要free 

//找单身狗
//一个数组只有2个数字是出现一次，其他所有数字都出现了2次，编写一个函数找出这两个只出现一次的数字
//例如1 2 3 4 5 1 2 3 4 6  