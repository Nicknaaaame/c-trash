#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void solution(char** args){
    int id = fork();
    unsigned short status;
    if(id==0){
        printf("Created\n");
        execvp(args[1], &args[1]);    
    } 
    if(id==-1){
        printf("Process wasnt created\n");
    }
    if(id!=0) {
        wait(&status);
        printf("Result code: %d\n", WEXITSTATUS(status));
    }
}

void main(int argc, char* argv[]) {
    // for(int i = 0; i<argc; i++){
    //     printf("%s\n", argv[i]);
    // }
    // solution(argv);
    int id = fork();
    unsigned short status;
    if(id==0){
        printf("Created\n");
        execvp(argv[1], &argv[1]);   
        exit(-1); 
    } 
    if(id==-1){
        printf("Process wasnt created\n");
    }
    if(id!=0) {
        wait(&status);
        printf("Result code: %d\n", WEXITSTATUS(status));
    }
}