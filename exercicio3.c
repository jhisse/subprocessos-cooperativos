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
 * printf após execl não será executado, pois
 * execl substitui o processo, assim como todo
 * seu espaço de memória
 *
 */

int main(void) {
    int ret;
    ret = fork();
    if (ret == 0) {
        execl("/bin/ls","ls",0);
        printf("Quando este comando será executado? \n");
    };
    printf("Por que a função printf anterior não foi executada?\n");
    return 0;
}
