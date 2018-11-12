#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

int buf[2];
sem_t write_buf_0;
sem_t write_buf_1;
sem_t write_buf;
sem_t take_for_cal;
sem_t ready_for_cal;
sem_t check_write_0;
sem_t check_write;



int get_sem_val(sem_t * sem){
	int sval;
	sem_getvalue(sem, &sval);
	return sval;
}


void * write_0(){

	// FILE * fp = fopen("0.dat", "r");
	// if(!fp){
	// 	printf("File \"1.dat\" opening failed");
	// 	return (void *)0;
	// }

	int data_set[] = {1,2,3,4,5,6,7,8,9,10};

	for(int i = 0; i < 10; i++){
		printf("wr_0 in working\n");
		int temp = data_set[i];
		sem_wait(&write_buf);
		sem_wait(&check_write_0);
		if(get_sem_val(& write_buf_0)){
			sem_wait(&write_buf_0);
			buf[0] = temp;
		}
		else{
			sem_wait(&write_buf_1);
			buf[1] = temp;
		}
		sem_post(&check_write_0);
		sem_wait(&check_write);
		if(get_sem_val(&write_buf) == 0){
			sem_post(&ready_for_cal);
		}
		sem_post(&check_write);
	}
	return (void *)0;
}

void * write_1(){
	// FILE * fp = fopen("1.dat", "r");
	// if(!fp){
	// 	printf("File \"1.dat\" opening failed");
	// 	return (void *)0;
	// }

	int data_set[] = {-1, -2, -3, -4, -5, -6, -7, -8, -9, -10};

	for(int i = 0; i < 10; i++){
		printf("w_1 in working\n");
		int temp = data_set[i];
		sem_wait(&write_buf);
		sem_wait(&check_write_0);
		if(get_sem_val(& write_buf_0)){
			sem_wait(&write_buf_0);
			buf[0] = temp;
		}
		else{
			sem_wait(&write_buf_1);
			buf[1] = temp;
		}
		sem_post(&check_write_0);
		sem_wait(&check_write);
		if(get_sem_val(&write_buf) == 0){
			sem_post(&ready_for_cal);
		}
		sem_post(&check_write);
	}

	return (void *) 0;
}


void * AddFun(){

	sem_wait(&ready_for_cal);
	sem_wait(&take_for_cal);
	int temp_0 = buf[0];
	int temp_1 = buf[1];
	printf("%d + %d = %d\n", temp_0, temp_1, temp_0 + temp_1);
	sem_post(&take_for_cal);
	sem_post(&write_buf_0);
	sem_post(&write_buf);
	sem_post(&write_buf_1);
	sem_post(&write_buf);
	return (void *) 0;
}

void * MulFun(){

	sem_wait(&ready_for_cal);
	sem_wait(&take_for_cal);
	int temp_0 = buf[0];
	int temp_1 = buf[1];
	printf("%d * %d = %d\n", temp_0, temp_1, temp_0 * temp_1);
	sem_post(&take_for_cal);
	sem_post(&write_buf_0);
	sem_post(&write_buf);
	sem_post(&write_buf_1);
	sem_post(&write_buf);
	return (void *) 0;
}

int main(int argc, char const *argv[]){
	/* code */
	sem_init(&write_buf_0, 0, 1);
	sem_init(&write_buf_1, 0, 1);
	sem_init(&write_buf, 0, 2);
	sem_init(&take_for_cal, 0, 0);
	sem_init(&ready_for_cal, 0, 0);
	sem_init(&check_write_0, 0, 1);
	sem_init(&check_write, 0, 1);

	printf("ready_for_cal: %d\n", get_sem_val(&ready_for_cal));

	pthread_t id_write_0;
	pthread_t id_write_1;
	pthread_t id_AddFun;
	pthread_t id_MulFun;

	pthread_create(&id_write_0, NULL, (void *)write_0, NULL);
	pthread_create(&id_write_1, NULL, (void *)write_1, NULL);
	pthread_create(&id_AddFun, NULL, (void *)AddFun, NULL);
	pthread_create(&id_MulFun, NULL, (void *)MulFun, NULL);


	pthread_join(id_write_0, NULL);
	pthread_join(id_write_1, NULL);
	pthread_join(id_AddFun, NULL);
	pthread_join(id_MulFun, NULL);


	return 0;
}