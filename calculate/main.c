#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"head.h"
    int an[3];//存入用户答案的全局变量
int main(struct formula f){
  int opernum;//符号数
  int typeflag,operflag=0;
  int r,i,j,k,t,n,repeat;
  int bktflag=1;
  int tnumber,numflag=1,m=0;
  FILE *file;
  createFile("Answers.txt");
  FILE *fp=fopen("Answers.txt","a+");
  struct num answers;
  createFile("Exercises.txt");
  printf("\n");
  file=fopen("Exercises.txt","a+");
  if(file==NULL) {
        printf("No File.\n");
         return 0;}
  printf("please enter the range:\n");
  scanf("%d",&r);
  printf("please enter the number of exercises:\n");
  scanf("%d",&tnumber);
  struct formula fmls[tnumber+1];
  int ran[tnumber+1][3];
  srand(time(NULL));
  while(numflag<tnumber+1){
   opernum=rand()%3+1;//确定运算符数量
   f.numcount=opernum+1;//运算数个数
   for(i=0;i<4;i++) f.figure[i].den=1;//整数时分母为1
   for(i=0;i<f.numcount;i++){
     f.figure[i].mol=rand()%r+1;
     typeflag=rand()%100;//1时为真分数
     if(typeflag==1)
         f.figure[i].den=rand()%50+1;
         if(f.figure[i].den==1||f.figure[i].mol%f.figure[i].den==0)
             f.figure[i].den=rand()%r+1;
         k=gcd(f.figure[i].mol,f.figure[i].den);
         f.figure[i].mol=f.figure[i].mol/k;
         f.figure[i].den=f.figure[i].den/k;//化简
     }//确定运算数
   for(i=0;i<4;i++){
     t=rand()%4;
     switch(t){
       case 0:f.oper[i]='+';break;
       case 1:f.oper[i]='-';break;
       case 2:f.oper[i]='*';break;
       case 3:f.oper[i]='/';break;
     }
   }//确定符号
   for(i=0;i<5;i++) f.brackets[i]=0;
   if(f.numcount==3){
     n=rand()%3;
     switch(n){
       case 0: bktflag=0;
        break;
       case 1: {
           for(i=0;i<4;i++) f.brackets[i]=0;
           f.brackets[0]=1;f.brackets[1]=1;}
       break;
       case 2:{
           for(i=0;i<4;i++) f.brackets[i]=0;
           f.brackets[1]=1;f.brackets[2]=1;}
       break;
   }
  }//3个运算数
  if(f.numcount==4){
     n=rand()%7;
     switch(n){
        case 0:bktflag=0;
         break;
        case 1:{
         for(i=0;i<4;i++) f.brackets[i]=0;
         f.brackets[0]=1;f.brackets[1]=1;}
         break;
        case 2:{
         for(i=0;i<4;i++) f.brackets[i]=0;
         f.brackets[0]=1;f.brackets[2]=1;}
         break;
        case 3:{
          for(i=0;i<4;i++) f.brackets[i]=0;
          f.brackets[1]=1;f.brackets[2]=1;}
         break;
        case 4:{
         for(i=0;i<4;i++) f.brackets[i]=0;
         f.brackets[1]=1;f.brackets[3]=1;}
         break;
        case 5:{
          for(i=0;i<4;i++) f.brackets[i]=0;
          f.brackets[2]=1;f.brackets[3]=1;}
         break;
        case 6:{
         for(i=0;i<4;i++) f.brackets[i]=1;}
         break;
     }
  }//确定括号
  for(i=1,repeat=0;i<=numflag;i++){
        if(ifRepete(f,fmls[i])==TRUE) {
            repeat=1;
            break;
        }
  }
  if(repeat==1) break;
  answers=calculateFml(f);//计算答案
  if(answers.mol<0||answers.den<0){//舍去负值式子
    continue;
  }
  printf("%d. ",numflag);//打印并录入式子和答案
  fprintf(file,"%d. ",numflag);
  printFormula(f);
  fmlInFile(file,f);
  fprintf(fp,"%d. ",numflag);
  numInFile(fp,answers);
  int g=gcd(answers.mol,answers.den);//将答案分解成三部分存入
  if(g>1){
        answers.den/=g;
        answers.mol/=g;
    }
     ran[numflag][2]=answers.den;
     ran[numflag][0]=answers.mol/answers.den;
     ran[numflag][1]=answers.mol%answers.den;
    numflag++;
 }
 //输入答案
 printf("Please input your answer:\n");
 int result[tnumber+1];
 for(i=1;i<=tnumber;i++){
    char input[10];
    struct num c1;
    printf("%d. ",i);
    fflush(stdin);
    gets(input);
    getAnswers(input);
    result[i]=1;//判断对错
    for(j=0;j<3;j++){
        if(an[j]!=ran[i][j]) {result[i]=0;break;}
    }
 }
    int correct=0,wrong=0;
    printf("Correct:(");
    for(i=1;i<=tnumber;i++){
        if(correct>0) printf(",");
        if(result[i]==1) {
                printf("%d",i);
                correct++;
        }
    }
    printf("),共%d题\n",correct);
    printf("Wrong:(");
    for(i=1;i<=tnumber;i++){
        if(wrong>0) printf(",");
        if(result[i]==0) {
                printf("%d",i);
                wrong++;
        }
    }
    printf("),共%d题\n",wrong);
 printf("\nOK:you can check the file.\n");
return 0;
}

