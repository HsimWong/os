#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int buf[2];
sem_t need_1;
sem_t need_0;
sem_t need;

sem_t data_update_num;

sem_t ready_for_cal;
sem_t cal_fin;

// function for getting value of semaphore variable
int get_sem_val(sem_t * sem){
	int sval;
	sem_getvalue(sem, &sval);
	return sval;
}

void * read_0(){
	printf("read_0 start working.\n");
	int dataset[] = {1,2,3,4,5,6,7,8,9,10};
	for(int i = 0; i < (sizeof(dataset)) / sizeof(dataset[0]); i++){
		int temp = dataset[i];
		sem_wait(&cal_fin);
		sem_wait(&need);
		if(get_sem_val(&need_0)){
			sem_wait(&need_0);
			buf[0] = temp;
			sem_post(&data_update_num);
			// sem_post(&need_0);
			// sem_post(&need);
			// continue;
		}
		else{
			sem_wait(&need_1);
			buf[1] = temp;
			// data_update_num++;
			sem_post(&data_update_num);
			// sem_post(&need_1);
			// sem
		}
		if(get_sem_val(&data_update_num) == 2){
			
		}

	}

	return (void *)0;
}

void * read_1(){
	printf("read_1 start working.\n");
	return (void *)0;
	// Action Area





	return (void *)0;
}

void * multp(){
	printf("Mul\n");
	return (void *)0;
}

void * add(){
	printf("add\n");
	printf("%d", buf[0] * buf[1]);
	return (void *)0;
}



int main(int argc, char const *argv[])
{
	sem_init(&need, 0, 2);
	sem_init(&need_0, 0, 1);
	sem_init(&need_1, 0, 1);
	sem_init(&ready_for_cal, 0, 0);
	sem_init(&cal_fin, 0, 1);

	pthread_t id_mul = 4;
	pthread_t id_r_0 = 5;
	pthread_t id_r_1 = 6;
	pthread_t id_add = 8;

	pthread_create(&id_r_0, NULL, (void *)read_0, NULL);
	pthread_create(&id_r_1, NULL, (void *)read_1, NULL);
	pthread_create(&id_add, NULL, (void *)multp, NULL);
	pthread_create(&id_mul, NULL, (void *)add, NULL);

	// sleep(10);
	pthread_join(id_r_0, NULL);
	pthread_join(id_r_1, NULL);
	pthread_join(id_add, NULL);
	pthread_join(id_mul, NULL);
	// pthread_join(id_mon, NULL);

	return 0;
}

