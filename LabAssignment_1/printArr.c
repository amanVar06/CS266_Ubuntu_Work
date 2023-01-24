#include <stdio.h>
int main()
{
    int n ;
    printf("Enter the size: ");
    scanf("%d",&n);

    int arr[n];
    int *ptr = arr;
    for (int i = 0; i < n; i++)
    {
        scanf("%d",&arr[i]);
    }
    
    printf("Array elements: \n");

    for (int i = 0; i < n; i++)
    {
        printf("%d ",*(ptr + i));
    }
    printf("\n");
    
    return 0;
}



