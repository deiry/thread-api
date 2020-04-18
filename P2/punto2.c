/*Modifique el programa resultante del numeral anterior de manera que
 no el número de factoriales a calcular no este limitado a 2. 
 Para este caso, el programa puede crear tantos hilos como sean 
 necesarios para el cálculo del factorial dependiendo del número de
  argumentos pasados. El hilo principal deberá esperar a que terminen 
  el resto de los hilos y a medida que vayan terminando muestran un 
  mensaje que indique el identificador del hilo finalizado.*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>


void *factorial (void *dato) {
    long long int resultado= 1;
    int num, n= atoi((char *) dato);
    for (num= 2; num<= n; num++) {
        resultado= resultado* num;
        printf ("Factorial de %d, resultado parcial %lld\n", n, resultado);
        sleep (random() %3);
    }
    printf ("El factorial de %d es %lld\n", n, resultado);
    pthread_exit (NULL);    
}

int main (int argc, char *argv[]) {
    pthread_t hilo[argc-1];
    int param;
    if (argc< 2) {
        printf ("Ingrese los números que quiera para tener el factorial.\n");
        exit (0);
    }
    for (param= 0; param< argc-1; param++){
        pthread_create (&hilo[param], NULL, factorial,(void *) argv[param+1]);
    }
       
    for (param= 0; param< argc-1; param++) {
        pthread_join (hilo[param], NULL);
        printf ("El hilo %d ha finalizado\n", param+1);
    }
    printf ("Factoriales calculados correctamente\n");
    return 0;
}