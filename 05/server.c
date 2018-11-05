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

    int msgid = -1;  

      struct msg_st data;  

    long int msgtype = 0;

    msgid = msgget((key_t)1234,IPC_CREAT);

    if(msgid == -1){ 

        printf("msgget failed\n");  

        exit(EXIT_FAILURE);  

        } 

    printf("Server start!\n");

    while(1){

        

        if(msgrcv(msgid, (void*)&data, 256, msgtype, 0) == -1){
                    printf("msgrcv failed\n");  
                    exit(EXIT_FAILURE);  
            }//end if

        
        //success
        printf("from client:%s\n",data.text);


    }//end while








}