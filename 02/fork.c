#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char const *argv[]){
	/* Here describes the father process
	 * Use getpid() to get current pid #.*/
	printf("MainProcess's getpid() = %d\n", getpid());

	/* Description of establishment of pipe.
	 * In this scope, field[0] is opened for reading
	 * while field[1] is opened for writing*/
	int field[2];			// pipe field[2] declaration
	pipe(field);			// pipe() for initialization
	char buf_read[200];

	/* Use fork() function to establish a new process.*/	
	int pid_1 = fork();
	
	/* What is known:
	 * 1. When a new process is forked, pid_1 of son's
	 * 	  process equals 0, which is false
	 * 2. Sub-process(son) is processed first*/
	if(pid_1){	
		/* Activity declaration of Father's process*/
		wait(pid_1);
		printf("Parent's getpid() = %d\n", getpid());
		printf("Parent's pid_1 = %d\n", pid_1);
	}

	else{
		int pid_2 = fork();		// Another process is established.
		/* Here declares what sons are doing */
		if(pid_2){
			/* Declaration of Son process*/
			printf("Son's getpid() = %d\n", getpid());
			printf("Son's pid_1 = %d\n", pid_1);
			printf("Son's pid_2 = %d\n", pid_2);
		}
		else{
			/* Declaration of Grandson*/
			printf("Grandson's getpid = %d\n", getpid());
			printf("Grandson's pid_1 = %d\n", pid_1);
			printf("Grandson's pid_2 = %d\n", pid_2);
		}
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
