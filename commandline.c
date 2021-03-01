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
	cmd->qntCommands = 0;

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
	cmd->qntCommands++;

	commandline *aux = CreateLine();
	commandline *last = GetLastCommand(cmd);

	last->nextOperator = key;

	last->next = aux;
	aux->prev = last;
	aux->current = CreateStack();

	aux->current->id = cmd->qntCommands;

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
			if (flagSpace)
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

		flagSpace = 0;
		flagPipe = 0;
		sprintf(string, "%s%c", string, key);
	}

	AddNull(root);
}

void AddNull(commandline *root)
{

	commandline *node = root;

	if (node->current->argSize == 0)
	{
		node->current->argSize++;
	}
	node->current->args[node->current->argSize] = NULL;

	node = node->next;

	while (node != NULL)
	{
		node->current->args[node->current->argSize] = NULL;

		node = node->next;
	}
}