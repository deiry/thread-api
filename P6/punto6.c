/*El profesor de un curso desea un programa en lenguaje C que calcule 
la desviación estándar (símbolo σ o s) de las notas obtenidas por sus 
estudiantes en el curso */

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include<math.h>
#include<stdio.h>
#include <sys/queue.h>

#define MAXLON 100


float calculate_standard_deviation(char *);
void read_file(void *);

/*Código extraido de https://www.tutorialspoint.com/data_structures_algorithms/linked_list_program_in_c.htm*/
struct node *head = NULL;
struct node *current = NULL;

/*Código extraido de https://www.tutorialspoint.com/data_structures_algorithms/linked_list_program_in_c.htm*/
struct node {
   float data;
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


struct params_thread{
    char *file;
    int id_thread;
};
  


int main(int argc, char *argv[]){
    int cant = atoi(argv[2]);
    pthread_t hilo[cant];
    struct params_thread params[cant];
    int param;
    char *notas_file = argv[1];
    if (argc== 1) {
        printf ("Ingrese nombre del archivo \n");
        exit (0);
    }else if(argc == 2){
        printf ("Ingrese el número de hilos\n");
        exit (0);
    }else if(argc > 3){
        printf ("Sólo se reciben dos parametros\n");
        exit (0);
    }

    for (param= 0; param<cant; param++){
        //printf("El hilo %d se ha creado\n", param+1);
        int thread_current = param+1;
        params[param].file = notas_file;
        params[param].id_thread = thread_current;
        pthread_create (&hilo[param], NULL, read_file,&params[param]);
    }

        for (param= 0; param< cant; param++) {
        pthread_join (hilo[param], NULL);
        //printf ("El hilo %d ha finalizado\n", param+1);
    }


    return 0;


}

void read_file(void *params){
    struct params_thread* args = (struct params_thread*)params;
    char *name = args->file;
    int id = args->id_thread;

    int pos, cont= 0, leidos, pos_nota = 1;
    char cadena[MAXLON];
    int fd;
    char *token;
    char *delim = ",";
    fd= open(name,O_RDONLY);
    float notas[MAXLON];
    float mean;
       
    while ((leidos =read(fd,cadena,MAXLON))!= 0) {
       
            token = strtok(cadena, delim);
             while (token!= NULL)
            {
                float number = atof(token);

                insertFirst(pos_nota,number);
                pos_nota++;
        
                token = strtok (NULL, ",");
            }



    }

    float std = calculate_standard_deviation(name);
    
    printf("Hilo %d y su desviación (std):  %f\n", id , std);
    pthread_exit(NULL);


}

float calculate_standard_deviation(char *name){
  
    int pos;
    float sum=0.0,mean=0.0;
    int length = 0;

    struct node *copy_mean = head;

    while(copy_mean != NULL) {
        sum = sum+copy_mean->data;
        length++;
      copy_mean = copy_mean->next;
   }
    
    mean = sum/length;
   
   float sumatoria = 0.0;
    struct node *copy_sum = head;
    while(copy_sum !=NULL){
        double aux = pow((copy_sum->data-mean),2);
        sumatoria = sumatoria + aux;
        copy_sum = copy_sum->next;
    }
 
    float std = sqrt(sumatoria/(length));
    return std;


}