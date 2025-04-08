#include<sys/ipc.h>
#include<sys/shm.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define SIZE 1024
int main(){
        key_t key = ftok("SHMFILE",65);
	if(key == -1){
		printf("SORRY KEY GEN FAILED");
		exit(1);
	}
        int shmid = shmget(key,SIZE,0666 | IPC_CREAT);
        char * str = (char *) shmat(shmid,NULL,0);
        printf("DATA READ: %s",str);
	
        shmdt(str);
	shmctl(shmid,IPC_RMID,NULL);
        return 0;
}
