#include<stdio.h> 
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<string.h> 
#include<sys/wait.h> 
#include<ctype.h>
  
int main() 
{ 
    int fd1[2];
  
    char input_str[100]; 
    pid_t p; 
  
    if (pipe(fd1)==-1) { 
        fprintf(stderr, "Pipe Failed" ); 
        return 1; 
    } 

    scanf("%s", input_str); 
    p = fork(); 
  
    if (p > 0) 
    { 
        char result_str[100]; 
  
        close(fd1[0]); 
  
        write(fd1[1], input_str, strlen(input_str)+1); 
        close(fd1[1]); 
    } 
    else
    { 
        close(fd1[1]);
  
        char result_str[100]; 
        read(fd1[0], result_str, 100); 
  
        int k = strlen(result_str); 
        int i; 
        for (i=0; i<k; i++) 
            result_str[i] = toupper(result_str[i]); 
  
        result_str[i] = '\0';
  
        printf("Result string is %s", result_str);

        close(fd1[0]); 
        exit(0); 
    } 
}
