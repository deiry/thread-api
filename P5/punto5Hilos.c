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
pthread_t hilo1, hilo2;
int fd, sumH1, sumH2, sum;
int handleVector (char *);
void * sumHalfVectorH1( void * mitad);
void * sumHalfVectorH2( void * mitad);

/*Código extraido de https://www.tutorialspoint.com/data_structures_algorithms/linked_list_program_in_c.htm*/
struct node *head = NULL;
struct node *current = NULL;

/*Código extraido de https://www.tutorialspoint.com/data_structures_algorithms/linked_list_program_in_c.htm*/
struct node {
   int data;
   int key;
   struct node *next;
};

/*Código extraido de https://www.tutorialspoint.com/data_structures_algorithms/linked_list_program_in_c.htm*/
void insertFirst(int key, float data) {

   struct node *link = (struct node*) malloc(sizeof(struct node));
	
   link->key = key;
   link->data = data;

   link->next = head;
	

   head = link;
}
/*Código extraido de https://www.tutorialspoint.com/data_structures_algorithms/linked_list_program_in_c.htm*/
int length_list() {
   int length = 0;
   struct node *current;
	
   for(current = head; current != NULL; current = current->next) {
      length++;
   }
	
   return length;
}

int main (int argc, char *argv[]) { 
  
  if (argc!= 2) {
    printf ("Indica el nombre de un fichero.\n");
    exit(0);
  }
  handleVector(argv[1]);
  printf("entraaa y tiene mitad %d \n", mitadVector);
  pthread_create (&hilo1, NULL, sumHalfVectorH1, mitadVector);
  pthread_create (&hilo2, NULL, sumHalfVectorH2, mitadVector);
  pthread_join (hilo1, NULL);
  pthread_join (hilo2, NULL);
  sum = sumH1 + sumH2;
  printf("suma: %d \n", sum);
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
        insertFirst(pos,cadena[pos]-'0');
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

void * sumHalfVectorH1( void * mitad){
  int m =  (int) mitad;
    printf("entraaa %lld \n", m);
  int pos;
  struct node *copy_head = head;

  for(pos = 0; pos < m; pos++){
    sumH1 = sumH1+copy_head->data;
    copy_head = copy_head->next;
    printf("iter h1\n");
  }

  head = copy_head;
  printf("Suma h1 %d finaliza h1\n", sumH1);
  pthread_exit(NULL);
}

void * sumHalfVectorH2( void * mitad){
   int m =  (int) mitad;
    printf("H2 Cont %lld %d \n", cont, m);
  struct node *copy_head = head;
int pos;
  for(pos = m; pos < cont; pos++){
    sumH2 = sumH2+copy_head->data;
    copy_head = copy_head->next;
    printf("iter h2\n");
  }

   printf("Suma h2 %d finaliza h2\n", sumH2);
  pthread_exit(NULL);
}