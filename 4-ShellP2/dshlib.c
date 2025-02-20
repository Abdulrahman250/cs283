#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "dshlib.h"

/*
* Implement your exec_local_cmd_loop function by building a loop that prompts the
* user for input.  Use the SH_PROMPT constant from dshlib.h and then
* use fgets to accept user input.
*
*      while(1){
*        printf("%s", SH_PROMPT);
*        if (fgets(cmd_buff, ARG_MAX, stdin) == NULL){
*           printf("\n");
*           break;
*        }
*        //remove the trailing \n from cmd_buff
*        cmd_buff[strcspn(cmd_buff,"\n")] = '\0';
*
*        //IMPLEMENT THE REST OF THE REQUIREMENTS
*      }
*
*   Also, use the constants in the dshlib.h in this code. 
*      SH_CMD_MAX              maximum buffer size for user input
*      EXIT_CMD                constant that terminates the dsh program
*      SH_PROMPT               the shell prompt
*      OK                      the command was parsed properly
*      WARN_NO_CMDS            the user command was empty
*      ERR_TOO_MANY_COMMANDS   too many pipes used
*      ERR_MEMORY              dynamic memory management failure
*
*   errors returned
*      OK                     No error
*      ERR_MEMORY             Dynamic memory management failure
*      WARN_NO_CMDS           No commands parsed
*      ERR_TOO_MANY_COMMANDS  too many pipes used
*  
*   console messages
*      CMD_WARN_NO_CMD        print on WARN_NO_CMDS
*      CMD_ERR_PIPE_LIMIT     print on ERR_TOO_MANY_COMMANDS
*      CMD_ERR_EXECUTE        print on execution failure of external command
*
*  Standard Library Functions You Might Want To Consider Using (assignment 1+)
*      malloc(), free(), strlen(), fgets(), strcspn(), printf()
*
*  Standard Library Functions You Might Want To Consider Using (assignment 2+)
*      fork(), execvp(), exit(), chdir()
*/
int exec_local_cmd_loop() 
{
    char cmd_buff[ARG_MAX];
    int rc = 0;
    cmd_buff_t cmd;

    // TODO IMPLEMENT MAIN LOOP

    // TODO IMPLEMENT parsing input to cmd_buff_t *cmd_buff

    // TODO IMPLEMENT if built-in command, execute builtin logic for exit, cd (extra credit: dragon)
    // the cd command should chdir to the provided directory; if no directory is provided, do nothing

    // TODO IMPLEMENT if not built-in command, fork/exec as an external command
    // for example, if the user input is "ls -l", you would fork/exec the command "ls" with the arg "-l"

    while (1) {
        printf("%s", SH_PROMPT);
        if (fgets(cmd_buff, ARG_MAX, stdin) == NULL) {
            printf("\n");
            break;
        }

        cmd_buff[strcspn(cmd_buff, "\n")] = '\0';
        if (strlen(cmd_buff) == 0 || strspn(cmd_buff, " \t") == strlen(cmd_buff)) {
            printf(CMD_WARN_NO_CMD);
            continue;
        }

        int rc = build_cmd_buff(cmd_buff, &cmd);  
        if (rc == OK) {
            if (exec_built_in_cmd(&cmd) == BI_EXECUTED) {
                continue;
            }
            exec_cmd(&cmd);
        } else if (rc == WARN_NO_CMDS) {
            printf("%s", CMD_WARN_NO_CMD);
        }
    }
    return 0;
}

Built_In_Cmds match_command(const char *input) 
{
    if (strcmp(input, "exit") == 0) {
        return BI_CMD_EXIT;
    } else if (strcmp(input, "cd") == 0) {
        return BI_CMD_CD;
    }
    return BI_NOT_BI;
}

Built_In_Cmds exec_built_in_cmd(cmd_buff_t *cmd) {
    if (strcmp(cmd->argv[0], "exit") == 0) {
        exit(0);
    } else if (strcmp(cmd->argv[0], "cd") == 0) {
        if (cmd->argc > 1) {
            if (chdir(cmd->argv[1]) != 0) {
                perror("cd");
            }
        }
        return BI_EXECUTED;
    }
    return BI_NOT_BI;
}


void trim_whitespace(char *str) 
{
    char *end;

    while (isspace((unsigned char)*str)) {
        str++;
    }

    if (*str == '\0') {
        return;
    }

    end = str + strlen(str) - 1;

    while (end > str && isspace((unsigned char)*end)) {
        end--;
    }

    *(end + 1) = '\0';
}

int build_cmd_buff(char *cmd_line, cmd_buff_t *cmd_buff) 
{
    trim_whitespace(cmd_line); 
    cmd_buff->argc = 0;
    cmd_buff->_cmd_buffer = cmd_line;
    
    char *current = cmd_line;
    int len = strlen(cmd_line);
    int in_quotes = 0;
    char *start = current;
    
    for (int i = 0; i <= len; i++) {
        if (current[i] == '\0' || (!in_quotes && current[i] == ' ')) {
            if (start != current + i) {
                int token_len = current + i - start;
                if (token_len > 0) {
                    if (*start == '"' && *(start + token_len - 1) == '"') {
                        start++;
                        token_len -= 2;
                    }
                    char *token = start;
                    *(start + token_len) = '\0';
                    
                    if (cmd_buff->argc < CMD_ARGV_MAX - 1) {
                        cmd_buff->argv[cmd_buff->argc++] = token;
                    }
                }
            }
            start = current + i + 1;
        } else if (current[i] == '"') {
            in_quotes = !in_quotes;
        }
    }
    
    cmd_buff->argv[cmd_buff->argc] = NULL;  
    return OK;
}

int exec_cmd(cmd_buff_t *cmd) 
{
    pid_t pid = fork();
    if (pid == 0) {  
        execvp(cmd->argv[0], cmd->argv);
        perror("execvp");  
        exit(EXIT_FAILURE);
    } else if (pid > 0) {  
        int status;
        waitpid(pid, &status, 0);
        return status;
    } else {
        perror("fork");
        return ERR_EXEC_CMD;
    }
}