#include <stdio.h>

void update(int *a,int *b) {
    // Complete this function 
    int absDiff=0;
    int sum=0;
    if(*a>*b){
        absDiff = *a - *b;
    }else{
        absDiff = *b - *a;
    }
    
    sum = *a + *b;
       
    *a = sum;
    *b = absDiff;
}

int main() {
    int a, b;
    int *pa = &a, *pb = &b;
    
    scanf("%d %d", &a, &b);
    update(pa, pb);
    printf("%d\n%d", a, b);

    return 0;
}
