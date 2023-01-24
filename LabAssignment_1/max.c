#include <stdio.h>

int main(){
 int num1;
 int num2;
 
 printf("Enter first number: ");
 scanf("%d",&num1);
 
 printf("Enter second number: ");
 scanf("%d",&num2);
 
 int *ptr1; 
 ptr1= &num1;
 int *ptr2; 
 ptr2= &num2;
 
 if (*ptr1 > *ptr2){
    printf("Maximum of both the two numbers: %d\n",*ptr1);
 }else{
    printf("Maximum of both the two numbers: %d\n",*ptr2);
 }


 return 0;
}
