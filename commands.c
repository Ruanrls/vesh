#include "commands.h"
#include <stdlib.h>
#include <stdio.h>

command *CreateStack()
{
    command *cmd = malloc(sizeof(command));

    cmd->n = 0;
    cmd->key = malloc(CMD_MAX_BUFF_SIZE); //Alocamos o tamanho máximo possível para não executarmos várias chamadas de sistema
    //ao adicionar um novo caractere na pilha

    return cmd;
}

char *GetCommand()
{
    command *cmd = CreateStack();
    char key;

    while ((key = getchar()) != '\n')
    {
        InsertChar(cmd, key);
    }

    return cmd->key;
}

int InsertChar(command *cmd, char key)
{

    if (cmd->n == CMD_MAX_BUFF_SIZE)
    {
        return FULL;
    }

    cmd->n++;
    cmd->key[cmd->n - 1] = key;
    return SUCCESS;
}

int RemoveChar(command *cmd)
{

    if (cmd->n == 0)
        return EMPTY;

    cmd->key[cmd->n - 1] = '\0';
    cmd->n--;

    return SUCCESS;
}