#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5
char ** strtoken(char *item, char search){
    char **ret = (char **)calloc(1024, sizeof(char*));
    for(int i = 0; i<1024; i++){
        *(ret+i) = (char *)calloc(1024, sizeof(char));
    }
    int m = 0;
    int n = 0;

    for(int i=0; (*(item+i)!='\0'); i++){
        
        int asd = 0;
        if (*(item+i)<31 || *(item+i)>126){
            
            asd = 1;
        }
        
        if(*(item+i) == search){
            m++;
            n=0;
        }else{
            if(asd!=1){
                ret[m] = (char *)realloc(ret[m], n+1);
                ret[m][n] = *(item+i);
                n++;
            }
        }
    }

    ret[m] = (char *)realloc(ret[m], n+1);
    ret[m][n] = '\0';

    return ret;

}

char* kth_word_in_mth_sentence_of_nth_paragraph(char**** document, int k, int m, int n) {
   return *(*(*(document+n-1)+m-1)+k-1);
}

char** kth_sentence_in_mth_paragraph(char**** document, int k, int m) { 
    return *(*(document+m-1)+k-1);
}

char*** kth_paragraph(char**** document, int k) {
    return *(document+k-1);
}

char**** get_document(char* text) {

    char ****Doc = (char ****)malloc(sizeof(char ***)*MAX_PARAGRAPHS);
    for(int i =0 ; i< MAX_PARAGRAPHS; i++){
        (*(Doc+i)) = (char ***)calloc(50, sizeof(char **));
        for(int j =0; j<50; j++){
            (*(*(Doc+i)+j)) = (char **)calloc(50, sizeof(char *));

            for(int k =0; k<MAX_CHARACTERS; k++){
                (*(*(*(Doc+i)+j)+k))= (char*)calloc(MAX_CHARACTERS, sizeof(char));
                memset(((*(*(*(Doc+i)+j)+k))), '\0', MAX_CHARACTERS*sizeof(char));
            }
             
        }
    }
    



    char **paragraph = strtoken(text, '\n');
    int i = 0;
    while(*paragraph[i] != '\0'){
        
        char **sentence = strtoken(paragraph[i], '.');
        int j=0;
        while(*sentence[j] != '\0'){
            
            char **word = strtoken(sentence[j], ' ');
            int k =0;
            while(*word[k] != '\0'){
                                
                strcpy((*(*(*(Doc+i)+j)+k)), (word[k]));
                k++;
            }
            

            j++;
        }
        

        i++;  
    }
    
    return Doc;
}


char* get_input_text() {	
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

void print_word(char* word) {
    printf("%s", word);
}

void print_sentence(char** sentence) {
    int word_count;
    scanf("%d", &word_count);
    for(int i = 0; i < word_count; i++){
        printf("%s", sentence[i]);
        if( i != word_count - 1)
            printf(" ");
    }
} 

void print_paragraph(char*** paragraph) {
    int sentence_count;
    scanf("%d", &sentence_count);
    for (int i = 0; i < sentence_count; i++) {
        print_sentence(*(paragraph + i));
        printf(".");
    }
}

int main() 
{
    char* text = get_input_text();
    char**** document = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            char* word = kth_word_in_mth_sentence_of_nth_paragraph(document, k, m, n);
            print_word(word);
        }

        else if (type == 2){
            int k, m;
            scanf("%d %d", &k, &m);
            char** sentence = kth_sentence_in_mth_paragraph(document, k, m);
            print_sentence(sentence);
        }

        else{
            int k;
            scanf("%d", &k);
            char*** paragraph = kth_paragraph(document, k);
            print_paragraph(paragraph);
        }
        printf("\n");
    }     
}