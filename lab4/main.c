#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/fcntl.h>
#include <semaphore.h>

void log(FILE *f){
    fprintf(f, "Logging by process with id %d\n", getpid());
}

void solution(FILE *f){
    sem_t *sem1;
    sem_t *sem2;
    sem1 = sem_open("/00001",  O_CREAT | O_EXCL, 0777, 1);
    sem2 = sem_open("/00002",  O_CREAT | O_EXCL, 0777, 0);

    int n = 5;

    if(fork()) {
        for(int i = 0; i<=n; i++){
            sem_wait(sem1);
            log(f);
            sem_post(sem2);
        }
        sem_unlink("/00001");

    } else {
        for(int i = 0; i<=n; i++){
            sem_wait(sem2);
            log(f);
            sem_post(sem1);
        }
        sem_unlink("/00002");
    } 
}

void main(int argc, char* argv[]) {
    FILE *f = fopen("log.txt", "a");
    solution(f);
}
