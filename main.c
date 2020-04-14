#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"head.h"
    int an[3];//�����û��𰸵�ȫ�ֱ���
int main(struct formula f){
  int opernum;//������
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
   opernum=rand()%3+1;//ȷ�����������
   f.numcount=opernum+1;//����������
   for(i=0;i<4;i++) f.figure[i].den=1;//����ʱ��ĸΪ1
   for(i=0;i<f.numcount;i++){
     f.figure[i].mol=rand()%r+1;
     typeflag=rand()%100;//1ʱΪ�����
     if(typeflag==1)
         f.figure[i].den=rand()%50+1;
         if(f.figure[i].den==1||f.figure[i].mol%f.figure[i].den==0)
             f.figure[i].den=rand()%r+1;
         k=gcd(f.figure[i].mol,f.figure[i].den);
         f.figure[i].mol=f.figure[i].mol/k;
         f.figure[i].den=f.figure[i].den/k;//����
     }//ȷ��������
   for(i=0;i<4;i++){
     t=rand()%4;
     switch(t){
       case 0:f.oper[i]='+';break;
       case 1:f.oper[i]='-';break;
       case 2:f.oper[i]='*';break;
       case 3:f.oper[i]='/';break;
     }
   }//ȷ������
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
  }//3��������
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
  }//ȷ������
  for(i=1,repeat=0;i<=numflag;i++){
        if(ifRepete(f,fmls[i])==TRUE) {
            repeat=1;
            break;
        }
  }
  if(repeat==1) break;
  answers=calculateFml(f);//�����
  if(answers.mol<0||answers.den<0){//��ȥ��ֵʽ��
    continue;
  }
  printf("%d. ",numflag);//��ӡ��¼��ʽ�Ӻʹ�
  fprintf(file,"%d. ",numflag);
  printFormula(f);
  fmlInFile(file,f);
  fprintf(fp,"%d. ",numflag);
  numInFile(fp,answers);
  int g=gcd(answers.mol,answers.den);//���𰸷ֽ�������ִ���
  if(g>1){
        answers.den/=g;
        answers.mol/=g;
    }
     ran[numflag][2]=answers.den;
     ran[numflag][0]=answers.mol/answers.den;
     ran[numflag][1]=answers.mol%answers.den;
    numflag++;
 }
 //�����
 printf("Please input your answer:\n");
 int result[tnumber+1];
 for(i=1;i<=tnumber;i++){
    char input[10];
    struct num c1;
    printf("%d. ",i);
    fflush(stdin);
    gets(input);
    getAnswers(input);
    result[i]=1;//�ж϶Դ�
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
    printf("),��%d��\n",correct);
    printf("Wrong:(");
    for(i=1;i<=tnumber;i++){
        if(wrong>0) printf(",");
        if(result[i]==0) {
                printf("%d",i);
                wrong++;
        }
    }
    printf("),��%d��\n",wrong);
 printf("\nOK:you can check the file.\n");
return 0;
}

