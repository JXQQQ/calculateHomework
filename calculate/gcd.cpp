#include<stdio.h>
int gcd(int numa,int numb){
  if(numb==0) return numa;
  return gcd(numb,numa%numb);
}//求最大公约数
