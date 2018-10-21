#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

typedef struct file_count file_count;
struct file_count{
    char *file;
    int contagem;
};

int conta_linhas(char *file);

void* thr_contalinhas(void* param);

int main(int argc, char *argv[])
{
    if(argc < 2){
        printf("Devem ser passados parametros\n");
        return EXIT_FAILURE;
    }

    file_count* contagens;

    contagens = calloc(argc-1,sizeof(file_count));
    //file_count contagens[] = file_count[1];//calloc(argc-1,sizeof(file_count));


    printf("Totais de linhas em cada arquivo:\n");

    pthread_t tid[argc-1];
    int i;
    for (i=1;i<argc;i++){

        contagens[i].file = argv[i];

        int te = pthread_create(&tid[i],
                       NULL, // Default é ser JOINABLE portando pode-se passar NULL;
                       &thr_contalinhas,
                       (void *)&contagens[i]
                       );
        if (te){

            perror("Falha na criação da thread");
            exit(EXIT_FAILURE);
        }


        //int numLinhas = conta_linhas(argv[i]);
        //printf("Totais de linhas em cada arquivo:\n%s : %d\n",argv[i],numLinhas);
    }
    pthread_exit(NULL);
    //return 0;
}

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
            close(fd);
            return EXIT_FAILURE;
        }
        int i;
        for (i=0;i<read_result;i++){
            if ( buf1[i] == '\n') {
                contador++;
            }
        }
    }while(read_result  != 0);

    close(fd);

    return contador;
}


void* thr_contalinhas(void* param)
{
    char *filename = ((struct file_count*)param)->file;
    printf("%s : %d\n",filename,conta_linhas(filename));
}

