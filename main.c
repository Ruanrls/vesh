#include "commands.h"
#include "commandline.h"
#include "exec.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *buff = malloc(sizeof(char) * 100);

	commandline *cmdline = CreateLine();
	commandline *aux;

	while (1)
	{

		printf("\n> ");
		GetCommand(cmdline);
		ExecCommandLine(cmdline);

		cmdline = NULL;
		free(cmdline);
		cmdline = CreateLine();
	}

	return 0;
}