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
}

int main()
{
    int fd1[2];

    char input_str[100];

    if (pipe(fd1) == -1)
    {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }

    scanf("%s", input_str);

    if (fork())
    {
        printf("if");
        close(fd1[0]);
        write(fd1[1], input_str, strlen(input_str) + 1);
        close(fd1[1]);
    }
    else
    {
        printf("else");
        close(fd1[1]);
        char str[100];
        read(fd1[0], str, 100);

        char* result_str=str_toupper(str);

        result_str[strlen(result_str)] = '\0';

        printf("Result string is %s", result_str);

        close(fd1[0]);
        exit(0);
    }
    printf("end");

}
