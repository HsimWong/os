#include<stdio.h>
#include<unistd.h>

int main(int argc, char const *argv[])
{

	// Determining the real value of getpid() of father.
	printf("MainProcess's getpid() = %d\n", getpid());


	int pid = fork();
	// printf("%d\n", pid);
	
	// After a process is forked, the new forked process is executed first

	if(pid > 1){
		
		wait(pid);

		printf("Parent's getpid() = %d\n", getpid());

		printf("Parent's pid = %d\n", pid);

		// printf("a\n");
		

	}
	else{
		// printf("b\n");
		printf("Son's getpid() = %d\n", getpid());
		printf("Son's pid = %d\n", pid);
	}
	return 0;
}

/*
 * 	Conclusion: 
 *	Son is executed first
 *	son's pid = 0;
 *	Father's pid is greater than 0;
 *	Son's pid != getpid()
 */