#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *ptr1 = NULL;
    FILE *ptr2 = NULL;
    FILE *ptr3 = NULL;

    char c1, c2;
    
    ptr1 = fopen("random.txt","r");
    ptr2 = fopen("random2.txt","r");
    ptr3 = fopen("new.txt","w");
    
    c1 = fgetc(ptr1);
    c2 = fgetc(ptr2);
    
    while(c1 != EOF){

        fputc(c1, ptr3);
        c1 = fgetc(ptr1);
    }

    while(c2 != EOF){
        fputc(c2, ptr3);
        c2 = fgetc(ptr2);
    }
  
    fclose(ptr1);
    fclose(ptr2);
    fclose(ptr3);
    
    return 0;
}
