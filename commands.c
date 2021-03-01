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
	cmd->id = 0;

	cmd->args = malloc(sizeof(char *) * ARG_MAX_QUANTITY);

	for (int i = 0; i < ARG_MAX_QUANTITY; i++)
	{
		cmd->args[i] = (char *)calloc(sizeof(char), ARG_MAX_SIZE); //alocamos o espaço total para evitarmos chamada de sistema
		cmd->args[i][0] = '\0';
	}

	return cmd;
}

void AddComand(command *cmd, char *buffer)
{
	if (cmd->argSize == ARG_MAX_QUANTITY - 1)
	{
		printf("Muitos argumentos passados!\n");
		exit(0);
	}

	strcat(buffer, "\0");

	cmd->argSize++;

	if (strlen(buffer) == 0)
	{
		printf("Sem buffer\n");
		exit(0);
	}

	strcpy(cmd->args[cmd->argSize - 1], buffer);

	buffer[0] = '\0';
}