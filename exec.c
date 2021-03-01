#include "exec.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> //chamadas de sistema
#include <errno.h>	//para tratar os erros
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>

void ExecCommandLine(commandline *cmd)
{
	int pid;
	int fd[2];
	int fd2[2];
	int status = -1;

	commandline *node = cmd;

	CheckExit(cmd->current);
	if (cmd->next == NULL) //single command
	{
		pid = fork();

		if (pid == -1)
		{
			printf("Erro ao criar um novo processo!\nSaindo...");
			exit(2);
		}
		else if (pid == 0)
		{
			ExecCommand(cmd->current);
		}
		return;
	}

	do
	{
		CheckExit(node->current);
		if (node->nextOperator == '>' || node->nextOperator == '<')
		{
			node = ExecArchiveCommand(node); //executa o comando de arquivo e retorna o no atual
		}
		else
		{
			if (node->current->id % 2 != 0)
				pipe(fd);
			else
				pipe(fd2);

			switch (fork())
			{
			case -1:
				printf("Falha ao criar novo processo!\nSaindo...");
				exit(EXIT_FAILURE);

			case 0:

				//caso seja o primeiro comando
				if (node->current->id == 0)
				{
					dup2(fd2[1], 1);
				}
				else if (node->current->id == node->qntCommands) //caso seja o último comando
				{
					if (node->qntCommands % 2 != 0)
						dup2(fd[0], STDIN_FILENO);

					else
						dup2(fd2[0], STDIN_FILENO);
				}
				else //caso seja os demais comandos
				{
					if (node->current->id % 2 != 0)
					{
						dup2(fd2[0], STDIN_FILENO);
						dup2(fd[1], STDOUT_FILENO);
					}
					else
					{
						dup2(fd[0], STDIN_FILENO);
						dup2(fd2[1], STDOUT_FILENO);
					}
				}

				ExecCommand(node->current);

				exit(0);
			default:

				if (node->current->id == 0) //caso seja o primeiro comando
				{
					close(fd2[1]);
				}
				else if (node->current->id == node->qntCommands) //caso seja o último comando
				{
					if (node->qntCommands % 2 != 0)
					{
						close(fd[0]);
					}
					else
					{
						close(fd2[0]);
					}
				}
				else
				{
					if (node->current->id % 2 != 0)
					{
						close(fd2[0]);
						close(fd[1]);
					}
					else
					{
						close(fd[0]);
						close(fd2[1]);
					}
				}

				waitpid(pid, NULL, 0);
			}
		}

		if (node->next == NULL)
			break;

		node = node->next;
	} while (node != NULL);

	setbuf(stdin, NULL);
}

void ExecCommand(command *cmd)
{
	if (-1 == execvp(cmd->args[0], cmd->args))
	{
		perror("Error: ");
		printf("\n");
		exit(2);
	}
}

commandline *ExecArchiveCommand(commandline *cmd)
{
	int fdArchive;
	int pid = fork();

	if (pid == -1)
	{
		printf("Erro ao criar um processo!\nSaindo...");
		exit(2);
	}
	else if (pid == 0)
	{
		if (cmd->nextOperator == '>')
		{
			fdArchive = open(cmd->next->current->args[0], O_CREAT | O_TRUNC | O_WRONLY, 0600);
			dup2(fdArchive, STDOUT_FILENO);
		}
		else if (cmd->nextOperator == '<')
		{
			fdArchive = open(cmd->next->current->args[0], O_RDONLY, 0600);
			dup2(fdArchive, STDIN_FILENO);
			close(fdArchive);

			fdArchive = open(cmd->next->current->args[0], O_CREAT | O_TRUNC | O_WRONLY, 0600);
			dup2(fdArchive, STDOUT_FILENO);
		}

		if (execvp(cmd->current->args[0], cmd->current->args) == -1)
		{
			perror("Error: ");
			printf("\n");
			exit(2);
		}
	}

	wait(NULL);
	close(fdArchive);

	return cmd->next;
}

void CheckExit(command *current)
{
	if (strncmp(current->args[0], "exit", 4) == 0)
	{
		printf("Ty, feel free to come back!\n");
		exit(0);
	}
}