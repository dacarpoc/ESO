//Daniel Carracedo Pocero T1-X2

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]){

    FILE *fentrada;
    int contador, tmp;
    char caracter;
   
    if(argc < 2){

	    printf("UVazip: file1 [file2 ...]\n");
	    exit(1);
    }

    for(int i=1;i<argc;i++){

        contador=1;
        fentrada=fopen(argv[i], "r");
        if (fentrada == NULL){

            printf("UVazip: no puedo abrir fichero\n");
            exit(1);
        }

	    caracter=fgetc(fentrada);
        while ((tmp=fgetc(fentrada)) != EOF){ 
                            
            if(caracter==tmp){

                contador++;
            }

            else{
                
                fwrite(&contador, sizeof(int), 1, stdout);
                fwrite(&caracter, sizeof(char), 1, stdout);
                caracter=tmp;
                contador=1;
            }
        }

        fwrite(&contador, sizeof(int), 1, stdout);
        fwrite(&caracter, sizeof(char), 1, stdout);
        
        fclose(fentrada);
    }
	
    exit(0);
}