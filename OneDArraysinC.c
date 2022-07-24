#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int arrSize = 0;
    scanf("%d", &arrSize);
    int *arr = (int *)malloc(arrSize * sizeof(int));
    
    for(int i = 0; i<arrSize; i++){
        scanf("%d", &arr[i]);
    }
    
    int sum = 0;
    
    for(int i = 0; i<arrSize; i++){
        sum += arr[i];
    }
    printf("%d\n", sum);
    
    free(arr);
    
     
    return 0;
}
