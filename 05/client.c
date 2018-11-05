#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <string.h>  
#include <errno.h>  
#include <sys/msg.h>

struct msg_st  

{  

    long int msg_type;  

    char text[256];  

};  


int main(){

    struct msg_st data;
    int msgid = -1;
    char buffer[256];

    memset(buffer,'\0',256);

    msgid = msgget((key_t)1234,IPC_CREAT); 

    if(msgid == -1){
        printf("msgget failed\n");  
            exit(EXIT_FAILURE);  
        }  

    while(1){

        printf("Enter a string\n");
        fgets(buffer,256,stdin);
        strcpy(data.text,buffer);
        data.msg_type=1;
        
        msgsnd(msgid, (void*)&data,256, 0);






    }






}
