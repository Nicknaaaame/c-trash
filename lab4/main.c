#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h> 

void log(){
    printf("Logging by process with id %d\n", getpid());
    // sleep(1);
}

void solution(){
    sem_t *sem1;
    sem_t *sem2;
    sem1 = sem_open("p1",  O_CREAT | O_EXCL, 0644, 1);
    sem2 = sem_open("p2",  O_CREAT | O_EXCL, 0644, 0);

    int n = 500000000;

    if(fork()) {
        for(int i = 0; i>=0; i++){
            printf("p1 %d\n", i);
            sem_wait(sem1);
            //log();
            printf("1\n");
            sem_post(sem2);
            printf("p1 %d\n", i);
        }
    } else {
        for(int i = 0; i>=0; i++){
            printf("p2 %d\n", i);
            sem_wait(sem2);
            //log();
            printf("2\n");
            printf("%d-------\n",sem_post(sem1));
            printf("p2 %d\n", i);
        }      
    } 
}

void main(int argc, char* argv[]) {
    solution();
}
