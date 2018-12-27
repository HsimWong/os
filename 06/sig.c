#include <stdio.h>
#include <signal.h>

static void sig_int(int no){
	printf("recieved SIGINT signal:%d\n", no);
	printf("pid of this process is %d\n", getpid());
	return;
}

static void sig_usr(int no){
		printf("received SIGUSR1 signal:%d\n", no);
		printf("pid of this process is %d\n", getpid());
		return;
}

int main(){
		int pid = fork();
		
		if(pid == 0){
				/* This is the child*/
				printf("Child's pid %d\n", getpid());
				signal(SIGINT, sig_int);
				for(;;);
		}
		else{
				printf("Father's pid %d\n", getpid());
				signal(SIGUSR1, sig_usr);
				
				for(;;);
		}
		return 0;


//		signal(SIGINT, myfunc);


		return 0;
}
