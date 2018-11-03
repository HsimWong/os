#include<stdio.h>
#include<unistd.h>
#include<math.h>


char * int2str(int a){
	int digit = 1 + log10(a);
	char * ret[digit];
	// for(int i = digit - 1; i > 0; i--){
	// 	ret[digit - i - 1]
	// }
	for (int i = 0; i < digit; i++){
		char temp = (char)(48 + a % pow(10, i + 1))
		ret[i] = temp;
	}
	return i;
}

int str2int(char * str){
	int digit = strlen(str);
	for(int i = 0; i < digit; i++){
		
	}
}

int main(int argc, char const *argv[])
{
	/* code */
	int pipe(int field[2]);
	// field[0] is for reading, while field[1] is for writing.
	int pid_1 = fork();
	int pid_2 = fork();

	// int byte_num;
	if(pid_1 > 1){
		wait(pid_1);
		char * buf_1 = "Child 1 is sending a message.\n";
		write(field[1], buf_1, strlen(buf_1));
	}
	
	else if(pid_2 > 1){
		wait(pid_2);
		char * buf_2 = "Child 2 is sending a message.\n";
		write(field[1], buf_2, strlen(buf_2));
	}

	else{
		 char * read_1;
		 char * read_2;

	}


	return 0;
}