#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

/*
 * Fluxo de execução:
 *
 *       fork()
 * main --+-- pid>0 -- printf()
 *        |
 *        +-- pid=0 -- execl() -> error
 *                  -- printf()
 *
 * printf após execl será executado, pois
 * execl não encontra o executável e retorna
 * um erro, não substituindo o processo em
 * execução
 *
 */

int main(void) {
    int ret;
    ret = fork();
    if (ret == 0) {
        /* execl("/bin/ll","ll",0) */
        if (execl("/bin/ll","ll",0) == -1) printf("%s\n", strerror(errno));
        printf("Por que este comando foi executado? \n");
    }
    else printf("Processo continua executando.\n");
    return 0;
}
