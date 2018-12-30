#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main(int argc, char const *argv[]){
    /* Use fork() function to establish a new process.*/	
    int pid_1 = fork();
    if(pid_1){
        /* Activity declaration of Father's process*/
        wait(pid_1);
        /* print loop here.*/
        for(int i = 0; i < 1000; i++){
            if(i % 10 == 0){
                printf("a ");
            }
        }
        printf("\n");
	}

	else{
        int pid_2 = fork();		// Another process is established.
        /* Here declares what sons are doing */
        if(pid_2){
            /* Declaration of son process */
            wait(pid_2);
            for(int i = 0; i < 1000; i++){
                if(i % 10 == 0){
                    printf("b ");
                }
                
            }
			printf("\n");
        }
        else{
            /* Declaration of Grandson*/
            /* print loop here.*/
            for(int i = 0; i < 1000; i++){
                if(i % 10 == 0){
                    printf("c ");
                }
            }
            printf("\n");
        }
    }
    return 0;
}
