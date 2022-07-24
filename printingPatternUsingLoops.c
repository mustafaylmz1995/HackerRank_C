#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int min(int a, int b){
    return (a<b)? a:b;
}

int main() 
{

    int n;
    scanf("%d", &n);
  	// Complete the code to print the pattern.
    int total = 2*n-1;
    for(int x=0; x<total; x++){
        for(int y=0; y<total; y++){

            int l = min(x,y);
            l = min(l, total-x-1);
            l = min(l, total-y-1);
            printf("%d ", n-l);
        }
        printf("\n");
    }

      
    return 0;
}

