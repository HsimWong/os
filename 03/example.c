#include<stdio.h>
#include<pthread.h>

void thread(){
	printf("This is a thread\n");
}

int main(int argc, char const *argv[])
{
	pthread_t id;
	pthread_create(&id, NULL, (void *)thread, NULL);
	pthread_join(id, NULL);
	printf("This is main");
	return 0;
}
