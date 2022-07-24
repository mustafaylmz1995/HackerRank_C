#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
//Complete the following function.


void calculate_the_maximum(int n, int k) {
  //Write your code here.
  int maxAnd = 0;
  int maxOr = 0;
  int maxExor = 0;
  
  for(int i=1; i<n; i++){ //a
    for(int j=i+1; j<n+1; j++){ //b
        int resAnd = i&j;
        int resOr = i|j;
        int resExor = i^j;
        
        maxAnd = (resAnd>maxAnd && resAnd<k) ? resAnd : maxAnd ;
        maxOr = (resOr>maxOr && resOr<k) ? resOr : maxOr ;
        maxExor = (resExor>maxExor && resExor<k) ? resExor : maxExor ;
  
    }
  }

    printf("%d\n%d\n%d\n", maxAnd, maxOr, maxExor);
  
  
}

int main() {
    int n, k;
  
    scanf("%d %d", &n, &k);
    calculate_the_maximum(n, k);
 
    return 0;
}
