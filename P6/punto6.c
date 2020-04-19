/*El profesor de un curso desea un programa en lenguaje C que calcule 
la desviación estándar (símbolo σ o s) de las notas obtenidas por sus 
estudiantes en el curso */

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include<math.h>

#define MAXLON 4

void calculate_standard_deviation(float [], int);

int main(int argc, char *argv[]){
    if (argc!= 2) {
        printf ("Indica el nombre de un fichero.\n");
        exit(0);
    }
    float notas[3] = {4.5,4.5,3.0};
    calculate_standard_deviation(&notas, sizeof(notas)/sizeof(notas[0]));
    return 0;


}

void read_file(char *nombre){
    char *name = (char *)nombre;
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

}

void calculate_standard_deviation(float notas[], int n){
  
    int pos;
    float sum=0.0,mean=0.0;

    printf("size %d", n);
    for (pos= 0; pos< n; pos++) {
         sum = sum+notas[pos];
    }

    mean = sum/n;
    printf("mean %f", mean);
   
    float sumatoria = 0.0;
    for(pos=0; pos<n; pos++){
        double aux = pow((notas[pos]-mean),2);
        sumatoria = sumatoria + aux;
    }
    printf("sumatoria %f", sumatoria);
    float std = sqrt(sumatoria/(n));
    printf("std %f", std);


}