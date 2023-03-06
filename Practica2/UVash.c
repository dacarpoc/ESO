#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_LENGTH 1024
#define MAX_COMMANDS 50

void Hijo(char *almacen);
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

        char *commands[MAX_COMMANDS];
        int num_commands = 0;
        char *token = strtok(almacen, "&");        
        while (token != NULL) {

            commands[num_commands++] = token;
            token = strtok(NULL, "&");
        }

        pid_t pids[num_commands];
        for (int i = 0; i < num_commands; i++) {

            pid_t pid = fork();
            if (pid == 0) {

                Hijo(commands[i]);
                exit(0);
            } 
            if (pid > 0) {

                pids[i] = pid;
            } else {

                fprintf(stderr, "%s", error_message);
                exit(1);
            }
        }
        for (int i = 0; i < num_commands; i++) {

            waitpid(pids[i], NULL, 0);
        }
    }

    exit(0);
}
void Hijo(char *almacen){
            
    char *args[MAX_LENGTH];
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

    if (strcmp(args[0], "cd") == 0) {

        if (i != 2) {

            fprintf(stderr,"%s", error_message);
            exit(0);
        }
        if (chdir(args[1]) != 0) {

            fprintf(stderr,"%s", error_message);
            exit(0);
        }
    }
    else{

        if(execvp(args[0], args) == -1){
            fprintf(stderr,"%s", error_message);
            exit(0);
        }

        fprintf(stderr, "%s", error_message);
        exit(1);
    }                
    
}

