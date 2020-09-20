#include <stdio.h>
#include "vector.h"

#define N (50)

void kkk(char *buffer, Vector table, int count) {
    for(int i = 0; i<N; ++i ){
        if(buffer[i]=='\n')
            vector_push_back(&table, count*(i+1));
    }
}

void main(){
    FILE *file = fopen("test.txt", "r");
    Vector table;
    int lineNum, count = 0;
    char buffer[N];
    scanf("&d", lineNum);
    while (fscanf(file,"%s" ,buffer)!=EOF) {
        kkk(buffer, table, count);
        count++;
    }
    
}