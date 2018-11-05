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

struct msg_st{
	long int msg_type;
	char text[256];
}

int main(int argc, char const *argv[])
{
	/* code */
	int child_0 = fork();

	// reciever process
	if(child_0){
		int msg_id = -1;
		struct msg_st data;
		msg_id = msgget((key_t)1234, IPC_CREAT | 0666);
		if(msg_id == -1){
			printf("msgget failed\n");
			exit(EXIT_FALURE);
		}
		printf("Receiver start\n");
		while(1){
			int status = msgrcv(msg_id, (void*)&data, 256, msg_type, 0);
			if(status == -1){
				printf("msgrcv failed\n");
				exit(EXIT_FAILURE);
			}
			printf("Message from sender:%s\n", data.text)
			
		}
	}

	// sender process
	else{
		
		while(true){
			int max_size = 256;
			// char * msg_1 = "This is a message";
			// char * msg_2 = "This is another message";
			char * msg[256];
			memset(buffer, '\0', 256);
			//int msg_id = -1;
			struct msg_st data;
			long int msg_type = 0;
			int msg_id = msgget((key_t)1234, IPC_CREAT | 0666);
			if(msg_id == -1){
				printf("msgget failed\n");
				exit(EXIT_FAILURE);
			}

			while(1){
				printf("Enter a string\n");
				fgets(msg, 256, stdin);
				strcpy(data.text, msg);
				data.msg_type = 1;
				if(is_exit(data.text)){
					break;
				}
				msgsnd(msg_id, (void * )&data, 256, 0);
			}

		}


	}


	return 0;
}
