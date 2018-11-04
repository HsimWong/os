#include <stdio.h>
#include <stdlib.h>
// #include <unistd.h>
#include <semaphore.h>
sem_t s;

void thread1(){
	sem_wait(&s);
	printf("This is thread1\n");
	return;
}

void thread2(){
	printf("This is thread2\n");
	sem_post(&s);
	return;
}

int main(int argc, char const *argv[])
{
	sem_init(&s, 0, 0);
	pthread_t id_1;
	pthread_t id_2;
	pthread_create(&id_1, NULL, (void *)thread1, NULL);
	pthread_create(&id_2, NULL, (void *)thread2, NULL);
	sleep(3);
	pthread_join(id_2, NULL);
	pthread_join(id_1, NULL);
	/* code */
	return 0;
}