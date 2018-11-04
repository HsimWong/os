#include <stdio.h>
#include <pthread.h>

void * myThread1(void * chr){
	// printf("This line is printed by thread 1\n");
	char * temp = (char *)chr;
	printf("%c\n", * temp);
	return (void *)0;
}

void * myThread2(void * num){
	int * temp = (int *)num;
	printf("%d\n", * temp);
	return (void *)0;
}



int main(int argc, char const *argv[])
{
	pthread_t id_1;
	pthread_t id_2;
	int num = 65536;
	char chr = 96;
	int ret_1 = pthread_create(&id_1, NULL, (void *)myThread1, (void *)&chr);
	pthread_join(id_1, NULL);
	int ret_2 = pthread_create(&id_2, NULL, (void *)myThread2, (void *)&num);
	pthread_join(id_2, NULL);
	printf("This is printed by main thread\n");
	// return 0;
	return 0;
}