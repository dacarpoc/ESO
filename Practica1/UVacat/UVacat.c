//Daniel Carracedo Pocero T1-X2

#include <stdlib.h>
#include <stdio.h>
#define TAMCAD 100000

int main(int argc, char const *argv[]){
    
    FILE *fentrada=NULL;
    char *buff;
    int numar=argc;

    if ((buff =(char *) malloc(TAMCAD*sizeof(char))) == NULL){

        fclose(fentrada);
        exit(1);
    }

    for(int i=1;i<numar;i++){

        fentrada=fopen(argv[i], "r");
        if (fentrada == NULL){

            printf("UVacat: no puedo abrir fichero\n");
            exit(1);
        }

        while (fgets(buff, sizeof(buff), fentrada) != NULL){

            printf("%s",buff);
        }

        fclose(fentrada);
    } 

    free(buff);
    return 0;
}