#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int contador = 0;

    int fd = STDIN_FILENO;
    char buf1[200];
    int read_result;
    do {
        read_result = read(fd, buf1, 200);
        if (read_result == -1) {
            perror("Erro ao ler arquivo!");
            return EXIT_FAILURE;
        }
        int i;
        for (i=0;i<read_result;i++){
            if ( buf1[i] == '\n') {
                contador++;
            }
        }
    }while(read_result  != 0);

    printf("Total de linhas: %d\n",contador);
    return 0;
}
