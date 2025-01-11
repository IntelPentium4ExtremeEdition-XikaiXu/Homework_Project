#include<stdio.h>

int main(void){
    int a = 0,c;
    int b = 3;
    int *i ;
    int *j ;
    int *h; 
    i = &a;
    j = &b;
    c = j - i; //init - last
    h = i + c; // 
    printf("%p,%p,%d,%p",i,j,c,h);
}