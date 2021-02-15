#ifndef COMMANDS_H
#define COMMANDS_H

#define CMD_MAX_BUFF_SIZE 255

//minha própria lista de errnos
#define SUCCESS 0
#define FULL 1
#define EMPTY 2

//estrutura de dados que irá conter os caracteres digitados
typedef struct Command
{
    int n;
    char *key;
} command;

char *GetCommand();                     //recebe o comando a ser utilizado
int InsertChar(command *cmd, char key); //Insere um caractere na pilha
int RemoveChar(command *cmd);           //Remove um caractere da pilha (.pop python)
command *CreateStack();                 //Cria a pilha e a inicializa vazia

#endif