#include "commands.h"
#include "commandline.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

commandline *CreateLine()
{
    commandline *cmd = malloc(sizeof(command *));

    cmd->current = CreateStack();
    cmd->next = NULL;
    cmd->prev = NULL;
    cmd->nextOperator = '\0';

    return cmd;
}

commandline *GetLastCommand(commandline *cmd)
{
    if (NULL == cmd->next || NULL == cmd->current)
        return cmd;

    return GetLastCommand(cmd->next);
}

void CreateCommand(commandline *cmd, char key)
{
    commandline *last = GetLastCommand(cmd);
    last->nextOperator = key;

    commandline *aux = CreateLine();

    aux->prev = last;
    last->next = aux;

    aux->current = CreateStack();
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

    setbuf(stdin, NULL);

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
        else if ('|' == key || '>' == key || '<' == key)
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

            CreateCommand(root, key);
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