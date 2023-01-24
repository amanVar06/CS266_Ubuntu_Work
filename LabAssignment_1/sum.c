#include <stdio.h>

int main(){
 int num1;
 int num2;
 
 printf("Enter first number: ");
 scanf("%d",&num1);
 
 printf("Enter second number: ");
 scanf("%d",&num2);
 
 int *ptr1 = &num1;
 int *ptr2 = &num2;
 
 printf("sum of both numbers = %d\n",*ptr1+*ptr2);

  
 return 0;
 
}
 
