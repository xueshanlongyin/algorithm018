# 学习笔记
## c语言
### 数组
1. 数组做函数形参,是传引用,不是传值函数内部改变数组元素,在函数外部也能体现修改,例如下面代码执行后,a[1]=5,a[2]=4
    ```c
    void updateArray (int a[]) {
        a[1]=5;
        a[2]=4;
    }

    int main() {
        int a[5] = {1,2,3,4,5};
        updateArray(a);
        printf("%d,%d\n", a[1], a[2]);
        return 0;
    }
    ```
2. T *p和T p[]等价
3. T a[M][N]; a[i]是一维数组, a[i]的类型是T *, sizeof(a[i]) = sizeof(T) * N, a[i]指向的地址 = 数组a的起始地址 + i * N * sizeof(T)
### 字符串
1. char *p="1234"与char p[]="1234"的区别是:1)前者属于只读数据区,是指针变量指向字符串常量,后者属于栈中分配的连续空间;2)前者不能通过 *p改写字符串内容,后者可以通过 *p或p[i]改写字符串内容
### 库函数
1. c/c++,数学函数math.h/cmath.h,字符处理函数ctype.h,字符分类函数一般用静态查表来实现
   ```c
   #define isdigit(x) (TABLE[x] & 1)
   ```
2. strcpy(char dest[], char src[]);
3. strcmp(char s1[], char s2[]); s1=s2,return=0; s1<s2,return<0; s1>s2,return>0;
4. strcat(char s1[], char s2[]);
5. strupr(char s[]);
6. strlwr(char s[]);
7. strstr(char s1[], char s2[]);判断s2是不是s1的子串,如果是,返回s2首字符在s1的位置
   ```c
   int Strstr(char s1[], char s2[]){
        if (strlen(s2) == 0) {
            return 0;
        }
        for (int i = 0; s1[i] != '\0'; i++) {
            int k = i;
            int j = 0;
            for (; s2[j] != '\0'; j++, k++) {
                if(s1[k] != s2[j]) {
                    break;
                }
            }
            if (s2[j] == '\0') {
                return i;
            }
        }
        return -1;
    }
   ```
8. char *strtok(char *str, const char *delim); 从str中逐个抽取被delim分隔开的若干个子串
   ```c

    char str[] = "- this, a sample string, ok.";
    char *p =  strtok(str, " ,.-");
    while (p != NULL) {
        printf("%s\n", p);
        p = strtok(NULL, " ,.-");// 分隔结束前,strtok首个参数必须是NULL,不再是str
    }
    printf("str = %s\n", str); // str = "- this",strtok破坏原有字符串,将子串后的第一个分隔符设置为'\0',用来做子串的结束符,返回子串首地址
   ```
9.  int atoi(char *s), double atof(char *s);
10. char *itoa(int val, char *s, int radix);
11. strncpy(s1, s2, n); 如果n > strlen(s2), 则s1 = s2; 否则, 替换s1的前n个字符为s2的前n个字符
    ```c
    char s1[] = "12345";
    char s2[] = "abc";
    printf("%s\n",strncpy(s1, s2, 3)); // s1="abc45"
    //printf("%s\n",strncpy(s1, s2, 4)); // s1="abc"
    ```
12. void *memset(void *dest, int ch, int n);将从dest开始的n个字节,都设置为ch,返回值是dest,ch只有最低的字节起作用
    ```c
    memset(arr, 0x321, sizeof(arr)); // arr[0]=arr[1]=arr[i]=0x21212121
    ```
13. T arr[n];sizeof(arr) = n*sizeof(T),数组的sizeof等于数组所占用的内存字节数
14. void *memcpy(void *dest, void *src, int n);将地址src开始的n个字节拷贝到地址dest,返回值是dest
15. void qsort(void * base, int nelem, unsigned int width, int(* pfcompare)(const void*, const void*));base起始地址,nelem待排序数组的元素个数,width每个元素大小(字节为单位),pfcompare比较函数地址;pfcompare(e1, e2),__(1)e1排在e2前面,则函数返回值是负整数(2)e1/e2哪个排在前面都行,则函数返回0(3)e1排在e2后面,则函数返回正整数__
16. char *strchr(const char *str, int c);查找给定字符c在str首次出现的位置,否则返回NULL
### 位运算
1. "&"通常用来,__将某变量的某些位清0且保持其他位不变__,__也可以用来获取某变量中的某一位__,如n&=0xf0,将低4位置0;n&0x80 == 0x80,判断第7位是否为1
2. "|"通常用来,__将变量中的某些位置1且保持其他位不变__,例如将int型变量n的低8位全置为1,其余位不变,则n|=0xff
3. "^"通常用来,__将变量中的某些位取反且保留其他位不变__,例如将int型变量n的低8位取反,其余位不变,则n^=0xff,__跟1异或取反，跟0异或不变__,异或运算规律:__已知a^b=c,则c^b=a,c^a=b__,可以实现不通过临时变量交换两个变量的值
4. "~"按位非运算
5. "<<"左移,高位丢弃,低位补0,比乘法操作快
6. ">>"右移,丢弃右侧,大多数C/C++编译器规定,原符号位为1,则右移补1;原符号位为0,则右移补0,相当于除以2的n次幂,结果往小里取整
7. int型a,n(0<=n<31),求a的第n位,(a>>n)&1或(a&(1<<n))>>n(前提条件是n<31,否则右移时可能补1)
### 格式化输入输出
1. printf("%x", n),变量n会自动转换为int型,short n = 0xfffe,输出时会转换为0xfffffffe
2. scanf的format最好不要用非空格比如","做分隔符,尤其是给%s赋值时,因为","会被当做%s中的一个字符;__默认的数据输入间隔是空格/\n/tab,所以%s不会存储空格/\n/tab__,但%c会存储空格/\n等字符,所以%c不能与%s等连用,最好在%c前加一个空格,这样在数据输入时%c会保存空格后的第一个字符,
   ```c
   scanf("%s%s %c", prisonName, response, & c1);
   ```
3. 需要读入一行到字符数组
   
   c语言
   ```c
   char s[80] = {0};
   char buf[80] = {0};
   scanf("%[^\n]", s);
   getchar(); // 清空缓冲区,否则gets会把\n从缓冲区取出并丢弃,buf得不到任何值
   gets(buf);
   ```
   c++
   ```c++
    char name[20] = {0};
    cin.getline(name, 20); // 读取一行不超过bufsize-1个字符到buf，末尾加'\0',换行符从输入流丢弃;超出bufsize-1,getline会设置失效位,关闭输入;使用cin.clear()重置失效位,打开输入,则能继续使用余下的字符串
    cin.clear();
    string s;
    getline(cin, s);
   ```

### 双指针的用法
1. 用作函数的返回值，比较常见的是返回分配的堆内存地址
    ```c
    bool get_memory(char **pst, unsigned int size) 
    ```
2. 用于申请动态一维数组，只是这个一维数组中存储的是指针类型,一维数组中的每个指针又可以动态分配一个一维数组，即最终可以形成一个二维数组
    ```c
    ppArray = (int**)malloc(sizeof(int*) * size)
    ```
3. 表示指针的地址，即指向指针的指针
    ```c
    #define TAILQ_ENTRY(type)
    struct {
        struct type *tqe_next;    /* next element */
        struct type **tqe_prev;    /* address of previous next element */
    }
    ```
### typedef用法
1. 为基本数据类型定义新的类型名
2. 为自定义数据类型（结构体、共用体和枚举类型）定义简洁的类型名称
3. 为数组定义简洁的类型名称
    ```c
    typedef int INT_ARRAY_100[100];
    INT_ARRAY_100 arr;
    ```
4. 为指针定义简洁的名称
    ```c
    // PFun是我们创建的一个类型别名
    typedef int *(*PFun)(int,char*);
    // 使用定义的新类型来声明对象，等价于int*(*a[5])(int,char*);
    PFun a[5];
    ```

### windows下安装MinGW的配置
1. https://zhuanlan.zhihu.com/p/66197013

### git配置
1. https://www.cnblogs.com/future-dream/p/11021983.html
2. https://www.zhihu.com/question/21402411
3. https://shimo.im/docs/m5rtM8K8rNsjw5jk/read

### 递归
1. C/C++模板
    ```c
    void recursion(int level, int param) { 
    // recursion terminator
    if (level > MAX_LEVEL) { 
        // process result 
        return ; 
    }
    // process current logic 
    process(level, param);
    // drill down 
    recursion(level + 1, param);
    // reverse the current level status if ne
    ```

### 树
1. C/C++模板
    ```c
    typedef struct TreeNode{
        int val;
        struct TreeNode *left;
        struct TreeNode *right;
    }TreeNode;
    ```

## linux学习
### 头文件
1. 
    ```c
    #include <linux/***.h> //是在linux-2.6.29/include/linux下面寻找源文件
    #include <asm/***.h> //是在linux-2.6.29/arch/arm/include/asm下面寻找源文件。
    #include <mach/***.h> //是在linux-2.6.29/arch/arm/mach-s3c2410/include/mach下面寻找源文件。

    #include <plat/regs-adc.h>//在linux-2.6.31_TX2440A20100510\linux-2.6.31_TX2440A\arch\arm\plat-s3c\include\plat
    #include <linux/module.h> //最基本的文件，支持动态添加和卸载模块。Hello World驱动要这一个文件就可以了
    #include <linux/fs.h> //包含了文件操作相关struct的定义，例如大名鼎鼎的struct file_operations

    //包含了struct inode 的定义，MINOR、MAJOR的头文件。
    #include <linux/errno.h> //包含了对返回值的宏定义，这样用户程序可以用perror输出错误信息。
    #include <linux/types.h> //对一些特殊类型的定义，例如dev_t, off_t, pid_t.其实这些类型大部分都是unsigned int型通过一连串的typedef变过来的，只是为了方便阅读。
    #include <linux/cdev.h> //对字符设备结构cdev以及一系列的操作函数的定义。//包含了cdev 结构及相关函数的定义。
    #include <linux/wait.h> //等代队列相关头文件//内核等待队列，它包含了自旋锁的头文件

    #include <linux/init.h>
    #include <linux/kernel.h> 

    #include <linux/slab.h> //包含了kcalloc、kzalloc内存分配函数的定义。
    #include <linux/uaccess.h> //包含了copy_to_user、copy_from_user等内核访问用户进程内存地址的函数定义。
    #include <linux/device.h> //包含了device、class 等结构的定义
    #include <linux/io.h> //包含了ioremap、iowrite等内核访问IO内存等函数的定义。
    #include <linux/miscdevice.h> //包含了miscdevice结构的定义及相关的操作函数。
    #include <linux/interrupt.h> //使用中断必须的头文件
    #include <mach/irqs.h> //使用中断必须的头文件
    #include <asm/bitops.h> //包含set_bit等位操作函数，实现Input子系统时可用。
    #include <linux/semaphore.h> //使用信号量必须的头文件
    #include <linux/spinlock.h> //自旋锁

    #include <linux/sched.h> //内核等待队列中要使用的TASK_NORMAL、TASK_INTERRUPTIBLE包含在这个头文件
    #include <linux/kfifo.h> //fifo环形队列
    #include <linux/timer.h> //内核定时器
    #include <linux/input.h> //中断处理

    //头文件主目录include

    //头文件目录中总共有32个.h头文件。其中主目录下有13个，asm子目录中有4个，linux子目录中有10个，sys子目录中有5个。这些头文件各自的功能如下，具体的作用和所包含的信息请参见第14章。

    #include <a.out.h> //a.out头文件，定义了a.out执行文件格式和一些宏。
    #include <const.h> //常数符号头文件，目前仅定义了i节点中i_mode字段的各标志位。
    #include <ctype.h> //字符类型头文件，定义了一些有关字符类型判断和转换的宏。
    #include <errno.h> //错误号头文件，包含系统中各种出错号。(Linus从minix中引进的)
    #include <fcntl.h> //文件控制头文件，用于文件及其描述符的操作控制常数符号的定义。
    #include <signal.h> //信号头文件，定义信号符号常量，信号结构以及信号操作函数原型
    #include <stdarg.h> //标准参数头文件，以宏的形式定义变量参数列表。主要说明了一个类型（va_list）和3个宏（va_start, va_arg和va_end），用于vsprintf、vprintf、vfprintf函数。
    #include <stddef.h> //标准定义头文件，定义了NULL, offsetof(TYPE, MEMBER)。
    #include <string.h> //字符串头文件，主要定义了一些有关字符串操作的嵌入函数。
    #include <termios.h> //终端输入输出函数头文件，主要定义控制异步通信口的终端接口。
    #include <time.h> //时间类型头文件，主要定义了tm结构和一些有关时间的函数原形。
    #include <unistd.h> //Linux标准头文件，定义了各种符号常数和类型，并声明了各种函数。如，定义了__LIBRARY__，则还包括系统调用号和内嵌汇编_syscall0()等。
    #include <utime.h> //用户时间头文件，定义了访问和修改时间结构以及utime()原型。

    //(1)体系结构相关头文件子目录include/asm

    //这些头文件主要定义了一些与CPU体系结构密切相关的数据结构、宏函数和变量。共4个文件。

    #include <asm/io.h> //I/O头文件，以宏的嵌入汇编程序形式定义对I/O端口操作的函数。
    #include <asm/memory.h> //内存拷贝头文件，含有memcpy()嵌入式汇编宏函数。
    #include <asm/segment.h> //段操作头文件，定义了有关段寄存器操作的嵌入式汇编函数。
    #include <asm/system.h> //系统头文件，定义了设置或修改描述符/中断门等的嵌入式汇编宏。

    //(2)Linux内核专用头文件子目录include/linux

    #include <linux/config.h> //内核配置头文件，定义键盘语言和硬盘类型（HD_TYPE）可选项。
    #include <linux/fdreg.h> //软驱头文件，含有软盘控制器参数的一些定义。
    #include <linux/fs.h> //文件系统头文件，定义文件表结构（file,buffer_head,m_inode等）。
    #include <linux/hdreg.h> //硬盘参数头文件，定义访问硬盘寄存器端口、状态码和分区表等信息。
    #include <linux/head.h> //head头文件，定义了段描述符的简单结构，和几个选择符常量。
    #include <linux/kernel.h> //内核头文件，含有一些内核常用函数的原形定义。
    #include <linux/mm.h> //内存管理头文件，含有页面大小定义和一些页面释放函数原型。
    #include <linux/sched.h> //调度程序头文件，定义了任务结构task_struct、初始任务0的数据，以及一些有关描述符参数设置和获取的嵌入式汇编函数宏语句。
    #include <linux/sys.h> //系统调用头文件，含有72个系统调用C函数处理程序,以"sys_"开头。
    #include <linux/tty.h> //tty头文件，定义了有关tty_io，串行通信方面的参数、常数。

    //(3)系统专用数据结构子目录include/sys

    #include <sys/stat.h> //文件状态头文件，含有文件或文件系统状态结构stat{}和常量。
    #include <sys/times.h> //定义了进程中运行时间结构tms以及times()函数原型。
    #include <sys/types.h> //类型头文件，定义了基本的系统数据类型。
    #include <sys/utsname.h> //系统名称结构头文件。
    #include <sys/wait.h> //等待调用头文件，定义系统调用wait()和waitpid()及相关常数符号.
    ```
