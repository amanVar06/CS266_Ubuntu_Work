/*
void printFibonacciUpToNTerms(int n)
{
    int f1 = 0, f2 = 1, i;
    printf("\n");

    if (n < 1)
        return;
    printf("%d ", f1);
    for (i = 1; i < n; i++)
    {
        printf("%d ", f2);
        int next = f1 + f2;
        f1 = f2;
        f2 = next;
    }
    printf("\n");
}


void allocateMemory(int *ptr, int n)
{
    ptr = (int *)malloc(n * sizeof(int));
    if (ptr == NULL)
    {
        printf("Memory not allocated.\n");
        exit(0);
    }
    else
    {

        // Memory has been successfully allocated
        printf("Memory successfully allocated using malloc.\n");

        // Get the elements of the array
        for (int i = 0; i < n; ++i)
        {
            ptr[i] = fibonacciNumberAtIndex(i);
        }

        // Print the elements of the array
        printf("The elements of the array are: \n");
        for (int i = 0; i < n; ++i)
        {
            printf("%d, ", ptr[i]);
        }
    }
}


int BuddySystem(int S[], int m, int n ){
   
    int i, j, x, y;
 
    // We need n+1 rows as the table is constructed
    // in bottom up manner using the base case 0
    // value case (n = 0)
    int table[n+1][m];
    
    // Fill the entries for 0 value case (n = 0)
    for (i=0; i<m; i++)
        table[0][i] = 1;
 
    // Fill rest of the table entries in bottom
    // up manner 
    for (i = 1; i < n+1; i++)
    {
        for (j = 0; j < m; j++)
        {
            // Count of solutions including S[j]
            x = (i-S[j] >= 0)? table[i - S[j]][j]: 0;
 
            // Count of solutions excluding S[j]
            y = (j >= 1)? table[i][j-1]: 0;
 
            // total count
            table[i][j] = x + y;
        }
    }
    return table[n][m-1];

}


*/