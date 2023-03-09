#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LONGITUD 1024
#define MAX_COMANDOS 50

void cd (char **args, int i);
void hijo(char *almacen);
char error_message[30] = "An error has occurred\n"; 

int main(int argc, char *argv[]) {
    
    char *almacen=NULL;
    size_t tam_line = 0;
    ssize_t tam;
    FILE *fd = stdin;
    int batch_mode = 0;
    
    if(argc > 2){

        fprintf(stderr, "%s", error_message);
        exit(1); 
    }

    if (argc > 1) {
        
        if((fd = fopen(argv[1], "r"))==NULL){

            fprintf(stderr, "%s", error_message);
            exit(1);
        }

        batch_mode = 1;
    }

    while (1) {

        if (!batch_mode) {

            fprintf(stdout,"UVash> ");
        }
       
        tam = getline(&almacen, &tam_line, fd); 

        if (tam == -1) {

            exit(0);
        }
       
        if (tam > 0) {

            almacen[tam - 1] = '\0';
        }

	    if (strcmp(almacen, "exit") == 0) {

            exit(0);
        }

        if (strncmp(almacen, "cd ", 3) == 0) {

            char *argscd[MAX_LONGITUD];
            int num_args = 0;
            char *token2 = strtok(almacen, " ");  

            while (token2 != NULL) {

                argscd[num_args++] = token2;
                token2 = strtok(NULL, " ");
            } 
            cd(argscd, num_args);
        }

        else{

            char *comandos[MAX_COMANDOS];
            int num_comandos = 0;
            char *token = strtok(almacen, "&");  

            while (token != NULL) {

                comandos[num_comandos++] = token;
                token = strtok(NULL, "&");
            }

            pid_t pids[num_comandos];

            for (int i = 0; i < num_comandos; i++) {

                pid_t pid = fork();

                if (pid == 0) {

                    hijo(comandos[i]);
                    exit(0);
                } 

                if (pid > 0) {

                    pids[i] = pid;
                } 
                
                else {

                    fprintf(stderr, "%s", error_message);
                    exit(1);
                }
            }

            for (int i = 0; i < num_comandos; i++) {

                waitpid(pids[i], NULL, 0);
            }
        }
    }

    exit(0);
}
void cd (char **args, int i){

	if (i != 2) {

        fprintf(stderr,"%s", error_message);
        exit(0);
    }

    if (chdir(args[1]) != 0) {
        
        fprintf(stderr,"%s", error_message);
        exit(0);
    }	
}
void hijo(char *almacen){
            
    char *args[MAX_LONGITUD];
    char *token = strtok(almacen, " ");
    int i = 0;
    int fich_salida = 0; 
    FILE *fout=stdout;

    while (token != NULL && !fich_salida) {

        if (strcmp(token, ">") == 0) {
        
            fich_salida = 1;
            token = strtok(NULL, " ");

            if((fout = fopen(token, "w"))==NULL){

                fprintf(stderr,"%s", error_message);
                exit(0);
            }
        }

        else{

            args[i] = token;
            i++;
            token = strtok(NULL, " ");
        }                
    }
    
    args[i] = NULL;  

    if (fich_salida) {
                    
        dup2(fileno(fout), 1);
        dup2(fileno(fout), 2);

        fclose(fout);
    }

    if(execvp(args[0], args) == -1){

        fprintf(stderr,"%s", error_message);
        exit(0);
    }

    fprintf(stderr, "%s", error_message);
    exit(1);    
}