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

    int fileDescriptors[2];
    commandline *command = CreateStack();

    GetCommand(command);

    printf("%d\n", command->argSize);

    for (int i = 0; i < command->argSize; i++)
    {
        printf("-%s-", command->args[i]);
    }

    // switch (fork())
    // {

    // case -1:
    //     printf("Erro ao criar um novo processo!\n");
    //     exit(EXIT_FAILURE);
    //     break;

    // case 0:
    //     //filho
    //     GetCommand(command);

    //     if (-1 == execvp(command->command, cmd))
    //     {
    //         perror("");
    //     }

    //     exit(EXIT_SUCCESS);
    //     break;

    // default:

    //     //pai
    //     wait(NULL);
    //     break;
    // }

    return 0;
}