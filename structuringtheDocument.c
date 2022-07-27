#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

struct word {
    char* data;
};

struct sentence {
    struct word* data;
    int word_count;//denotes number of words in a sentence
};

struct paragraph {
    struct sentence* data  ;
    int sentence_count;//denotes number of sentences in a paragraph
};


struct document {
    struct paragraph* data;
    int paragraph_count;//denotes number of paragraphs in a document
};


char ** strtoken(char *item, char search){
    char **ret = (char **)malloc(sizeof(char*)*1024);
    for(int i = 0; i<1024; i++){
        *(ret+i) = (char *)malloc(sizeof(char)*1024);
    }
    int m = 0;
    int n = 0;

    for(int i=0; *(item+i)!='\0'; i++){
        
        if(*(item+i) == search){
            m++;
            n=0;
        }else{
            ret[m] = (char *)realloc(ret[m], n+1);
            ret[m][n] = *(item+i);
            n++;
        }
    }
    

    return ret;
        
}


struct document get_document(char* text) {
    struct document* Doc = (struct document*)malloc(sizeof(struct document));
    Doc->data = (struct paragraph *)malloc(sizeof(struct paragraph)*5);
    for(int i=0; i<5; i++){
        Doc->data[i].data = (struct sentence *)calloc(100, sizeof(struct sentence));
        for(int j=0; j<100; j++){
            Doc->data[i].data[j].data = (struct word *)calloc(100, sizeof(struct word));
            
            for(int k =0; k<100; k++){
                Doc->data[i].data[j].data[k].data = (char*)calloc(100, sizeof(char));
                memset(Doc->data[i].data[j].data[k].data, '\0', 100);
            }
            
        }

    }
    
    char **paragraph = strtoken(text, '\n');
    int i = 0;
    while(*paragraph[i] != '\0'){
        
        char **sentence = strtoken(paragraph[i], '.');
        int j=0;
        while(*sentence[j] != '\0' && *sentence[j] != '\1'){
            
            char **word = strtoken(sentence[j], ' ');
            int k =0;
            while(*word[k] != '\0'){
                
                Doc->data[i].data[j].word_count +=1;
                strcpy(Doc->data[i].data[j].data[k].data, (word[k]));
                //Doc->data[i].data[j].data[k].data = (char *) realloc(Doc->data[i].data[j].data[k].data, k+1*sizeof(char));
                k++;
            }
            
            Doc->data[i].sentence_count +=1; 
            //Doc->data[i].data[j].data = (struct word *)realloc(Doc->data[i].data[j].data, j+1*sizeof(struct word));
            j++;
        }
        
        Doc->paragraph_count += 1;
        //Doc->data[i].data = (struct sentence *)realloc(Doc->data[i].data, i+1*sizeof(struct sentence));
        i++;  
    }
    
    return *Doc;
}

struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc, int k, int m, int n) {
    return Doc.data[n-1].data[m-1].data[k-1];
}

struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m) { 
    return Doc.data[m-1].data[k-1];
}

struct paragraph kth_paragraph(struct document Doc, int k) {
    return Doc.data[k-1];
}

void print_word(struct word w) {
    printf("%s", w.data);
}

void print_sentence(struct sentence sen) {
    for(int i = 0; i < sen.word_count; i++) {
        print_word(sen.data[i]);
        if (i != sen.word_count - 1) {
            printf(" ");
        }
    }
}

void print_paragraph(struct paragraph para) {
    for(int i = 0; i < para.sentence_count; i++){
        print_sentence(para.data[i]);
        printf(".");
    }
}

void print_document(struct document doc) {
    for(int i = 0; i < doc.paragraph_count; i++) {
        print_paragraph(doc.data[i]);
        if (i != doc.paragraph_count - 1)
            printf("\n");
    }
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

int main() 
{
    char* text = get_input_text();
    struct document Doc = get_document(text);

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
            print_word(w);
        }

        else if (type == 2) {
            int k, m;
            scanf("%d %d", &k, &m);
            struct sentence sen= kth_sentence_in_mth_paragraph(Doc, k, m);
            print_sentence(sen);
        }

        else{
            int k;
            scanf("%d", &k);
            struct paragraph para = kth_paragraph(Doc, k);
            print_paragraph(para);
        }
        printf("\n");
    }     
}