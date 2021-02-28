#include "commands.h"
#include "commandline.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

command *CreateStack()
{
    command *cmd = malloc(sizeof(command));

    cmd->cmdSize = 0;
    cmd->argSize = 0;

    cmd->args = malloc(sizeof(char *) * ARG_MAX_QUANTITY);

    for (int i = 0; i < ARG_MAX_QUANTITY; i++)
    {
        cmd->args[i] = (char *)calloc(sizeof(char), ARG_MAX_SIZE); //alocamos o espaço total para evitarmos chamada de sistema
    }

    return cmd;
}