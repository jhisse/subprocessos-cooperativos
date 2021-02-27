#include <stdio.h>
#include <unistd.h>

/*
 * Fluxo de execução:
 *
 *       fork()      fork()
 * main --+-- pid>0 --+-- pid>0 -- printf()
 *        |           |
 *        |           +-- pid=0 -- printf()
 *        |
 *        |          fork()
 *        +-- pid=0 --+-- pid>0 -- printf()
 *                    |
 *                    +-- pid=0 -- printf()
 *
 */

int main(void) {
    int ret1, ret2;
    ret1 = fork();
    ret2 = fork();
    printf("Programa em execução.\n");
    return 0;
}
