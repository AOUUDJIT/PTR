#include <stdio.h>   // printf
#include <pthread.h> // pthread
#include <unistd.h>  // sleep
#include <stdlib.h>  // srand
#include <time.h>    // time

#include "sens.h"

 char data1[] = {'A','B','C'};
char data_i1[] = {'C','B','A'};
char data2[] = {'A','B','D','C'};
char data_i2[] = {'C','B','A'};
char data_i3[] = {'C','E','A'};

clock_t t1d[30], t2d[30],t3d[30];
clock_t t1a[30], t2a[30],t3a[30];

int nb_train =0;
				
pthread_mutex_t verrou_sens  = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t verrou_sensInverse  = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t fifo  = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t fifo1  = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t fifo2  = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond;

void* Train1(void *arg) {

	int i;
	float t1,s1;
	for (i=0;i<30;i++){
		t1d[i] = clock(); // temps de dépare
		sens(arg);
		
	
        	sens_inverse(arg);
		t1a[i] = clock()-t1d[i]; // temps de trajet =  temps de D'arrivée- temps de dépare
		s1=s1+t1a[i]; // somme des temps de trajet 
	fprintf(stderr,"le temps de parcours du train 1 jusqu'ici : %f\n",s1);
        	fflush(stderr);
	}
	
	t1=s1/30; // la moyenne de temps de trajet
	fprintf(stderr,"le temps moyen de parcours du train 1 : %f\n",t1);
        	fflush(stderr);
	fprintf(stderr,"le temps total de parcours du train 1: %f\n",s1);
        	fflush(stderr);
    return NULL;
}

void* Train2(void *arg) {
	float t2,s2;
                 	
	int i;
	for (i=0;i<30;i++){
		t2d[i] = clock();		// temps de dépare
		sens(arg);			

	
        	sens_inverse(arg);
		t2a[i] = clock()-t2d[i];	// temps de trajet =  temps de D'arrivée- temps de dépare
	   	 s2=s2+t2a[i];			// somme des temps de trajet 
	fprintf(stderr,"le temps de parcours du train 2 jusqu'ici : %f\n",s2);
        	fflush(stderr);
	}
	
	t2=s2/30; 				// la moyenne de temps de trajet 
	fprintf(stderr,"le temps moyen de parcours du train 2 : %f\n",t2);
	fprintf(stderr,"le temps total des parcours du train 2 :%f\n",s2);

	
    return NULL;
}

void* Train3(void *arg) {

	float t3,s3;
	int i;
	for (i=0;i<30;i++){
		t3d[i] = clock();		// temps de dépare
		sens(arg);

	
        	sens_inverse(arg);
		t3a[i] = clock()-t3d[i];	// temps de trajet =  temps de D'arrivée- temps de dépare
	    	s3=s3+t3a[i];			// somme des temps de trajet 
	fprintf(stderr,"le temps de parcours du train 3 jusqu'ici : %f\n",s3);
	}
	
	t3=s3/30;				// la moyenne de temps de trajet
	fprintf(stderr,"le temps moyen de parcours du train 3 : %f\n",t3);
	fprintf(stderr,"le temps total de parcours du train 3 : %f\n",s3);

    return NULL;
}


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
