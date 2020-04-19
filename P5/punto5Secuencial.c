/*Se requiere un programa que reciba un vector de números a 
través de un archivo de texto.*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAXLON 1000

void suma (char *);

int main (int argc, char *argv[]) { 
  if (argc!= 2) {
    printf ("Indica el nombre de un fichero.\n");
    exit(0);
  }
  suma(argv[1]);
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
