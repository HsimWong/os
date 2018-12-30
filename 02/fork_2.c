#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char const *argv[]){
	printf("MainProcess's getpid() = %d\n", getpid());
	int field[2];			// pipe field[2] declaration
	pipe(field);			// pipe() for initialization
	char buf_read[200];

	int pid_1 = fork();
	
	if(pid_1){	
		wait(pid_1);
		printf("Parent's getpid() = %d\n", getpid());
		printf("Parent's pid_1 = %d\n", pid_1);
		close(field[1]);
		read(field[0], buf_read, 24);
		printf("%s\n", buf_read);

		for(int i = 0; i < 1000; i++){
			if(i % 10 == 0){
				printf("a ");
			}
		}
	}

	else{
		int pid_2 = fork();		// Another process is established.
		if(pid_2){
			wait(pid_2);
			printf("Son's getpid() = %d\n", getpid());
			printf("Son's pid_1 = %d\n", pid_1);
			printf("Son's pid_2 = %d\n", pid_2);
			close(field[0]);
			char * info = "Child 1 sends a message.";
			write(field[1], info, strlen(info));
			
			for(int i = 0; i < 1000; i++){
				if(i%10 == 0){
					printf("b ");
				}
			}
		}

		else{
			/* Declaration of Grandson*/
			printf("Grandson's getpid = %d\n", getpid());
			printf("Grandson's pid_1 = %d\n", pid_1);
			printf("Grandson's pid_2 = %d\n", pid_2);
			close(field[0]);
			char * info = "Child 2 sends a message.";
			write(field[1], info, strlen(info));
			
			for(int i = 0; i < 1000; i++){
				if(i%10 == 0){
					printf("c ");
				}
			}
		}
	}
	return 0;
}
