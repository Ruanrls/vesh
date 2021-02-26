#include "commands.h"
#include <stdlib.h>
#include <stdio.h>
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

void GetCommand(commandline *root)
{
    commandline *commandNode = GetLastCommand(root);
    command *cmd = commandNode->current;

    char string[ARG_MAX_SIZE] = "\0";
    char key;

    int flagSpace = 0;
    int flagPipe = 0;

    int *argSize = &(cmd->argSize);
    int *cmdSize = &(cmd->cmdSize);

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
            if (flagPipe)
            {
                flagPipe = 0;
                continue;
            }

            strcpy(cmd->args[cmd->argSize], string);
            string[0] = '\0';
            cmd->argSize++;
            cmd->cmdSize++;
            flagSpace = 1;
            continue;
        }
        else if (key == '|')
        {
            flagPipe = 1;

            if (flagSpace)
            {
                cmd->argSize--;
                flagSpace = 0;
            }
            else
            {
                strcpy(cmd->args[cmd->argSize], string);
                string[0] = '\0';
                cmd->argSize++;
                cmd->cmdSize++;
            }

            CreateCommand(root);
            cmd = commandNode->next->current;
            argSize = &(cmd->argSize);
            cmdSize = &(cmd->cmdSize);
            continue;
        }

        sprintf(string, "%s%c", string, key);
        cmd->cmdSize++;
    }
    cmd->args[cmd->argSize] = NULL;
}

commandline *CreateLine()
{
    commandline *cmd = malloc(sizeof(command));

    cmd->current = CreateStack();
    cmd->next = NULL;
    cmd->prev = NULL;

    return cmd;
}

commandline *GetLastCommand(commandline *cmd)
{
    if (NULL == cmd->next || NULL == cmd->current)
        return cmd;

    return GetLastCommand(cmd->next);
}

void CreateCommand(commandline *cmd)
{

    commandline *last = GetLastCommand(cmd);
    commandline *aux = CreateLine();

    aux->prev = last;
    last->next = aux;

    aux->current = CreateStack();
}