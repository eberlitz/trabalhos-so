#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int conta_linhas(char *file)
{
    int contador = 0;

    int fd = open(file,O_RDONLY);
    if  (fd==-1) {
            perror("Erro ao abrir arquivo!");
            return EXIT_FAILURE;
    }

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

    return contador;
}

int main(int argc, char *argv[])
{
    if(argc == 1){
        printf("Devem ser passados parametros\n");
        return EXIT_FAILURE;
    }

    int i;
    for (i=1;i<argc;i++){
        int numLinhas = conta_linhas(argv[i]);
        printf("Totais de linhas em cada arquivo:\n%s : %d\n",argv[i],numLinhas);
    }
    return 0;
}
