#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER 100

int main(void) {

    int status, id, j;
    
    int fd1[2];
    if(pipe(fd1)<0) { perror("pipe"); return -1; }
    int fd2[2];
    if(pipe(fd2)<0) { perror("pipe"); return -1; }
    int fd3[2];
    if(pipe(fd3)<0) { perror("pipe"); return -1; }

    /* Insira um comando para pegar o PID do processo corrente e mostre na tela da console. */
    id = getpid();
    printf("[PAI] Meu PID é %d. Criando processo filho...\n", id);

    id = fork();
    
    if (id > 0 /* insira um comando para criar um subprocesso */) {
        /* Faça com que o processo pai execute este trecho de código */
        /* Mostre na console o PID do processo pai e do processo filho */
        printf("[PAI] Meu PID é %d e meu filho foi criado com PID %d\n", getpid(), id);

        /* Monte uma mensagem e a envie para o processo filho */
        close(fd1[0]);
        char message[BUFFER] = "Olá filho. Aqui é o processo pai.";
        write(fd1[1], message, sizeof(message)); 
        close(fd1[1]);

        /* Mostre na tela o texto da mensagem enviada */
        printf("[PAI] Mensagem enviada para o processo filho: %s\n", message);
        
        /* Aguarde a resposta do processo filho */
        char reply1[BUFFER];
        close(fd2[1]);
        read(fd2[0], reply1, sizeof(reply1));
    
        /* Mostre na tela o texto recebido do processo filho */
        printf("[PAI] Mensagem recebida do processo filho: %s\n", reply1);

        /* Aguarde mensagem do filho e mostre o texto recebido */
        char reply2[BUFFER];
        close(fd3[1]);
        read(fd3[0], reply2, sizeof(reply2));
        printf("[PAI] Mensagem recebida do processo filho: %s\n", reply2);        

        /* Aguarde o término do processo filho */
        wait(&status);        

        /* Informe na tela que o filho terminou e que o processo pai também vai encerrar */
        printf("[PAI] O processo filho terminou e eu estou encerrando...\n");

    } else {
        /* Faça com que o processo filho execute este trecho de código */
        /* Mostre na tela o PID do processo corrente e do processo pai */
        printf("[FILHO] Meu PID é %d e meu pai tem PID %d\n", getpid(), getppid());
     
        /* Aguarde a mensagem do processo pai e ao receber mostre o texto na tela */
        char message[BUFFER];
        close(fd1[1]);
        read(fd1[0], message, sizeof(message));        
        printf("[FILHO] Mensagem recebida do processo pai: %s\n", message);
    
        /* Envie uma mensagem resposta ao pai */
        close(fd2[0]);
        char reply1[BUFFER] = "Olá pai. Aqui é o processo filho.";
        write(fd2[1], reply1, sizeof(reply1));
        close(fd2[1]);

        printf("[FILHO] Mensagem enviada para o processo pai: %s\n", reply1);

        /* Execute o comando “for” abaixo */
        for (j = 0; j <= 10000; j++);
        /* Envie mensagem ao processo pai com o valor final de “j” */
        char reply2[BUFFER];
        close(fd3[0]);
        sprintf(reply2, "Olá pai, sou eu de novo. O valor de j é %d.", j);
        write(fd3[1], reply2, sizeof(reply2));
        close(fd3[1]);

        printf("[FILHO] Mensagem enviada para o processo pai: %s\n", reply2);
        
        /* Execute o comando abaixo e responda às perguntas */
        execl("/bin/ls", "ls", NULL);
        /* O que acontece após este comando? */
        /* O que pode acontecer se o comando “execl” falhar? */
    }
    exit(0);
}
