#ifndef COMMANDS_H
#define COMMANDS_H

//constantes de controle
#define CMD_MAX_SIZE 255
#define ARG_MAX_SIZE 50
#define ARG_MAX_QUANTITY 5
#define STDOUT_MAX_BUFF 1000

//minha própria lista de errnos
#define SUCCESS 0
#define FULL 1
#define EMPTY 2

//estrutura de dados que irá conter os caracteres digitados na commandline separando os argumentos
typedef struct
{
    int cmdSize; //Tamanho em caracteres do comando inserido
    int argSize; //Quantidade de argumentos no comando (O proprio comando conta como argumento)
    char **args; //argumentos digitados
} command;

typedef struct Commandline
{
    command *current;

    struct Commandline *prev;
    struct Commandline *next;
} commandline;

//command->prev = null
//command->next null

//command
command *CreateStack();                 //Cria a pilha e a inicializa vazia
void GetCommand(commandline *root);     //Recebe o comando a ser utilizado
int InsertArg(command *cmd, char *key); //Insere um caractere na pilha

//commandline
commandline *CreateLine();
commandline *GetLastCommand(commandline *cmd);
void CreateCommand(commandline *cmd);

#endif