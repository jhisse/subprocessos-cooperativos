#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <error.h>

#define LINESIZE 100 


int main(void) {
    int status;
    char line[LINESIZE];
    
    while(printf("$ ") && fgets(line, sizeof(line), stdin) != NULL) {
        
        line[strcspn(line, "\r\n")] = 0;

        if(strncmp(line, "exit", 4) == 0) break;
        if(strlen(line) == 0) continue;       
        
        char buffer[LINESIZE+5];
        
        strcpy(buffer, "/bin/");
        strcat(buffer, line);

        if(fork() == 0) {
            exit(execl(buffer, line, NULL));
        } else {
            wait(&status);

            if(WEXITSTATUS(status) == 0) printf("Executado com sucesso.\n");
            else printf("Código de retorno = %d\n", WEXITSTATUS(status));
        }
    }
    exit(0);
}
