#include <stdio.h>
int main()
{
    int arr[] = {2,5,1,4,9,3,7,0,6,8};
    int *ptr = arr;
    int n = 10;
    int temp;
    
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i -1; j++)
        {
            if (*(ptr + j) > *(ptr + j + 1))
            {
                temp = *(ptr + j);
                *(ptr + j) = *(ptr + j + 1);
                *(ptr + j + 1) = temp;
            }
            
        }
        
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d ",*(ptr + i));
    }
    printf("\n");   
    
    return 0;
}

