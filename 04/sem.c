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
sem_t write_buf;
sem_t take_for_cal;
sem_t ready_for_cal;
sem_t check_write_0;
sem_t check_write;
int have_data_0;
int have_data_1;


int get_sem_val(sem_t * sem){
	int sval;
	sem_getvalue(sem, &sval);
	return sval;
}



void * write_0(){
	// FILE * fp = fopen("1.dat", "r");
	// if(!fp){
		// printf("File \"1.dat\" opening failed");
	// 	return (void *)0;
	// }

	int data_set[] = {1,2,3,4,5,6,7,8,9,10};

	for(int i = 0; i < 10; i++){
		have_data_0 = 1;
		// printf("w_1 in working\n");
		int temp = data_set[i];
		// printf("write 0 Round %d want write_b\n", i);
		// sem_wait(&write_buf);
		// printf("write 0 Round %d get write_b\n", i);
		// printf("write 0 Round %d want check_write\n", i);
		// sem_wait(&check_write_0);
		// printf("write 0 Round %d get check_write\n", i);
		// if(get_sem_val(& write_buf_0)){
			sem_wait(&write_buf_0);

		// printf("write 0 Round %d get write_buf_0\n", i);
			buf[0] = temp;
		// }
			sem_post(&take_buf_0);
		// else{
		//	sem_wait(&write_buf_1);
			
		// printf("write 0 Round %d get write_buf_1\n", i);
		//	buf[1] = temp;
		// }
		// sem_post(&check_write_0);
		// printf("write 0 round %d release check_write_0 \n", i);
		// sem_wait(&check_write);
		// printf("write 0 round %d get check_write \n", i);
		
		// if(get_sem_val(&write_buf) == 0){
			// sem_post(&ready_for_cal);
			// printf("write 0 round %d release ready_for_cal \n", i);
		
			// sem_post(&take_for_cal);
			// printf("write 0 round %d release takeforcal \n", i);
		
		//}
		// sem_post(&check_write);
		// printf("write 0 round %d release check_write \n", i);
		// if(temp == 10 || temp == -10){
		// 	break;
		// }	
	}
	// have_data_0 = 0;


	return (void *) 0;
}
void * write_1(){
	// FILE * fp = fopen("1.dat", "r");
	// if(!fp){
	//	printf("File \"1.dat\" opening failed");
	// 	return (void *)0;
	// }

	int data_set[] = {-1, -2, -3, -4, -5, -6, -7, -8, -9, -10};

	for(int i = 0; i < 10; i++){
		// printf("w_1 in working\n");
		int temp = data_set[i];
		// printf("write 1 Round %d want write_b\n", i);
		// sem_wait(&write_buf);
		// printf("write 1 Round %d get write_b\n", i);
		// printf("write 1 Round %d want check_write\n", i);
		// sem_wait(&check_write_0);
		// printf("write 1 Round %d get check_write\n", i);
		// if(get_sem_val(& write_buf_0)){
			sem_wait(&write_buf_1);

		// printf("write 1 Round %d get write_buf_0\n", i);
			buf[1] = temp;
			sem_post(&take_buf_1);
		//}
		//else{
		//	sem_wait(&write_buf_1);
			
		// printf("write 1 Round %d get write_buf_1\n", i);
		//	buf[1] = temp;
		
		//sem_post(&check_write_0);
		// printf("write 1 round %d release check_write_0 \n", i);
		//sem_wait(&check_write);
		// printf("write 1 round %d get check_write \n", i);
		
		//if(get_sem_val(&write_buf) == 0){
		//	sem_post(&ready_for_cal);
			// printf("write 1 round %d release ready_for_cal \n", i);
		
		//	sem_post(&take_for_cal);
			// printf("write 1 round %d release takeforcal \n", i);
		
		//}
		//sem_post(&check_write);
		// if(temp == 10 || temp == -10){
		// 	break;
		// }
		// printf("write 1 round %d release check_write \n", i);
		
	}

	return (void *) 0;
}


void * AddFun(){
	while(1){
		// printf("add want ready_for_cal\n");
		//sem_wait(&ready_for_cal);
		// printf("add get ready_for_cal\n");
		// printf("add want take_for_cal\n");
		//sem_wait(&take_for_cal);
		sem_wait(&take_buf_0);
		sem_wait(&take_buf_1);
		// printf("add get take_for_cal\n");
		int temp_0 = buf[0];
		int temp_1 = buf[1];
		printf("%d + %d = %d\n", temp_0, temp_1, temp_0 + temp_1);
		//sem_post(&take_for_cal);
		// printf("add released takeforcal\n");
		sem_post(&write_buf_0);
		// printf("add release write_buf_0\n");
		// sem_post(&write_buf);
		// printf("add release write_buf\n");
		sem_post(&write_buf_1);
		// printf("add release write_buf_1\n");
		// sem_post(&write_buf);
		// printf("add release write_buf\n");
	}

	return (void *) 0;
}

void * MulFun(){
	while(1){
		// printf("mul want ready_for_cal\n");
		// sem_wait(&ready_for_cal);
		// printf("mul get ready_for_cal\n");
		// printf("mul want take_for_cal\n");
		// sem_wait(&take_for_cal);
		// printf("mul get take_for_cal\n");
		sem_wait(&take_buf_0);
		sem_wait(&take_buf_1);
			int temp_0 = buf[0];
		int temp_1 = buf[1];
		printf("%d * %d = %d\n", temp_0, temp_1, temp_0 * temp_1);
		// sem_post(&take_for_cal);
		// printf("mul released takeforcal\n");
		sem_post(&write_buf_0);
		// printf("mul release write_buf_0\n");
		// sem_post(&write_buf);
		// printf("mul release write_buf\n");
		sem_post(&write_buf_1);
		// printf("mul release write_buf_1\n");
		// sem_post(&write_buf);
		// printf("mul release write_buf\n");
	}
	return (void *) 0;
}

int main(int argc, char const *argv[]){
	/* code */
	have_data_0 = have_data_1 = 1;
	sem_init(&write_buf_0, 0, 1);
	sem_init(&write_buf_1, 0, 1);
	sem_init(&write_buf, 0, 2);
	sem_init(&take_for_cal, 0, 0);
	sem_init(&ready_for_cal, 0, 0);
	sem_init(&check_write_0, 0, 1);
	sem_init(&check_write, 0, 1);
	sem_init(&take_buf_0, 0,0);
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
