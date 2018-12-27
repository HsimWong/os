#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#define MSG_KEY 122
// message queue establising: int msgget(key_t key, int msgflg);
// message send: int msgsnd(msgid, msgp, size, flag);

int open_queue(int keyval){
		int qid;
		qid = msgget(keyval, IPC_CREAT | 0666);
		if(qid == -1){
				perror("Failed in calling msgget");
				return (-1);
				
		}
		return qid;
}

struct mybuf{
		long mtype;
		char text[256];
};


int main(int argc, char const * argv[]){
		// int key_val = 0;
		// if(open_queue(key_val) != -1){
		// 		printf("calling msgget success\n");
		// }

		int pid = fork();
		if(pid > 0){
				struct mybuf buf;
				int msg_id = msgget(MSG_KEY, IPC_CREAT | 0666);
				msgrcv(msg_id, &buf, sizeof(buf.text), 0, MSG_NOERROR);
				printf("Message received: %s\n", buf.text);
				wait(pid);				
		}
		else{
				struct mybuf buf;
				int msg_id = msgget(MSG_KEY, IPC_CREAT | 0666);
				printf("Please input your message:\n");
				fgets(buf.text, sizeof(buf.text), stdin);
				buf.mtype = 1000;
				msgsnd(msg_id, &buf, sizeof(buf.text), IPC_NOWAIT);
		}
		return 0;
}
