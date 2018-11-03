#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char const *argv[])
{


	// Determining the real value of getpid() of father.
	printf("MainProcess's getpid() = %d\n", getpid());


	
	// printf("%d\n", pid);
	
	// After a process is forked, the new forked process is executed first


	// In this scope, field[0] is opened for reading
	// field[1] is opened for writing
	int field[2];
	pipe(field);
	// char buf_write[200];
	char buf_read[200];

	int pid_1 = fork();
	int pid_2 = fork();
	if(pid_1){
		
		wait(pid_1);

		printf("Parent's getpid() = %d\n", getpid());

		printf("Parent's pid_1 = %d\n", pid_1);
		close(field[1]);
		read(field[0], buf_read, 24);
		printf("%s\n", buf_read);
		// printf("a\n");
		

	}
	else{
		// printf("b\n");
		
		
		// Here declares what son is doing
		if(pid_2){

			printf("Son's getpid() = %d\n", getpid());
			printf("Son's pid_1 = %d\n", pid_1);
			printf("Son's pid_2 = %d\n", pid_2);
			close(field[0]);
			char * info = "Child 1 sends a message.";
			write(field[1], info, strlen(info));
			// printf("%s", info);

		}
		// Declaration of the actions of grandson
		else{
			printf("Grandson's getpid = %d\n", getpid());
			printf("Grandson's pid_1 = %d\n", pid_1);
			printf("Grandson's pid_2 = %d\n", pid_2);
			close(field[0]);
			char * info = "Child 2 sends a message.";
			write(field[1], info, strlen(info));
			// close(field[0]);
			// char * son_info;
			// strcpy(son_info, "Child 2 sends a message.");
			// write(field[1], son_info, strlen(son_info));
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