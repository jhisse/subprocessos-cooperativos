#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define LINESIZE 100
#define MAXARGS  20

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int main(void) {
    int status;
    char line[LINESIZE];
    
    while(1) {
	printf(ANSI_COLOR_GREEN "$ " ANSI_COLOR_RESET);
        fflush(stdin);
        
        if(fgets(line, sizeof(line), stdin) == NULL) break;
        
        line[strcspn(line, "\r\n")] = 0;

        if(strncmp(line, "exit", 4) == 0) break;
        if(strlen(line) == 0) continue;
        
        char **command = malloc(MAXARGS * sizeof(char *));
        char *parsed;
        int index = 0;

        for(parsed=strtok(line, " "); parsed!=NULL; parsed=strtok(NULL, " "))
            command[index++] = parsed;
        command[index] = NULL;
        
        if(fork() == 0) {
            exit(execvp(command[0], command));
        } else {
            wait(&status);

            if(WEXITSTATUS(status) == 0) printf(ANSI_COLOR_BLUE "Executado com sucesso.\n" ANSI_COLOR_RESET);
            else printf(ANSI_COLOR_BLUE "Código de retorno = %d\n" ANSI_COLOR_RESET, WEXITSTATUS(status));
        }
    }
    exit(0);
}
