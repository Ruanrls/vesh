#include "commands.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

commandline *CreateStack()
{
    commandline *cmd = malloc(sizeof(commandline));

    cmd->cmdSize = 0;
    cmd->argSize = 0;

    cmd->args = malloc(sizeof(char **) * ARG_MAX_QUANTITY);

    for (int i = 0; i < ARG_MAX_QUANTITY; i++)
    {
        cmd->args[i] = (char *)calloc(sizeof(char), ARG_MAX_SIZE); //alocamos o espaço total para evitarmos chamada de sistema
    }

    return cmd;
}

void GetCommand(commandline *cmd)
{
    char string[ARG_MAX_SIZE] = "\0";
    char key;

    int *argSize = &(cmd->argSize), *cmdSize = &(cmd->cmdSize);

    while (cmd->cmdSize < CMD_MAX_SIZE && cmd->argSize < ARG_MAX_QUANTITY)
    {
        key = getchar();

        if (key == '\n')
        {
            strcpy(cmd->args[cmd->argSize], string);
            if (strlen(cmd->args[cmd->argSize]) == 0)
                break;
            cmd->argSize++;
            break;
        }
        else if (key == ' ')
        {
            strcpy(cmd->args[cmd->argSize], string);
            string[0] = '\0';
            cmd->argSize++;
            cmd->cmdSize++;
            continue;
        }

        sprintf(string, "%s%c", string, key);
        cmd->cmdSize++;
    }
}