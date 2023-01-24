#include <stdio.h>

int main(){
 int num = 2;
 char chr = 'c';
 char str[5] = "Aman";
 
 int *ptr1 = &num;
 char *ptr2 = &chr;
 char *ptr3 = str;
 
 printf("ptr1 = %p\n",ptr1);
 printf("ptr2 = %p\n",ptr2);
 printf("ptr3 = %p\n",ptr3);
  
 return 0;
}
 
