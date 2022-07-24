#include <stdio.h>
#include <stdlib.h>

int main()
{
    int num, *arr, i;
    scanf("%d", &num);
    arr = (int*) malloc(num * sizeof(int));
    for(i = 0; i < num; i++) {
        scanf("%d", arr + i);
    }


    /* Write the logic to reverse the array. */
    //num --> 6
    //arr_i    0 1 2 3 4  5
    //arr --> 12 1 2 7 13 16
    int *new_arr = (int*) malloc(num * sizeof(int));
    for (int i = 0; i<num; i++){
        *(new_arr+i) = arr[num-i-1];
    }
    arr = new_arr;
    
    for(i = 0; i < num; i++)
        printf("%d ", *(arr + i));
    
    
    return 0;
}
