#ifndef COMMANDS_H
#define COMMANDS_H

//constantes de controle
#define CMD_MAX_SIZE 255
#define ARG_MAX_SIZE 50
#define ARG_MAX_QUANTITY 5

//minha própria lista de errnos
#define SUCCESS 0
#define FULL 1
#define EMPTY 2

typedef struct
{
    int size;  //tamanho em caracteres do argumento
    char *arg; //Argumento
} arguments;

//estrutura de dados que irá conter os caracteres digitados na commandline separando os argumentos
typedef struct Commandline
{
    int cmdSize;     //Tamanho em caracteres do comando inserido (apenas o comando, sem os args)
    int argSize;     //Quantidade de argumentos no comando
    char *command;   //comando principal digitado
    arguments *args; //argumentos digitados
} commandline;

//command line
commandline *CreateStack();                 //Cria a pilha e a inicializa vazia
commandline *GetCommand();                  //recebe o comando a ser utilizado
int InsertChar(commandline *cmd, char key); //Insere um caractere na pilha
int RemoveChar(commandline *cmd);           //Remove um caractere da pilha (.pop python)

//args
int InsertArg(commandline *cmd, char key, int position); //Insere um caractere na pilha
int RemoveArg(arguments *args);                          //Remove um caractere da pilha (.pop python)

#endif