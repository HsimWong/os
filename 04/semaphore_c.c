#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

int buf[2];
sem_t read_buf_0;
sem_t read_buf_1;
sem_t read_buf;
sem_t take_for_cal;
sem_t ready_for_cal;
sem_t check_read_0;
sem_t check_read;

int get_sem_val(sem_t * sem){
	int sval;
	sem_getvalue(sem, &sval);
	return sval;
}


void * read_0(){
	FILE * fp = fopen("0.dat", "r");
	if(!fp){
		printf("File \"1.dat\" opening failed");
		return (void *)0;
	}

	int data_set = {1,2,3,4,5,6,7,8,9,10};

	for(int i = 0; i < 10; i++){
		int temp = data_set[i];
		sem_wait(&read_buf);
		sem_wait(&check_read_0);
		if(get_sem_val(& read_buf_0)){
			sem_wait(&read_buf_0);
			buf[0] = temp;
		}
		else{
			sem_wait(&read_buf_1);
			buf[1] = temp;
		}
		sem_post(&check_read_0);
		
	}
}

void * read_1(){
	FILE * fp = fopen("1.dat");

	int data_set = {-1, -2, -3, -4, -5, -6, -7, -8, -9, -10};

	for(int i = 0; i < 10; i++){
		
	}
}

void * AddFun(){
	
}

void * MulFun(){

}
