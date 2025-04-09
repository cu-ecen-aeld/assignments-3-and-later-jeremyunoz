#include "systemcalls.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * @param cmd the command to execute with system()
 * @return true if the command in @param cmd was executed
 *   successfully using the system() call, false if an error occurred,
 *   either in invocation of the system() call, or if a non-zero return
 *   value was returned by the command issued in @param cmd.
*/
bool do_system(const char *cmd)
{

/*
 *  Call the system() function with the command set in the cmd
 *   and return a boolean true if the system() call completed with success
 *   or false() if it returned a failure
*/
    if (cmd == NULL) {
        fprintf(stderr, "Command is NULL\n");
        return false;
    }

    int status = system(cmd);
    if (status == -1) {
        perror("System call failed!"); 
        return false;
    }
    return true;
}

/**
* @param count -The numbers of variables passed to the function. The variables are command to execute.
*   followed by arguments to pass to the command
*   Since exec() does not perform path expansion, the command to execute needs
*   to be an absolute path.
* @param ... - A list of 1 or more arguments after the @param count argument.
*   The first is always the full path to the command to execute with execv()
*   The remaining arguments are a list of arguments to pass to the command in execv()
* @return true if the command @param ... with arguments @param arguments were executed successfully
*   using the execv() call, false if an error occurred, either in invocation of the
*   fork, waitpid, or execv() command, or if a non-zero return value was returned
*   by the command issued in @param arguments with the specified arguments.
*/

bool do_exec(int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;

    pid_t pid = fork();
    if (pid == -1){
        perror("child process is not created"); 
        va_end(args);
        return false;
    }
    
    if (pid == 0) {
        // child
        if (execv(command[0], command) == -1) {
            perror("execv function failed"); 
            exit(-1);
        }
    }
    
    int status; 
    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid failed");
        va_end(args);
        return false;
    }

    va_end(args);

    return (WIFEXITED(status) && WEXITSTATUS(status) == 0);
}

/**
* @param outputfile - The full path to the file to write with command output.
*   This file will be closed at completion of the function call.
* All other parameters, see do_exec above
*/
bool do_exec_redirect(const char *outputfile, int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;
    
    int fd = open(outputfile, O_WRONLY|O_TRUNC|O_CREAT, 0644); 
    if (fd == -1) {
        perror("The file is not created");
        close(fd);
        va_end(args);
        return false;
    }

    pid_t childpid = fork();
    if (childpid == -1){
        perror("child process is not created"); 
        close(fd);
        va_end(args);
        return false;
    }
    
    if (childpid == 0) {
        // Child process
        if (dup2(fd, STDOUT_FILENO) == -1) {
            perror("dup2 failed");
            close(fd);
            exit(1);
        }
        close(fd);  // fd duplicated, safe to close original

        if (execv(command[0], command) == -1) {
            perror("execv function failed"); 
            exit(1);
        }
    }

    int status;
    if (waitpid(childpid, &status, 0) == -1) {
        perror("waitpid failed");
        close(fd);
        va_end(args);
        return false;
    }

    close(fd);
    va_end(args);

    return (WIFEXITED(status) && WEXITSTATUS(status) == 0);
}
