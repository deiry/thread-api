/*Se requiere un programa que reciba un vector de números a 
través de un archivo de texto.*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

#define MAXLON 1000

void suma (char *);

int main (int argc, char *argv[]) { 
  clock_t tiempo_inicio, tiempo_final;
  double segundos;
  tiempo_inicio = clock();

  if (argc!= 2) {
    printf ("Indica el nombre de un fichero.\n");
    exit(0);
  }
  suma(argv[1]);
  
  tiempo_final = clock();
  segundos = (double)(tiempo_final - tiempo_inicio ) / CLOCKS_PER_SEC; /*según que estes midiendo el tiempo en segundos es demasiado grande*/

  printf("%f",segundos);
  return 0;
}

void suma (char *nombre) {
  int pos, sum = 0, leidos;
  char cadena[MAXLON];
  int entero;
  int fd;
  fd= open(nombre,O_RDONLY);
  while ((leidos =read(fd,cadena,MAXLON))!= 0) {
    for (pos= 0; pos< leidos; pos++) {
      if ((cadena[pos] != ',') && (cadena[pos] != ' ') && (cadena[pos] != '\n')) {
        entero = cadena[pos] - '0';
        sum = sum + entero;
      }
    }
  }
  printf("La suma de los números del fichero %s es: %d \n", nombre, sum);
  close(fd);
}
