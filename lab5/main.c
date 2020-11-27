#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <ctype.h>

char* str_toupper(char *str)
{
    int i;
    for (i = 0; i < strlen(str); i++)
        str[i] = toupper(str[i]);
    
    return str;
}

int main()
{
    int my_pipe[2];
    char input_str[100];

    if (pipe(my_pipe) == -1)
    {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }

    scanf("%s", input_str);

    if (fork())
    {
        close(my_pipe[0]);
        write(my_pipe[1], input_str, strlen(input_str) + 1);
        close(my_pipe[1]);
    }
    else
    {
        close(my_pipe[1]);
        char str[100];
        read(my_pipe[0], str, 100);

        char* result_str=str_toupper(str);

        printf("Result string is %s", result_str);

        close(my_pipe[0]);
        exit(0);
    }
}
