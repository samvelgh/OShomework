#include <stdio.h>


void swap(int *a, int *b){
    int temp=*a;
    *a=*b;
    *b=temp;
    
    
}

int main() {
    int one=5;
    int two=7;
    int *ptrofone=&one;
    int *ptroftwo=&two;
    printf("Before swap \nval of one: %d\nvalue one two %d\n",one,two);
    swap(ptrofone,ptroftwo);
    printf("after swap \nval of one: %d\nvalue one two %d\n",one,two);
    return 0;
    
}
