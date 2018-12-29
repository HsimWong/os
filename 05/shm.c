#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#define SHM_KEY 1221
#define SIZE 1024

int main(){
	int pid = fork();
	if(pid > 0){
		int shid = shmget(SHM_KEY, SIZE, IPC_CREAT | 0666);
		int * addr = shmat(shid, 0, 0);
		wait(pid);
		printf("Number reveived are:\n");
		for(int i = 0; i < 10; i++){
			printf("%d\n", *(addr + i * sizeof(int)));
		}
		printf("Their second power values are:\n");
		for (int i = 0; i < 10; i++){
			printf("%d\n",(int)(*(addr + i * sizeof(int)) * (*(addr + i * sizeof(int)))));
		}
		shmdt(addr);
		shmctl(shid, IPC_RMID, 0);
	}	
	else{
		int shid = shmget(SHM_KEY, SIZE, IPC_CREAT | 0666);
		int * addr = shmat(shid, 0, 0);
		for (int i = 0; i < 10; i++){
			printf("Please input the %d number", i);
			scanf("%d", addr + i * sizeof(int));
		}
		// printf("Please input:");
		// scanf("%d", addr);
		sleep(0);
	}
	return 0;
}

