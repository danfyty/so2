#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include "utils.h"
#define BUFSIZE 1024
#define MAXARG 10
#define DELIMITERS " \n\t"


/*
0->stdin
1->stout
2->stderr
 */
int main(int argc, char **argv) {

    int i, fd, pid, rs, status;
    char buffer[BUFSIZE], *args[MAXARG], *token;


    while(1) {
        printf("prompt: ");

        fgets(buffer, BUFSIZE-1, stdin);

        token=strtok(buffer, DELIMITERS);
        args[0]=token;
        for(i=1;(i<MAXARG) && (token=strtok(NULL, DELIMITERS));++i) {
            args[i]=token;
        }
        args[i]=NULL;


        pid=fork();
        FATAL(pid<0);
        //printf("a%d\n", pid);

        if(pid>0) {
            wait(&status);
        }
        else {
            /*
               redireciona saida do filho
            close(1);
            fd=open("out.txt", O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
            */
            rs=execvp(args[0], args);
            FATAL(rs<0);
        }
    }

    //write(fd, "HELLLO\n", 7);

    //printf("File descriptro %d\n", fd);

    close(fd);


    return EXIT_SUCCESS;
}
