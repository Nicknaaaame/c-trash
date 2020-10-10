#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int* append(int* arr, int el, int size){
    arr = realloc(arr, size+1);
    arr[size] = el;
    return arr;
}

int* create_table(FILE *f, int *table_size) {
    int* table = malloc(sizeof(int)*0);
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);
    char *content = malloc(fsize);
    fread(content, 1, fsize, f);
    
    int str_count = 0;
    table = append(table, -1, str_count++);
    for(int i = 0; i<fsize; ++i){
        if(content[i]=='\n'){
            table = append(table, i, str_count++);
        }
    }
    table = append(table, fsize, str_count++);
    *table_size = str_count;
    return table;
}

// void print_str(FILE *f, int *table, int str_num){
//     int l = table[str_num]+1;
//     fseek(f, l, SEEK_SET);
//     int fsize = table[str_num+1] - l;
//     char *content = malloc(fsize);
//     fread(content, 1, fsize, f);
//     printf("Str with num %d : %s\n",str_num+1, content);
// }

void print_str_via_mmap(FILE *f, int *table, int str_num) {
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);
    int fin = open("test.txt", O_RDONLY);
    char* content = mmap(0, fsize, PROT_READ, MAP_SHARED, fin, 0);

    int str_size = table[str_num+1] - table[str_num]+1;
    char *result = malloc(fsize);

    for(int i = table[str_num]+1, j=0; i<table[str_num+1]; i++, j++){
        result[j]=content[i];
    }

    printf("Str with num %d : %s\n",str_num+1, result);

}

void print_arr(int* arr, int size){
    for(int i = 0; i<size; ++i){
        printf("%d - %d\n", i, arr[i]);
    }
}

void main(){
    FILE *file = fopen("test.txt", "r");
    int table_size;
    int* table = create_table(file, &table_size);
    print_arr(table, table_size);
    int str_num;
    scanf("%d", &str_num);
    while (str_num>0){
        if(str_num>table_size-1){
            printf("Str with num %d is not exist\n", str_num);
        } else {
            print_str_via_mmap(file, table, str_num-1);
        }
        scanf("%d", &str_num);
    }
}