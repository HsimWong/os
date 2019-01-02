#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

/* int [] for the buffer of temporary integer holder */
int buf[2];

/* semaphores declaration*/
sem_t Write;
sem_t take;

sem_t check_idx;

int insert_index;

void * write_0(){	
	int data_set[] = {
			-1, -2, -3, -4, -5, -6, -7, -8, -9, -10
	};
	
	/* Passing values towards buffer array*/
	for(int i = 0; i < 10; i++){
		sem_wait(&Write);
		buf[insert_index] = data_set[i];
		insert_index = (insert_index + 1) % 2;
		//printf("%d is inserted\n", data_set[i]);
	/* Check whether to post signal "take"*/
	sem_wait(&check_idx);
	if(insert_index == 0){
		sem_post(&take);
		// printf("write0: ready to take\n");
	}
	sem_post(&check_idx);
	
}
return (void *)0;
}

void * write_1(){
	int data_set[] = {
		1, 2, 3, 4, 5, 6, 7, 8, 9, 10
	};

	for (int i = 0; i < 10; i++){
		sem_wait(&Write);
		buf[insert_index] = data_set[i];
		insert_index = (insert_index + 1) % 2;
		//printf("%d is inserted\n", data_set[i]);
	

	sem_wait(&check_idx);
	if(insert_index == 0){
		sem_post(&take);
		//printf("write1: ready to take\n");
	}
	sem_post(&check_idx);
	}
	return (void *)0;
}
void * AddFun(){
	for(int i = 0; i < 10; i++){
			
		sem_wait(&take);
		int temp_0 = buf[0];
		int temp_1 = buf[1];
		printf("%d + %d = %d\n", temp_0, temp_1, temp_0 + temp_1);
		sem_post(&Write);
		sem_post(&Write);
	}
	return (void *)0;

}

void * MulFun(){
	for(int i = 0; i < 10; i++){
			sem_wait(&take);
			int temp_0 = buf[0];
			int temp_1 = buf[1];
			printf("%d * %d = %d\n", temp_0, temp_1, temp_0 * temp_1);
			sem_post(&Write);
			sem_post(&Write);
	}
	return (void*) 0;
}

int main(int argc, char const * argv[]){
		/* semaphores' initialization*/
		sem_init(&Write, 0, 2);
		sem_init(&take, 0, 0);
		sem_init(&check_idx, 0, 1);
		/* index of inserting value initialzation*/
		insert_index = 0;
		/* Threads declaration */
		pthread_t id_write_0;
		pthread_t id_write_1;
		pthread_t id_AddFun;
		pthread_t id_MulFun;
		/* Threads initialization */
		pthread_create(&id_write_1, NULL, (void *)write_1, NULL);
		pthread_create(&id_write_0, NULL, (void *)write_0, NULL);
		pthread_create(&id_MulFun, NULL, (void *)MulFun, NULL);
		pthread_create(&id_AddFun, NULL, (void *)AddFun, NULL);
		/* Threads finish */
		// pthread_join(id_write_0, NULL);
		// pthread_join(id_write_1, NULL);
		pthread_join(id_AddFun, NULL);
		pthread_join(id_MulFun, NULL);
		pthread_join(id_write_0, NULL);
		pthread_join(id_write_1, NULL);
		return 0;
}


