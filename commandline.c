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

commandline *CreateCommandLine(commandline *cmd, char key)
{
    commandline *last = GetLastCommand(cmd);
    last->nextOperator = key;

    commandline *aux = CreateLine();

    aux->prev = last;
    last->next = aux;

    aux->current = CreateStack();

	return aux;
}

void GetCommand(commandline *root)
{
    commandline *commandNode = GetLastCommand(root);
    command *cmd = commandNode->current;
	command *new = NULL;

    char string[ARG_MAX_SIZE] = "\0";
    char key;

    int flagSpace = 0;
    int flagPipe = 0;

    setbuf(stdin, NULL);

    while (cmd->cmdSize < CMD_MAX_SIZE && cmd->argSize < ARG_MAX_QUANTITY)
    {
        key = getchar();	
        if (key == '\n')
        {
            AddComand(cmd, string);
			if(flagSpace)
				cmd->argSize--;
            break;
        }

        cmd->cmdSize++;
        if (key == ' ')
        {
            flagSpace = 1;
            if (flagPipe)
            {
                flagPipe = 0;
                continue;
            }

			AddComand(cmd, string);
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
                AddComand(cmd, string);
            }

            commandNode = CreateCommandLine(root, key);
            cmd = commandNode->current;
			continue;
        }

    	sprintf(string, "%s%c", string, key);
    }

	if(cmd->argSize == 0)
	{
    	cmd->args[cmd->argSize+1] = NULL;
	}
}