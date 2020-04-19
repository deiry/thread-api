/*Modifique el programa resultado del ejercicio anterior
 para que se creen tantos hilos como ficheros especificados 
 como parámetros de entrada de tal manera que todos los 
 hilos lleven a cabo su función de forma concurrente.*/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

#define MAXLON 1000

pthread_t tid;
void *cuenta(void *);


int main(int argc, char *argv[])
{
    pthread_t hilo[argc-1];
    int param;
    if (argc < 2)
    {
        printf("Indica el nombre de un fichero.\n");
        exit(0);
    }
    for (param= 0; param< argc-1; param++){

        pthread_create (&hilo[param], NULL, cuenta,(void *) argv[param+1]);
    }

    for (param= 0; param< argc-1; param++) {
        pthread_join (hilo[param], NULL);
        printf ("El hilo %d ha finalizado\n", param+1);
    }
    printf ("Ficheros leidos exitosamente\n");

}

void *cuenta(void *nombre)
{
    char *name= (char *)nombre;
    int pos, cont= 0, leidos;
    char cadena[MAXLON];
    int fd;
    fd= open(name,O_RDONLY);
   
    while ((leidos =read(fd,cadena,MAXLON))!= 0) {
        
        for (pos= 0; pos< leidos; pos++) {
        if ((cadena[pos]== 'a') || (cadena[pos]== 'A')) {
            cont++;
        }
        }
    }
    printf("Fichero %s: %d caracteres 'a' o 'A' encontrados\n", nombre, cont);
    close(fd);
    pthread_exit(NULL);
}