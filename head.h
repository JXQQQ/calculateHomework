#ifndef TEST_H
#define TEST_H
#define NULL 0
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INTE 0 //����
#define FRAC 1 //����
#define MAXSIZE 10001
typedef int Status;
struct num {//����
    int mol;//����
    int den;//��ĸ(����Ĭ��Ϊ1)
};
struct formula{//ʽ��
    int numcount;//�������ĸ���
    struct num figure[4];//������������
    char oper[4];//���ŵ����飨Ĭ��oper[0]==NULL��
    Status brackets[4];//��������
};
extern struct num calculateFml(struct formula fml);
extern struct num getAnswer(char an[]);
extern int an[3];
#endif

