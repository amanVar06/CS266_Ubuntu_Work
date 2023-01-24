#include <stdio.h>
int main()
{
    char *str;
    str = "aman varshney";
    int len = 0;
    int i = 0;

    while (*(str + i) != '\0')
    {
        len++;
        i++;
    }
    
    printf("length of the string: %d\n",len);
    return 0;
}

