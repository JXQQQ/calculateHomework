#ifndef TEST_H
#define TEST_H
#define NULL 0
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INTE 0 //整数
#define FRAC 1 //分数
#define MAXSIZE 10001
typedef int Status;
struct num {//数据
    int mol;//分子
    int den;//分母(整数默认为1)
};
struct formula{//式子
    int numcount;//运算数的个数
    struct num figure[4];//运算数的数组
    char oper[4];//符号的数组（默认oper[0]==NULL）
    Status brackets[4];//括号数组
};
extern struct num calculateFml(struct formula fml);
extern struct num getAnswer(char an[]);
extern int an[3];
#endif

