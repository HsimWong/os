#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

int buf[2];
sem_t write_buf_0;
sem_t write_buf_1;
sem_t take_buf_0;
sem_t take_buf_1;

void *write_0(){
	int data_set[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

	for (int i = 0; i < 10; i++)
	{
		have_data_0 = 1;

		int temp = data_set[i];

		sem_wait(&write_buf_0);
		buf[0] = temp;
		sem_post(&take_buf_0);
	}
	return (void *)0;
}
void *write_1(){
	int data_set[] = {-1, -2, -3, -4, -5, -6, -7, -8, -9, -10};

	for (int i = 0; i < 10; i++)
	{
		int temp = data_set[i];
		sem_wait(&write_buf_1);
		buf[1] = temp;
		sem_post(&take_buf_1);
	}

	return (void *)0;
}

void *AddFun(){
	while (1){
		sem_wait(&take_buf_0);
		sem_wait(&take_buf_1);
		int temp_0 = buf[0];
		int temp_1 = buf[1];
		printf("%d + %d = %d\n", temp_0, temp_1, temp_0 + temp_1);
		sem_post(&write_buf_0);
		sem_post(&write_buf_1);
	}

	return (void *)0;
}

void *MulFun(){
	while (1){
		sem_wait(&take_buf_0);
		sem_wait(&take_buf_1);
		int temp_0 = buf[0];
		int temp_1 = buf[1];
		printf("%d * %d = %d\n", temp_0, temp_1, temp_0 * temp_1);
		sem_post(&write_buf_0);
		sem_post(&write_buf_1);
	}
	return (void *)0;
}

int main(int argc, char const *argv[]){
	sem_init(&write_buf_0, 0, 1);
	sem_init(&write_buf_1, 0, 1);
	sem_init(&take_buf_0, 0, 0);
	sem_init(&take_buf_1, 0, 0);
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
