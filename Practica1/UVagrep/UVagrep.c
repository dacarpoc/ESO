//Daniel Carracedo Pocero T1-X2

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[]){
    
    FILE *fentrada;
    char *almacen;
    size_t tam;

    almacen=NULL;
    tam=0;

    if(argc<2){

        printf("UVagrep: searchterm [file ...]\n");
        exit(1);
    }

    if(argc==2){

	    while(!feof(stdin)){

            getline(&almacen,&tam,stdin);
            if(strstr(almacen, argv[1])){

                printf("%s", almacen);
            }

            free(almacen);
            almacen=NULL;
            tam=0;
        }
    }

    else{

        for(int i=2;i<argc;i++){

            fentrada=fopen(argv[i], "r");
            if (fentrada == NULL){

                printf("UVagrep: cannot open file\n");
                exit(1);
            }

            while(!feof(fentrada)){

                getline(&almacen,&tam,fentrada);      
                if(strstr(almacen, argv[1])){

                    printf("%s", almacen);
                }

                free(almacen);
                almacen=NULL;
                tam=0;
            }
            
            fclose(fentrada);
        } 
    }

    exit(0);
}