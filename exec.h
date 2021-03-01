#include "commandline.h"

#ifndef EXEC_H
#define EXEC_H

#define STDOUT_MAX_BUFF 500
#define FD_READ 0
#define FD_WRITE 1

void ExecCommandLine(commandline *cmd);
void ExecCommand(command *cmd);
commandline *ExecArchiveCommand(commandline *cmd);
void CheckExit(command *current);

#endif