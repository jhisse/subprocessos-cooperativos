#include <stdio.h>
#include <unistd.h>

/*
 * Fluxo de execução:
 *
 *       fork()
 * main --+-- pid>0 -- printf()
 *        |
 *        +-- pid=0 -- execl()
 *
 */

int main(void) {
    int ret;
    ret = fork();
    if (ret == 0) execl("/bin/ls","ls",0);
    else printf("Processo continua executando.\n");
    return 0;
}
