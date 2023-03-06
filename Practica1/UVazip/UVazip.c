//Daniel Carracedo Pocero T1-X2

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]){

    FILE *fentrada;
    int contador=0;
    char caracter, tmp;
    if(argc<2){

	    printf("UVazip: file1 [file2 ...]\n");
	    exit(1);
    }

    for(int i=1;i<argc-1;i++){

        fentrada=fopen(argv[i], "r");
        if (fentrada == NULL){

            printf("UVazip: no puedo abrir fichero\n");
            exit(1);
        }

	    caracter=fgetc(fentrada);
        while (fgetc(fentrada) != EOF){ 
                 
            tmp=fgetc(fentrada);
            if(caracter==tmp){

                contador++;
            }

            else{
                
                fwrite(&contador, 1, sizeof(int), stdout);
                fwrite(&caracter, sizeof(char), 1, stdout);
                caracter=tmp;
            }
        }

        fclose(fentrada);
    }
	
    exit(0);
}