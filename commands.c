#include "commands.h"
#include <stdlib.h>
#include <stdio.h>

commandline *CreateStack()
{
    commandline *cmd = malloc(sizeof(commandline));

    cmd->cmdSize = 0;
    cmd->argSize = 0;
    cmd->command = calloc(1, CMD_MAX_SIZE); //alocamos o espaço total para evitarmos chamada de sistema

    cmd->args = malloc(sizeof(arguments) * ARG_MAX_QUANTITY); //alocamos o espaço total para evitarmos chamada de sistema
    for (int i = 0; i < ARG_MAX_QUANTITY; i++)
    {
        cmd->args[i].arg = calloc(sizeof(char), ARG_MAX_SIZE); //alocamos o espaço total para evitarmos chamada de sistema
        cmd->args[i].size = 0;
    }

    printf("Passou do if");

    return cmd;
}

commandline *GetCommand()
{
    commandline *cmd = CreateStack();
    char key;

    while ((key = getchar()) != '\n')
    {
        InsertChar(cmd, key);
    }

    return cmd;
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

int InsertArg(commandline *cmd, char key, int position) //Insere um caractere na pilha
{

    if (cmd->args[position].size == ARG_MAX_SIZE || cmd->argSize == ARG_MAX_QUANTITY) //buffer cheio
        return FULL;

    cmd->args[position].size++;
    cmd->args[position].arg[cmd->args[position].size - 1] = key;
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