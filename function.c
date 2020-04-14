#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "head.h"
void createFile(char filename[]){//创建文件,已存在则覆盖
    FILE *fp;
    fp=fopen(filename, "w");//写入文件
    if(fp==NULL) printf("文件创建失败");
    else printf("文件%s创建成功！",filename);
    fclose(fp);
}
int gcd(int numa,int numb){//最大公约数
  if(numb==0) return numa;
  return gcd(numb,numa%numb);
}//求最大公约数
void printFormula(struct formula fml){//打印一个式子
    int flag=0,bflag=0;//出现单括号时flag=1，已打印括号时bflag=1
    int i;
    for(i=0,flag=0;i<fml.numcount;i++){
        bflag=0;
        if(i>0) {
                if(fml.oper[i]=='/') printf("÷");
                else if(fml.oper[i]=='*') printf("×");
                else printf("%c",fml.oper[i]);
            }
        if(fml.brackets[i]==TRUE&&flag==0&&bflag==0){
            printf("(");
            flag=1;
            bflag=1;
        }
        printNum(fml.figure[i]);
        if(flag==1&&fml.brackets[i]==TRUE&&bflag==0) {
            printf(")");
            flag=0;
        }
    }
    printf("=\n");

}
void printNum(struct num c1){//真分数打印一个数
        int g=gcd(c1.mol,c1.den);
        if(g>1){
            c1.den/=g;
            c1.mol/=g;
        }
        if(c1.den==1) printf("%d",c1.mol);
        else if(c1.den<c1.mol){
            int z=c1.mol/c1.den;
            int r=c1.mol%c1.den;
            printf("%d'%d/%d",z,r,c1.den);
        }else printf("%d/%d",c1.mol,c1.den);
        return ;
}
void fmlInFile(FILE *fp,struct formula fml){//写入文件：式子
    if(fp==NULL){
        printf("式子写入失败");
    }else{
        int flag,bflag=0;//出现单括号时为1
        int i;
        for(i=0,flag=0;i<fml.numcount;i++){
                bflag=0;
            if(i>0) {
                if(fml.oper[i]=='/') fprintf(fp,"÷");
                else if(fml.oper[i]=='*') fprintf(fp,"×");
                else fprintf(fp,"%c",fml.oper[i]);
            }
            if(flag==0&&fml.brackets[i]==TRUE&&bflag==0){
                fprintf(fp,"(");
                flag=1;
                bflag=1;
            }

            int g=gcd(fml.figure[i].mol,fml.figure[i].den);//打印式子中的数
            if(g>1){
                fml.figure[i].den/=g;
                fml.figure[i].mol/=g;
            }
            if(fml.figure[i].den==1) fprintf(fp,"%d",fml.figure[i].mol);
            else if(fml.figure[i].den<fml.figure[i].mol){
                int z=fml.figure[i].mol/fml.figure[i].den;
                int r=fml.figure[i].mol%fml.figure[i].den;
                fprintf(fp,"%d'%d/%d",z,r,fml.figure[i].den);
            }else fprintf(fp,"%d/%d",fml.figure[i].mol,fml.figure[i].den);
            if(flag==1&&fml.brackets[i]==TRUE&&bflag==0) {
                fprintf(fp,")");
                flag=0;
            }
        }
    fprintf(fp,"=\n");
    }
    return 0;
}
struct num addCount(struct num c1,struct num c2){//两数加法
    struct num c3;
    c3.den=c1.den*c2.den;
    c3.mol=c1.mol*c2.den+c1.den*c2.mol;
    return c3;
}
struct num subCount(struct num c1,struct num c2){//两数减法
    struct num c3;
    c3.den=c1.den*c2.den;
    c3.mol=c1.mol*c2.den-c1.den*c2.mol;
    return c3;
}
struct num mulCount(struct num c1,struct num c2){//两数乘法
    struct num c3;
    c3.den=c1.den*c2.den;
    c3.mol=c1.mol*c2.mol;
    return c3;
}
struct num divCount(struct num c1,struct num c2){//两数除法
    struct num c3;
    c3.den=c1.den*c2.mol;
    c3.mol=c1.mol*c2.den;
    return c3;
}
struct num calculate(struct num c1,struct num c2,char oper0){//两数运算
    switch(oper0){
    case'+':
        return addCount(c1,c2);
    case'-':
        return subCount(c1,c2);
    case'*':
        return mulCount(c1,c2);
    case'/':
        return divCount(c1,c2);
    default:
        printf("计算失效！");
        return c1;
    }
}
struct formula simplifyMD(struct formula fml){//递归计算式子中乘除法（不考虑括号变化）
    int i=0;
    struct num temp;
    for(i=0;i<fml.numcount-1;i++){
        if(fml.oper[i+1]=='*'||fml.oper[i+1]=='/'){
            temp=calculate(fml.figure[i],fml.figure[i+1],fml.oper[i+1]);
            fml.figure[i++]=temp;
            fml.numcount--;
                for(;i<fml.numcount;i++){
                    fml.figure[i]=fml.figure[i+1];
                    fml.oper[i]=fml.oper[i+1];
                }
                fml=simplifyMD(fml);
        }
    }
    return fml;
}
struct formula simplifyAS(struct formula fml){//递归计算式子中加减法（不考虑括号变化）
    int i=0;
    struct num temp;
    for(i=0;i<fml.numcount-1;i++){
        if(fml.oper[i+1]=='+'||fml.oper[i+1]=='-'){
            temp=calculate(fml.figure[i],fml.figure[i+1],fml.oper[i+1]);
            fml.figure[i++]=temp;
            fml.numcount--;
                for(;i<fml.numcount;i++){
                    fml.figure[i]=fml.figure[i+1];
                    fml.oper[i]=fml.oper[i+1];
                }
                fml=simplifyAS(fml);
        }
    }
    return fml;
}
struct formula simplifyBracket(struct formula fml){//递归化简括号
    int i=0;
    struct num temp;
    struct formula ff;;
    for(i=0;i<fml.numcount;i++){
        if(fml.brackets[i]==TRUE){
                int j,k,count;
                if(fml.brackets[i+1]==0) count=3;
                else count=2;
                if(count==2) {//括号中只有2数
                    temp=calculate(fml.figure[i],fml.figure[i+1],fml.oper[i+1]);//计算括号内式子
                    fml.figure[i]=temp;
                    fml.brackets[i]=0;
                    fml.numcount--;
                    i++;
                    for(;i<fml.numcount;i++){
                        fml.figure[i]=fml.figure[i+1];
                        fml.oper[i]=fml.oper[i+1];
                        fml.brackets[i]=fml.brackets[i+1];
                    }
                }
                if(count==3){
                    ff.numcount=count;
                    k=i;
                    for(j=0;j<3;j++,k++){
                        ff.figure[j]=fml.figure[k];
                        ff.oper[j]=fml.oper[k];
                        ff.brackets[j]=0;
                    }
                    ff=simplifyMD(ff);
                    ff=simplifyAS(ff);
                    fml.figure[i]=ff.figure[0];
                    fml.brackets[i]=0;
                    if(i<fml.numcount-3){
                        fml.figure[i+1]=fml.figure[i+3];
                        fml.oper[i+1]=fml.oper[i+3];
                        fml.brackets[i+1]=fml.brackets[i+3];
                    }
                    fml.numcount-=2;
                }
                fml=simplifyBracket(fml);
        }
    }
    return fml;
}
struct num calculateFml(struct formula fml){//计算整个式子的结果
    struct formula fml0;
    fml0=simplifyBracket(fml);
    fml0=simplifyMD(fml0);
    fml0=simplifyAS(fml0);
    return fml0.figure[0];
}
void numInFile(FILE *fp,struct num c1){//写入文件：真分数
    if(fp==NULL){
        printf("数据写入失败");
    }else{
        int g=gcd(c1.mol,c1.den);
        if(g>1){
            c1.den/=g;
            c1.mol/=g;
        }
        if(c1.den==1) fprintf(fp,"%d",c1.mol);
        else if(c1.den<c1.mol){
            int z=c1.mol/c1.den;
            int r=c1.mol%c1.den;
            fprintf(fp,"%d'%d/%d",z,r,c1.den);
        }else fprintf(fp,"%d/%d",c1.mol,c1.den);
       fprintf(fp,"\n");
    }
    return ;
}
void getAnswers(char input[]){//将输入的答案转入全局变量an[3];
    char  *zh,*mol,*den;
    int z,m,d;
    zh=strtok(input,"'");
    mol=strtok(NULL,"/");
    den=strtok(NULL," ");
    if(!mol){//整数不存在
        mol=strtok(zh,"/");
        den=strtok(NULL,"");
        zh="  ";
    }
    z=atoi(zh);
    m=atoi(mol);
    d=atoi(den);
    if(!den){//整数
        an[2]=0;
        an[1]=0;
        an[0]=m;
    }else
    if(d==0){
        an[1]=-1;
        an[2]=1;
    }else{
        an[0]=z;
        an[1]=m;
        an[2]=d;
    }
    return ;
}
void printResult(int result[],int n){//打印结果
    int i,correct=0,wrong=0;
    printf("Correct:(");
    for(i=1;i<n;i++){
        if(correct>0) printf(",");
        if(result[i]==TRUE) {
                printf("%d",i);
                correct++;
        }
    }
    printf("),共%d题\n",correct);
    printf("Wrong:(");
    for(i=1;i<n;i++){
        if(wrong>0) printf(",");
        if(result[i]==TRUE) {
                printf("%d",i);
                wrong++;
        }
    }
    printf("),共%d题\n",wrong);
}
Status ifRepete(struct formula fmla,struct formula fmlb){
    if(fmla.numcount!=fmlb.numcount) return FALSE;
    int n=fmla.numcount;
    struct num ans1,ans2;
    ans1=calculateFml(fmla);
    ans2=calculateFml(fmlb);
    if(ans1.den!=ans2.den||ans1.mol!=ans2.mol) return FALSE;
    int i,j,a[n],b[n],temp;
    for(i=0;i<n;i++){
        a[i]=fmla.figure[i].mol/fmla.figure[i].den;
        b[i]=fmlb.figure[i].mol/fmlb.figure[i].den;
    }
    for(i=0;i<n;i++){//按运算数从小到大排列
        for(j=0;j<n;j++){
            if(a[j]<a[i]){
                temp=a[j];
                a[j]=a[i];
                a[i]=temp;
            }
            if(b[j]<b[i]){
                temp=b[j];
                b[j]=b[i];
                b[i]=temp;
            }
        }
    }
    for(i=0;i<n;i++){
        if(a[i]!=b[i]) return FALSE;
    }
    return TRUE;
}
