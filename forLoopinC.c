#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>



int main() 
{
    int a, b;
    scanf("%d\n%d", &a, &b);
  	// Complete the code.
    char *str;

    for(int i = a; (i<=b); i++){
        switch (i) {
            case 1: str = "one\0"; break;
            case 2: str = "two\0"; break;
            case 3: str = "three\0"; break;
            case 4: str = "four\0"; break;
            case 5: str = "five\0"; break;
            case 6: str = "six\0"; break;
            case 7: str = "seven\0"; break;
            case 8: str = "eight\0"; break;
            case 9: str = "nine\0"; break;
            default: str=(i%2==0) ? "even\0":"odd\0"; break;
        }
        
        printf("%s\n", str);

    }

    return 0;
}

