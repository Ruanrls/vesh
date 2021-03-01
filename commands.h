#ifndef COMMANDS_H
#define COMMANDS_H

//constantes de controle
#define CMD_MAX_SIZE 255
#define ARG_MAX_SIZE 500
#define ARG_MAX_QUANTITY 5

//minha própria lista de errnos
#define SUCCESS 0
#define FULL 1
#define EMPTY 2

//estrutura de dados que irá conter os caracteres digitados na commandline separando os argumentos
typedef struct
{
	int id;

	int cmdSize; //Tamanho em caracteres do comando inserido
	int argSize; //Quantidade de argumentos no comando (O proprio comando conta como argumento)
	char **args; //argumentos digitados
} command;

//command
command *CreateStack();					//Cria a pilha e a inicializa vazia
int InsertArg(command *cmd, char *key); //Insere um caractere na pilha
void AddComand(command *cmd, char *buffer);
command *concat(command *next, char *buffer);

#endif