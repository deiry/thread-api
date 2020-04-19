#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>

#define MAXLON 1000
int mitadVector = 0;
void handleVector (char *);

int main (int argc, char *argv[]) { 
  if (argc!= 2) {
    printf ("Indica el nombre de un fichero.\n");
    exit(0);
  }
  handleVector(argv[1]);
  return 0;
}

void handleVector (char *nombre) {
  int pos, sum = 0, leidos, cont = 0;
  char cadena[MAXLON];
  int fd;
  fd= open(nombre,O_RDONLY);
  while ((leidos =read(fd,cadena,MAXLON))!= 0) {
    for (pos= 0; pos< leidos; pos++) {
      if ((cadena[pos] != ',') && (cadena[pos] != ' ') && (cadena[pos] != '\n')) {
        cont++;
      }
    }
  }

  mitadVector = floor(cont/2);
 

  printf("La suma de los números del fichero %s es: %d y %d \n", nombre, sum, mitadVector);
  close(fd);
}

