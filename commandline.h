#ifndef COMMANDLINE_C
#define COMMANDLINE_C


typedef struct Commandline
{
    command *current;

    char nextOperator;

    struct Commandline *prev;
    struct Commandline *next;
} commandline;


//commandline
commandline *CreateLine();
commandline *GetLastCommand(commandline *cmd);
void GetCommand(commandline *root);     //Recebe o comando a ser utilizado
commandline *CreateCommandLine(commandline *cmd, char key);


#endif