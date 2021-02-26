#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //chamadas de sistema
#include <errno.h>  //para tratar os erros
#include <sys/wait.h>
#include <string.h>

#define BUFFSIZE 500

int main()
{
    char *buff = malloc(sizeof(char) * 100);

    commandline *cmdline = CreateLine();
    commandline *aux;

    GetCommand(cmdline);

    printf("%s\n", cmdline->current->args[0]);
    printf("%c\n", cmdline->nextOperator);

    printf("%s\n", cmdline->next->current->args[0]);

    /* int fileDescriptors[2], bytes;
    command *cmd = CreateStack();

    char buffer[STDOUT_MAX_BUFF] = "\0";

    pipe(fileDescriptors);
    switch (fork())
    {

    case -1:
        printf("Erro ao criar um novo processo!\n");
        exit(EXIT_FAILURE);
        break;

    case 0:
        //filho
        GetCommand(cmd);

        close(fileDescriptors[0]);
        dup2(fileDescriptors[1], 1);

        if (-1 == execvp(cmd->args[0], cmd->args))
        {
            perror("");
        }

        return 0;

    default:
        //pai
        wait(NULL);
        close(fileDescriptors[1]);

        bytes = read(fileDescriptors[0], &buffer, STDOUT_MAX_BUFF);

        close(fileDescriptors[0]);

        printf("Vamos testar o buffer: \n\n%s", buffer);

        break;
    }
 */
    return 0;
}