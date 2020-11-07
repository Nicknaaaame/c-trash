#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h> 

void log(){
    printf("Logging by process with id %d\n", getpid());
    sleep(1);
}

void solution(){
    sem_t *sem1;
    sem_t *sem2;
    // sem_init(&sem1,0, 1);
    // sem_init(&sem2,0, 0);

    sem1 = sem_open("1", O_CREAT | O_EXCL, 0777, 1);
    sem2 = sem_open("2", O_CREAT | O_EXCL, 0777, 0);

    if(sem1==-1||sem2==-1){
        printf("ERR");
        return(-1);
    }
    
    pid_t pid1 = fork();
    pid_t pid2 = fork();
    int n = 5;

    if(pid1==0&&pid2>0) {
        for(int i = 0; i<n; i++){
            sem_wait(sem1);
            log();
            printf("1------------------\n");
            sem_post(sem2);
        }
    }
    if(pid1>0 && pid2==0) {
        for(int i = 0; i<n; i++){
            sem_wait(sem2);
            log();
            printf("2\n");
            sem_post(sem1);
        }      
    }
}

void main(int argc, char* argv[]) {
    solution();
}
