#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>
#include<unistd.h>
#include<stdlib.h>
#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];

sem_t empty,full;
pthread_mutex_t mutex;
int in,out;

void * producer(void * arg){
	int id = *((int*) arg);
	while(1){
		int r = rand()%1000;
		sem_wait(&empty);
			pthread_mutex_lock(&mutex);
				printf("%d PRODUCER IN C.S\n",id);
				buffer[(in++) % BUFFER_SIZE] = r;
				printf("inserted %d into the buffer... LEAVING BY %d \n ",r,id);
			pthread_mutex_unlock(&mutex);

		sem_post(&full);
		sleep(10);
	}
}

void * consumer(void * arg){
	int id = *((int*) arg);
	while(1){
		sem_wait(&full);
			pthread_mutex_lock(&mutex);
				printf("%d CONSUMER IN C.S\n",id);
				int r = buffer[(out++)%BUFFER_SIZE] ;
				printf("READ THE VALUE %d\n",r);
			pthread_mutex_unlock(&mutex);
		sem_post(&empty);
		sleep(2);
	}
}

int main(int argC,char * argV[]){
	if(argC<3){
		fprintf(stderr,"USAGE: <PRODUCERS><CONSUMERS>");
		exit(1);
	}
	int producers = atoi(argV[1]);
	int consumers = atoi(argV[2]);

	sem_init(&full,0,0);
	sem_init(&empty,0,BUFFER_SIZE);
	pthread_mutex_init(&mutex,NULL);

	int p[producers],c[consumers];
	pthread_t prod[producers] , cons[consumers];
	for(int i=0;i<producers;i++){
		p[i] = i+1;
		pthread_create(&prod[i],NULL,producer,&(p[i]));
	}
	for(int i=0;i<consumers;i++){
		c[i]= i + 1;
		pthread_create(&cons[i],NULL,consumer,&(c[i]));
	}
	for(int i=0;i<producers;i++)
		pthread_join(prod[i],NULL);
	for(int i=0;i<consumers;i++)
		pthread_join(cons[i],NULL);

	sem_destroy(&full);
	sem_destroy(&empty);
	pthread_mutex_destroy(&mutex);

}
