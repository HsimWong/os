#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <string.h>
#define MSG_KEY 1223
// message queue establising: int msgget(key_t key, int msgflg);
// message send: int msgsnd(msgid, msgp, size, flag);

/* Define a set of message as a strcture.*/
struct mybuf{
	long mtype;
	char text[256];
};

int main(int argc, char const * argv[]){

	int pid = fork();
	
	if(pid > 0){
		while(1){
			struct mybuf buf;
			/* Message queue establishment*/
			int msg_id = msgget(MSG_KEY, IPC_CREAT | 0666);
			/* Receive message from queue and cp . buf*/
			msgrcv(msg_id, &buf, sizeof(buf.text), 0, MSG_NOERROR);
			/* Check if the message received === 'exit' */
			if(buf.text[0] == 'e' && buf.text[1] == 'x' && buf.text[2] == 'i' && buf.text[3] == 't'){
				break;
			}
			/* Print the message */
			printf("Message received: %s\n", buf.text);
		}		
	}
	else{
		while(1){
			struct mybuf buf;
			/* Message queue establishment*/
			int msg_id = msgget(MSG_KEY, IPC_CREAT | 0666);
			/* Receive message from console and print */
			printf("Please input your message:\n");
			fgets(buf.text, sizeof(buf.text), stdin);
			
			buf.mtype = 1000;
			/* Send the message */
			msgsnd(msg_id, &buf, sizeof(buf.text), IPC_NOWAIT);
			/* Check if the message received === 'exit' */
			if(buf.text[0] == 'e' && buf.text[1] == 'x' && buf.text[2] == 'i' && buf.text[3] == 't'){
				printf("Goodbye\n");
				abort = 1;
				break;
			}
			/* Put the current process into READY QUEUE */
			sleep(0);
		}
	}
	return 0;
}
