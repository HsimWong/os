#include<stdio.h>
#include<unistd.h>
#include<math.h>
#include<stdlib.h>
/*
 *	The code below is for perperation
 * 	of sending messages in random length
 *	without decomposing strings.
 *
 *	This part will be finished in the 
 *	near future
 */

// char * int2str(int a){
// 	int digit = 1 + log10(a);
// 	char * ret[digit];
// 	// for(int i = digit - 1; i > 0; i--){
// 	// 	ret[digit - i - 1]
// 	// }
// 	for (int i = 0; i < digit; i++){
// 		char temp = (char)(48 + a % pow(10, i + 1))
// 		ret[i] = temp;
// 	}
// 	return i;
// }

// int str2int(char * str){
// 	int digit = strlen(str);
// 	for(int i = 0; i < digit; i++){

// 	}
// }

int main(int argc, char const *argv[])
{
	/* code */


	int field[2];
	pipe(field);

	printf("getpid() = %d\n", getpid());
	int pid_1 = fork();
	printf("pid = %d\n", pid_1);
	// field[0] is for reading, while field[1] is for writing.
	// as to the perspective from the son process
	// int pid_1 = fork();
	// int pid_2 = fork();


	int info_dig = 30;

	// int byte_num;
	// The son_1 process
	
	// if(!wait(pid_1)){
	// 	// wait(pid_1);
	// 	close(field[0]);
	// 	printf("%d", getpid());
	// 	char * buf_1 = "Child 1 is sending a message.\n";
	// 	write(field[1], buf_1, info_dig);
	// 	// exit(0);
	// }
	
	// else if(pid_2 == 0){
	// 	wait(pid_2);
	// 	close(field[0]);
	// 	char * buf_2 = "Child 2 is sending a message.\n";
	// 	write(field[1], buf_2, info_dig);
	// 	exit(0);
	// }

	// else if(pid_1 != 0){
	// 	printf("%d\n", pid_1);
	// 	 char * read_buf;
	// 	 close(field[1]);
	// 	 read(field[0], read_buf, info_dig);
	// 	 printf("%s\n", read_buf);
	// 	 exit(0);
	// }


	return 0;
}