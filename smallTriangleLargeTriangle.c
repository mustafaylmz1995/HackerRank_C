#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct triangle
{
	int a;
	int b;
	int c;
};

typedef struct triangle triangle;
void sort_by_area(triangle* tr, int n) {
    /**
    * Sort an array a of the length n
    */
    
    float areaList[n];
    float areaTemp;
    double p;
    triangle trTemp;
    
    for(int i=0; i<n; i++){
        int a = tr[i].a;
        int b = tr[i].b;
        int c = tr[i].c;
        
        p= (a+b+c);
        p /=2;
        areaList[i] = sqrt((p)*(p-a)*(p-b)*(p-c));
    }
    
    for(int i=0; i<n; i++){
        for(int j= 0; j<n-1-i; j++){
            if(areaList[j] > areaList[j+1]){
                areaTemp = areaList[j];
                areaList[j]= areaList[j+1];
                areaList[j+1] = areaTemp;

                trTemp = tr[j];
                tr[j] = tr[j+1];
                tr[j+1] = trTemp;
                
            }
        }
    }


    
    
}


int main()
{
	int n;
	scanf("%d", &n);
	triangle *tr = malloc(n * sizeof(triangle));
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", &tr[i].a, &tr[i].b, &tr[i].c);
	}
	sort_by_area(tr, n);
	for (int i = 0; i < n; i++) {
		printf("%d %d %d\n", tr[i].a, tr[i].b, tr[i].c);
	}
	return 0;
}