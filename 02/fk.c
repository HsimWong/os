#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char const *argv[]){
	/* Fork a sub-process here */	
	int pid_son = fork();

	if(pid_son == 0){
		printf("Son process print an A\n");
	}
	else{
		printf("Father process prints a B\n");
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
