#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lexicographic_sort(const char* a, const char* b) {
    int x = strcmp(a, b);
    
    if( x== 0){
        //same not change
        return 1;
    }else if( x>0){
        //b stringi daha once geliyor
        return -1;
    }else{
        //a stringi daha once geliyor
        return 1;
    }
    
    
    
}

int lexicographic_sort_reverse(const char* a, const char* b) {

    int x = strcmp(a, b);
    
    if( x== 0){
        //same not change
        return 1;
    }else if( x>0){
        //b stringi daha once geliyor
        return 1;
    }else{
        //a stringi daha once geliyor
        return -1; //reverse
    }
    
    
}

int sort_by_number_of_distinct_characters(const char* a, const char* b) {
    //find no distinct characters:
    int alphabets[26];
    memset(alphabets, 0, 26*sizeof(int));
    int anoDist = 0;
    int bnoDist = 0;
    
    for(int i=0; *(a+i) != '\0'; i++){
        alphabets[*(a+i)-97]++;
    }
    for(int i=0; i<26; i++){
        if(alphabets[i] != 0){
            anoDist++;
        }
    }
    
    memset(alphabets, 0, 26*sizeof(int));
    for(int i=0; *(b+i) != '\0'; i++){
        alphabets[*(b+i)-97]++;
    }
    
    for(int i=0; i<26; i++){
        if(alphabets[i] != 0){
            bnoDist++;
        }
    }
    
    int x = anoDist-bnoDist;
    if( x == 0){

        return lexicographic_sort(a, b);
        
    }else if( x>0){

        return -1;
    }else{

        return 1; //reverse
    }
    

}

int sort_by_length(const char* a, const char* b) {
    
    int x = strlen(a);
    int y = strlen(b);
    int z = x-y;
    if( z == 0){
        //same length not change
        return lexicographic_sort(a, b);;
    }else if( z>0){
        //b stringi daha once geliyor
        return -1;
    }else{
        //a stringi daha once geliyor
        return 1; //reverse
    }
    
}

void string_sort(char** arr,const int len,int (*cmp_func)(const char* a, const char* b)){

    //an array of strings : arr
    //length of string array: len
    //pointer to the string comparison function: cmp_func
    
    
    //buble sort
    for(int i=0; i<len; i++){
        for(int j= 0; j<len-i-1; j++){

            if(cmp_func(arr[j], arr[j+1]) == -1){
                //need to change
                char strTemp[1024] = {'\0'};
                            
                strcpy(strTemp, arr[j+1]);
                *(arr+j+1) = realloc(*(arr + j+1), strlen(*(arr + j)) + 1);
                strcpy(arr[j+1], arr[j]);
                *(arr + j) = realloc(*(arr + j), strlen(strTemp) + 1);
                strcpy(arr[j], strTemp);
                
            }
            
        }
    }
    
    
}


int main() 
{
    int n;
    scanf("%d", &n);
  
    char** arr;
	arr = (char**)malloc(n * sizeof(char*));
  
    for(int i = 0; i < n; i++){
        *(arr + i) = malloc(1024 * sizeof(char));
        scanf("%s", *(arr + i));
        *(arr + i) = realloc(*(arr + i), strlen(*(arr + i)) + 1);
    }
  
    string_sort(arr, n, lexicographic_sort);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);
    printf("\n");

    string_sort(arr, n, lexicographic_sort_reverse);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");

    string_sort(arr, n, sort_by_length);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]);    
    printf("\n");

    string_sort(arr, n, sort_by_number_of_distinct_characters);
    for(int i = 0; i < n; i++)
        printf("%s\n", arr[i]); 
    printf("\n");
}