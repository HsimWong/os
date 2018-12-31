#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void * myThread1(void * var){
	int * temp = (int *)var;
	for(int i = 0; i < 10; i++){
		printf("%d\t", temp[i]);
	}
	printf("\n");
	return (void *)0;
}
void * myThread2(void * var){
	int * temp = (int *)var;
	for(int i = 0; i < 10; i++){
		printf("%d\t", temp[9 - i]);
	}
	printf("\n");
	return (void *)0;
}

int main(int argc, char const *argv[]){
	/* Two threads' tid declaration */
	pthread_t id_1;
	pthread_t id_2;
	/* An array with random values.*/
	int data[10] = {879,894651,23,7894563,32156,64351,87964531,535,894,3465};
	/* Sort the array */
	qsort(data, 10, sizeof(data[0]), cmp);
	int ret_1 = pthread_create(&id_1, NULL, (void *)myThread1, (void *)data);
	pthread_join(id_1, NULL);
	/* Output cannot be made simultaneously.*/
	int ret_2 = pthread_create(&id_2, NULL, (void *)myThread2, (void *)data);
	pthread_join(id_2, NULL);
	
	
	return 0;
}