/*Modifique el programa  de manera que reciba dos números enteros 
como parámetros de entrada y calcule sus factoriales de manera concurrente 
utilizando dos hilos que se ejecutan en paralelo con el hilo principal. 
El hilo principal deberá esperar a que terminen los otros dos hilos. 
Recuerda  añadir el parámetro ```-lpthread``` al comienzo del ```gcc``` 
para compilar la aplicación multihilo.*/

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
  pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
  srand(time(0));
  pthread_t hilo1, hilo2;
  if (argc!= 3) {
    printf ("Ingresa dos números enteros.\n");
    exit(0);
  }
  pthread_create (&hilo1, NULL, factorial, (void *) argv[1]);
  pthread_create (&hilo2, NULL, factorial, (void *) argv[2]);
  pthread_join (hilo1, NULL);
  pthread_join (hilo2, NULL);
  return 0;
}

