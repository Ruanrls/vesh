#include "commands.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

commandline *CreateStack()
{
    commandline *cmd = malloc(sizeof(commandline));

    cmd->cmdSize = 0;
    cmd->argSize = 0;
    cmd->command = malloc(sizeof(char) * CMD_MAX_SIZE); //alocamos o espaço total para evitarmos chamada de sistema

    cmd->args = malloc(sizeof(arguments) * ARG_MAX_QUANTITY); //alocamos o espaço total para evitarmos chamada de sistema
    for (int i = 0; i < ARG_MAX_QUANTITY; i++)
    {
        cmd->args[i].arg = calloc(sizeof(char), ARG_MAX_SIZE); //alocamos o espaço total para evitarmos chamada de sistema
        cmd->args[i].size = 0;
    }

    return cmd;
}

void *GetCommand(commandline *cmd)
{
    char key;

    while ((key = getchar()) != '\n')
    {

        switch (key)
        {
        case ' ':
            cmd->argSize++;
            GetArgs(cmd);
            break;

        default:
            InsertChar(cmd, key);
            break;
        }
    }
}

void *GetArgs(commandline *cmd)
{
    char key = 'a';

    while (1)
    {
        key = getchar();

        if (key == '\n' || cmd->argSize == ARG_MAX_QUANTITY)
            break;

        if (key == ' ')
        {
            cmd->argSize++;
            continue;
        }

        InsertArg(cmd, key);
    }
}

int InsertChar(commandline *cmd, char key)
{

    if (cmd->cmdSize == CMD_MAX_SIZE) //buffer cheio
        return FULL;

    cmd->cmdSize++;                       //Aumenta um caractere na variável de controle
    cmd->command[cmd->cmdSize - 1] = key; //Caso não seja um novo argumento
                                          //empilhamos no comando principal

    return SUCCESS;
}

int RemoveChar(commandline *cmd)
{

    if (cmd->cmdSize == 0) //nada a ser retirado
        return EMPTY;

    cmd->command[cmd->cmdSize - 1] = '\0'; //removemos o caractere
    cmd->cmdSize--;

    return SUCCESS;
}

int InsertArg(commandline *cmd, char key) //Insere um caractere na pilha
{
    if (cmd->args[cmd->argSize - 1].size == ARG_MAX_SIZE) //buffer cheio
        return FULL;

    cmd->args[cmd->argSize - 1].size++;
    cmd->args[cmd->argSize - 1].arg[cmd->args[cmd->argSize - 1].size - 1] = key; //insere o caractere no argumento
    return SUCCESS;
}

int RemoveArg(arguments *args) //Remove um caractere da pilha (.pop python)
{
    if (args->size == 0) //nada a ser retirado
        return EMPTY;

    args->arg[args->size - 1] = '\0'; //removemos o caractere
    args->size--;
}

char **ParseArgs(arguments *args)
{
    printf("Teste");
}