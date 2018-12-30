#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char const *argv[]){
	/* Description of establishment of pipe.
	 * In this scope, field[0] is opened for reading
	 * while field[1] is opened for writing*/
	int field[2];			// pipe field[2] declaration
	pipe(field);			// pipe() for initialization
	char buf_read[200];

	/* Use fork() function to establish a new process.*/	
	int pid_1 = fork();
	if(pid_1){	
		/* Activity declaration of Father's process*/
		wait(pid_1);
		/* Father process reading from field[0] requires
		 * close() function on field[1].*/
		close(field[1]);
		read(field[0], buf_read, 24);
		printf("%s\n", buf_read);
	}

	else{
		int pid_2 = fork();		// Another process is established.
		/* Here declares what sons are doing */
		if(pid_2){
			/* Declaration of son
			 * Son process reading from field[1] requires
		 	 * close() function on field[0].*/
			close(field[0]);
			char * info = "Child 1 sends a message.";
			write(field[1], info, strlen(info));
		}
		else{
			/* Declaration of Grandson
			 * Grandson process reading from field[0] requires
		 	 * close() function on field[0].*/
			close(field[0]);
			char * info = "Child 2 sends a message.";
			write(field[1], info, strlen(info));
		}
	}
	return 0;
}