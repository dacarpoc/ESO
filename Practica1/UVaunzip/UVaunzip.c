//Daniel Carracedo Pocero T1-X2

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

    FILE *fentrada;
    int contador;
    char caracter;

    if (argc < 2) {

        printf("UVaunzip: file1 [file2 ...]\n");
	    exit(1);
    }

    for(int i=1;i<argc;i++){

        fentrada = fopen(argv[i], "r");
        if (fentrada == NULL) {

            printf("UVazip: no puedo abrir fichero\n");
            exit(1);
        }

        while (fread(&contador, sizeof(int), 1, fentrada) == 1) {

            caracter = fgetc(fentrada);
            for (int i = 0; i < contador; i++) {
                
                fwrite(&caracter, sizeof(char), 1, stdout);
            }
        }

        fclose(fentrada);
    }
    
    exit(0);
}
