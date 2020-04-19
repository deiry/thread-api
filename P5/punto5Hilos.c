#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>
#include <pthread.h>

#define MAXLON 1000
int mitadVector = 0, cont = 0;
char cadena[MAXLON];
int  vector[MAXLON];
// pthread_t hilo1, hilo2;
int fd, sumH1, sumH2, sum;
int handleVector (char *);
// void * sumHalfVectorH1( void * mitad);
// void * sumHalfVectorH2( void * mitad);

int main (int argc, char *argv[]) { 
  
  if (argc!= 2) {
    printf ("Indica el nombre de un fichero.\n");
    exit(0);
  }
  handleVector(argv[1]);
  // printf("entraaa y tiene mitad %d \n", mitadVector);
 
  // sum = sum + sumH2;
  // printf("suma: %d \n", sum);
  return 0;
}

int handleVector (char *nombre) {
  printf("entra");
  int pos, leidos;
  fd= open(nombre,O_RDONLY);
  while ((leidos =read(fd,cadena,MAXLON))!= 0) {
    for (pos= 0; pos< leidos; pos++) {
      if ((cadena[pos] != ',') && (cadena[pos] != ' ') && (cadena[pos] != '\n')) {
        cont++;
        vector[pos]= cadena[pos] - '0';
        printf("vecot %d \n",vector[pos]);
      }
    }
  
  }

  mitadVector = floor(cont/2);
 
  // printf("La suma de los números del fichero %s es:   \n", nombre);
  close(fd);
  return 0;
}

// void * sumHalfVectorH1( void * mitad){
//   long long int m = (long long int) mitad;
//     printf("entraaa %lld \n", m);
//   int pos;
//   for(pos = 0; pos < m -1; pos++){
//     sumH1 = sumH1 + vector[pos];
//   }
//   printf("finaliza h1");
//   pthread_exit(NULL);
// }

// void * sumHalfVectorH2( void * mitad){
//    long long int m = (long long int) mitad;
//   int pos;
//   for(pos = m -1; pos < cont-1; pos++){
//     sumH2 = sumH2 + vector[pos];
//   }
//   printf("finaliza h1");
//   pthread_exit(NULL);
// }