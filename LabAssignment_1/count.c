#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *ptr = NULL;
    char c;
    int wrd_cnt = 0;
    int chr_cnt = 0;
    
    ptr = fopen("random.txt","r");
    
    c = fgetc(ptr);
    printf("Content of the file: \n");
    
    while(c != EOF){
        printf("%c",c);
        
        if(c == ' ' || c == '\n'){
            wrd_cnt++;
        }else{
            chr_cnt++;
        }
        c = fgetc(ptr);
    }
    
    printf("\nNumber of Characters: %d\n",chr_cnt);
    printf("Number of Words: %d\n",wrd_cnt);
    

    fclose(ptr);
    return 0;
}
