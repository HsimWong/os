#include <stdio.h>
#include <pthread.h>

/* Description of the first thread
 * which just prints a line in the command.*/
void myThread1(){
	printf("This line is printed by thread 1\n");
	return;
}

/* Description of the second thread
 * which just prints a line in the command.*/
void myThread2(){
	printf("This is printed by thread 2\n");
	return;
}

int main(){
	
	pthread_t id_1;
	pthread_t id_2;
	pthread_create(&id_1, NULL, (void *)myThread1, NULL);
	pthread_create(&id_2, NULL, (void *)myThread2, NULL);
	pthread_join(id_1, NULL);
	pthread_join(id_2, NULL);
	printf("This is printed by main thread\n");
	return 0;
}
