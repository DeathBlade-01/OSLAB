#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#define SIZE 1024
int main(){
        key_t key = ftok("SHMFILE",65);
	if(key == -1){
		printf("SORRY, KEY GEN FAILED\n");
		exit(1);
	}
        int shmid = shmget(key,SIZE,0666 | IPC_CREAT);
        char * str = (char *) shmat(shmid,NULL,0);
	printf("ENTER STRING PLS");
	char buffer[20];
	scanf("%s",buffer);
	strcat(str,buffer);
	printf("DATA WRITTEN");
	shmdt(str);
	return 0;
}
