#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>








int buf[2];
sem_t need;
// sem_t read_1;
sem_t need_0;
sem_t need_1;

sem_t rd_0;
sem_t rd_1;

int have_num_0;
int have_num_1;

int get_sem_val(sem_t * sem){
	int sval;
	sem_getvalue(sem, &sval);
	return sval;
}

void * read_0(){
	printf("read_0\n");
	int temp;
	FILE * fp = fopen("1.dat", "r");
	if(!fp){
		printf("File \"1.dat\"open error");
		return (void *)0;
	}
	
	for(int i = 0; !feof(fp); i++){
		have_num_0 = 1;
		sem_wait(&need);
		fscanf(fp, "%d", &temp);
		if(get_sem_val(&need_0)){
			sem_wait(&need_0);
			buf[0] = temp;
			sem_post(&rd_0);
			continue;
		}	
		else{
			sem_wait(&need_1);
			buf[1] = temp;
			sem_post(&rd_1);
			continue;
		}
	}
	have_num_0 = 0;
	return (void *)0;
}

void * read_1(){
	printf("read_1\n");
	int temp;
	FILE * fp = fopen("2.dat", "r");
	if(!fp){
		printf("File \"2.dat\"open error");
		return (void *)0;
	}
	
	for(int i = 0; !feof(fp); i++){

		have_num_0 = 1;
		sem_wait(&need);

		fscanf(fp, "%d", &temp);
		if(get_sem_val(&need_0)){
			sem_wait(&need_0);
			buf[0] = temp;
			sem_post(&rd_0);
			continue;
		}	
		else{
			sem_wait(&need_1);
			buf[1] = temp;
			sem_post(&rd_1);
			continue;
		}

		for(int i = 0; i < 2; i++){
			printf("%d\n", buf[i]);
		}
	}
	have_num_0 = 0;
	return (void *)0;

}

void * multp(){
	while(have_num_1 || have_num_0){
		sem_wait(&rd_0);
		sem_wait(&rd_1);
		int fac_1 = buf[0];
		int fac_2 = buf[1];

		sem_post(&need_1);
		sem_post(&need);
		sem_post(&need_0);
		sem_post(&need);
		printf("%d * %d = %d\n", buf[0], buf[1], (buf[0] * buf[1]));
		
	}

	return (void *)0;
}
void * add(){
	while(have_num_1 || have_num_0){
		sem_wait(&rd_0);
		sem_wait(&rd_1);
		int fac_1 = buf[0];
		int fac_2 = buf[1];
		sem_post(&need_1);
		sem_post(&need);
		sem_post(&need_0);
		sem_post(&need);
		printf("%d + %d = %d\n", buf[0], buf[1], (buf[0] + buf[1]));

	}

	return (void *)0;
}




int main(int argc, char const * argv[]){
	// printf("start\n");
	sem_init(&need, 0, 2);
	sem_init(&need_0, 0, 1);
	sem_init(&need_1, 0, 1);
	sem_init(&rd_1, 0, 0);
	sem_init(&rd_0, 0, 0);


	pthread_t id_add;
	pthread_t id_mul;
	pthread_t id_r_0;
	pthread_t id_r_1;
	pthread_create(&id_r_0, NULL, (void *)read_0, NULL);

	pthread_create(&id_r_1, NULL, (void *)read_1, NULL);
	pthread_create(&id_add, NULL, (void *)multp, NULL);
	pthread_create(&id_mul, NULL, (void *)add, NULL);


	// sleep(10);
	pthread_join(&id_r_0, NULL);
	pthread_join(&id_r_1, NULL);
	pthread_join(&id_add, NULL);
	pthread_join(&id_mul, NULL);
	



	return 0;

}

// Notes Here:
// 1. Use sem_wait(), sem_post() in stead of implicit wait()


// /home/ryan/Desktop/os/04/semaphore.c: In function ‘main’:
// /home/ryan/Desktop/os/04/semaphore.c:109:2: warning: implicit declaration of function ‘pthread_create’ [-Wimplicit-function-declaration]
//   pthread_create(&id_r_0, NULL, (void *)read_0, NULL);
//   ^
// /home/ryan/Desktop/os/04/semaphore.c:113:2: warning: implicit declaration of function ‘sleep’ [-Wimplicit-function-declaration]
//   sleep(5);
//   ^
// /home/ryan/Desktop/os/04/semaphore.c:114:2: warning: implicit declaration of function ‘pthread_join’ [-Wimplicit-function-declaration]
//   pthread_join(&id_r_0, NULL);
//   ^
// read_1
// read_0
// -1 + -2 = -3
// 1 + -3 = -2
// 2 + -4 = -2
// 3 + -5 = -2
// 4 + -6 = -2
// 5 + -7 = -2
// 6 + -8 = -2
// 7 + -9 = -2
// 8 + -10 = -2
// 9 + -10 = -1
// [Finished in 5.2s]

// ryan@ubuntu:~/Desktop/os/04$ ./semaphore
// read_1
// read_0
// -1 + -2 = -3
// -3 + -4 = -7
// 1 + 2 = 3
// -5 + -6 = -11
// -7 + -8 = -15
// -9 + -10 = -19
// 3 * 4 = 12
// 5 * 6 = 30
// 7 * 8 = 56
// 9 * 10 = 90
