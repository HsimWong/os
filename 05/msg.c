#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

bool is_exit(char * str){
	char * exit = "exit()";
	bool ret = false;
	for(int i = 0; i < 6; i++){
		ret = (str[i] == exit[i]);
		if(!ret){
			return false;
		}
	}
	return true;
}


int get_line(char * line, int max_size){
	char c;
	int len = 0;
	while((c = getchar()) != EOF && len < max_size){
		line[len++] = c;
		if(c == '\n'){
			break;
		}
	}
}



int main(int argc, char const *argv[])
{
	/* code */
	int child_0 = fork();

	// reciever process
	if(child_0){

	}

	// sender process
	else{
		
		while(true){
			int max_size = 256;
			char * msg = (char *)malloc(sizeof(char) * max_size);
			// while((len = get_line(msg, max_size))!= 0){

			// }
			printf("Entre a message:\n");
			int len = 0;
			char c;
			while((c = getchar()) != EOF && len < max_size){
				msg[len++] = c;
				if(c == '\n'){
					break;
				}
			}

			if (is_exit(msg)){
				break;
			}
		}


	}


	return 0;
}