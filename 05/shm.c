#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#define SHM_KEY 1221
#define SIZE 1024

int main(){
		int pid = fork();
		if(pid > 0){
				int shid = shmget(SHM_KEY, SIZE, IPC_CREATE | 0666);
				int * addr = shmat(shid, 0, 0);
				wait(pid);
				printf("The input number is: %d\n", * addr);
				// wait(pid);
				shmdt(addr);
				shmctl(shid, IPC_RMID, 0);
		}
		else{
				int shid = shmget(SHM_KEY, SIZE, IPC_CREAT | 0666);
				int * addr = shmat(shid, 0, 0);
				printf("Please input:");
				scanf("%d", addr);
				sleep(0);
		}
		return 0;
}
