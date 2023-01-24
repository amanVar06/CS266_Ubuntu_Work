#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *ptr = NULL;
    char string[] = "my name is aman varshney";
    
    //writing in a file
    ptr = fopen("myfile.txt","w");
    fprintf(ptr, "%s", string);
    
    fclose(ptr);
   
    return 0;
}

