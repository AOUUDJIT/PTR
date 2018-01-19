#include <stdlib.h>
#include <stdio.h>
#include <pthread.h> // pthread
#include <unistd.h>  // sleep
#include <time.h>    // time
#include "sens.h"

pthread_mutex_t verrou_sens  = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t verrou_sensInverse  = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t fifo  = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t fifo1  = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t fifo2  = PTHREAD_MUTEX_INITIALIZER;

 char data1[] = {'A','B','C'};
char data_i1[] = {'C','B','A'};
char data2[] = {'A','B','D','C'};
char data_i2[] = {'C','B','A'};
char data_i3[] = {'C','E','A'};

clock_t t1d[30], t2d[30],t3d[30];
clock_t t1a[30], t2a[30],t3a[30];

int nb_train =0;
extern
void* sens(void *arg) {
	int id = *((int*) arg);
	int i;

	

	for (i = 0; i < 2; i++) {

		if ((id==0)){
		printf("le Train %d  veut s'engager sur la voie  %c%c\n", id+1,data1[i],data1[i+1]);
        	fflush(stdout);
		}

		if (id==1){
		printf("le Train %d  veut s'engager sur la voie %c%c\n", id+1,data2[i],data2[i+1]);		
        	fflush(stdout);
		}
		
		if (id==2){
		printf("le Train %d  veut s'engager sur la voie %c%c\n", id+1,data2[i],data2[i+1]);
        	fflush(stdout);
		}
		
		pthread_mutex_lock(&fifo); 
		pthread_mutex_lock(&verrou_sens); // verou les trains du sens 
		nb_train += 1;

    		if (nb_train==1){ 
		    pthread_mutex_lock(&verrou_sensInverse);// verou les trains du sensInverse
		}

		pthread_mutex_unlock(&verrou_sens);	// débloque les trains du sens 	
		pthread_mutex_unlock(&fifo);			
		

		if (id==0){
		printf("le Train %d  est sur la voie  %c%c\n", id+1,data1[i],data1[i+1]);
        	fflush(stdout);
		}

		if (id==1){
		printf("le Train %d  est sur la voie %c%c\n", id+1,data2[i],data2[i+1]);
        	fflush(stdout);
		}

		if (id==2){
		printf("le Train %d  est sur la voie %c%c\n", id+1,data2[i],data2[i+1]);
        	fflush(stdout);        	
		}

		sleep(rand() % 2);


		if (id==0){
		printf("le Train %d  sort de la voie  %c%c\n", id+1,data1[i],data1[i+1]);
        	fflush(stdout);
		}

		if (id==1){
		printf("le Train %d  sort de la voie %c%c\n", id+1,data2[i],data2[i+1]);
        	fflush(stdout);
		}

		if (id==2){		
		printf("le Train %d  sort de la voie %c%c\n", id+1,data2[i],data2[i+1]);
        	fflush(stdout);
		}

		
		pthread_mutex_lock(&verrou_sens);	// verou les trains du sens 
		nb_train = nb_train - 1;

		if(nb_train == 0) 
	            pthread_mutex_unlock(&verrou_sensInverse);// débloque les trains sensInverse

		pthread_mutex_unlock(&verrou_sens);	// débloque les trains sens						
		sleep(rand() % 3); // le train fait une pause
	
	}
		
	printf("le train %d : fini un sens\n", id+1);
       	fflush(stdout);

    return NULL;
}

extern
void* sens_inverse(void *arg) {
	int id = *((int*) arg);
	int i;
	

	for (i = 0; i < 2; i++) {
		if (id==0){
		printf("le Train %d  veut s'engager sur la voie  %c%c\n", id+1,data_i1[i],data_i1[i+1]);
        	fflush(stdout);
		}

		if (id==1){
		printf("le Train %d  veut s'engager sur la voie %c%c\n", id+1,data_i2[i],data_i2[i+1]);
        	fflush(stdout);
		}

		if (id==2){
		printf("le Train %d  veut s'engager sur la voie %c%c\n", id+1,data_i3[i],data_i3[i+1]);
        	fflush(stdout);
		}
		
		pthread_mutex_lock(&fifo); 
		pthread_mutex_lock(&verrou_sensInverse); // verou les trains du sensInverse 
		nb_train += 1;

    		if (nb_train==1){ 
		    pthread_mutex_lock(&verrou_sens); // verou les trains du sens
		}

		pthread_mutex_unlock(&verrou_sensInverse);// débloque les trains du sensInverse 		
		pthread_mutex_unlock(&fifo);	
		

		if (id==0){
		printf("le Train %d  est sur la voie  %c%c\n", id+1,data_i1[i],data_i1[i+1]);
        	fflush(stdout);
		}

		if (id==1){
		printf("le Train %d  est sur la voie %c%c\n", id+1,data_i2[i],data_i2[i+1]);
        	fflush(stdout);
		}

		if (id==2){
		printf("le Train %d  est sur la voie %c%c\n", id+1,data_i3[i],data_i3[i+1]);
        	fflush(stdout);
		}

		sleep(rand() % 2); 


		if (id==0){
		printf("le Train %d  sort de la voie  %c%c\n", id+1,data_i1[i],data_i1[i+1]);
        	fflush(stdout);
		}

		if (id==1){
		printf("le Train %d  sort de la voie %c%c\n", id+1,data_i2[i],data_i2[i+1]);
        	fflush(stdout);
		}

		if (id==2){
		printf("le Train %d  sort la voie %c%c\n", id+1,data_i3[i],data_i3[i+1]);
        	fflush(stdout);
		}


		pthread_mutex_lock(&verrou_sensInverse);	// verou des trains sensInverse
		nb_train = nb_train - 1;

		if(nb_train == 0) 
	            pthread_mutex_unlock(&verrou_sens);// débloque des trains sens

		pthread_mutex_unlock(&verrou_sensInverse);	// débloque des trains sensInverse
		sleep(rand() % 3); // le lecteur fait une pause

	}
	printf(" fin de parcour le train %d : \n", id+1);
       	fflush(stdout);
    return NULL;
}


