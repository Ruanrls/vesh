#include "commands.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //chamadas de sistema
#include <errno.h>  //para tratar os erros

#define BUFFSIZE 500

int main()
{

    int fileDescriptors[2];
    commandline *command;
    int bytes;

    char *cmd[] = {NULL};

    pipe(fileDescriptors);

    printf("Forking...\n");
    switch (fork())
    {

    case -1:
        printf("Erro ao criar um novo processo!\n");
        exit(EXIT_FAILURE);
        break;

    case 0:
        //filho

        command = GetCommand();
        if (-1 == execvp(command->command, cmd))
        {
            perror("");
        }

        dup2(0, fileDescriptors[1]);

        exit(EXIT_SUCCESS);
        break;

    default:

        //pai
        dup2(fileDescriptors[1], 0);
        break;
    }

    return 0;
}