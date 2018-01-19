#include <stdio.h>   // printf
#include <pthread.h> // pthread
#include <unistd.h>  // sleep
#include <stdlib.h>  // srand
#include <time.h>    // time
#include "sens.h"
				
pthread_mutex_t verrou_sens  = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t verrou_sensInverse  = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t fifo  = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t fifo1  = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t fifo2  = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond;


int main() {
	int i, nb[3];
	srand(time(NULL)); // initialisation de rand
    pthread_t tid[3];


	for (i = 0; i < 1; i++) {
		nb[i] = i;
    	pthread_create(&tid[i], NULL, Train1, (void*) &nb[i]);
    }
	for (i = 0; i < 1; i++) {
		nb[i+1] = i+1;
		pthread_create(&tid[i+1], NULL, Train2, (void*) &nb[i+1]);
    }
	for (i = 0; i < 1; i++) {
		nb[i+2] = i+2;
		pthread_create(&tid[i+2], NULL, Train3, (void*) &nb[i+2]);
    }
		

    for (i = 0; i < 3; i++) {
		pthread_join(tid[i], NULL);
    }
    
    puts("les Trajets sont terminées");
    fflush(stdout);	

    pthread_mutex_destroy(&verrou_sens);
    pthread_mutex_destroy(&verrou_sensInverse);
    pthread_mutex_destroy(&fifo);
       pthread_mutex_destroy(&fifo1);
    pthread_mutex_destroy(&fifo2);
    pthread_cond_destroy(&cond);

    return 0;
}
