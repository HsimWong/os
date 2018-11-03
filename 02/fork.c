#include<stdio.h>
#include<unistd.h>

int main(int argc, char const *argv[])
{
	
	int pid = fork();
	if(pid > 1){
		
		wait(pid);
		// printf("a\n");
		printf("Son's pid is %d\n", getpid());
	}
	else{
		// printf("b\n");
		printf("Parent's pid is %d\n", getpid());
	}
	return 0;
}