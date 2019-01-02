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
		/* 共享存储区的建立，得到存储区的描述符，开通读写权限*/
		int shid = shmget(SHM_KEY, SIZE, IPC_CREAT | 0666);
		/* 共享存储区的附接，得到存储区的地址*/
		int * addr = shmat(shid, 0, 0);
		/*在子进程进行完毕后在进行后续操作 */
		wait(pid);
		printf("Number reveived are:\n");
		/* 获取存储区内部信息 */
		for(int i = 0; i < 10; i++){
			printf("%d\n", *(addr + i * sizeof(int)));
		}
		/*打印*/
		printf("Their second power values are:\n");
		for (int i = 0; i < 10; i++){
			printf("%ld\n",(long int)(*(addr + i * sizeof(int)) * (*(addr + i * sizeof(int)))));
		}
		/* 共享存储区断开 */
		shmdt(addr);
		/* 共享存储区释放 */
		shmctl(shid, IPC_RMID, 0);
	}	
	else{
		/* 共享存储区的建立，得到存储区的描述符，开通读写权限*/
		int shid = shmget(SHM_KEY, SIZE, IPC_CREAT | 0666);
		/* 共享存储区的附接，得到存储区的地址*/
		int * addr = shmat(shid, 0, 0);
		/* 信息录入*/
		for (int i = 0; i < 10; i++){
			printf("Please input the %d number", i);
			scanf("%d", addr + i * sizeof(int));
		}
		/* 将当前进程放回READY队列*/
		sleep(0);
	}
	return 0;
}

