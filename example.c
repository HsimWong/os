#include<stdio.h>
#include<pthread.h>

void thread(){
	printf("This is a thread\n");
}

int main(int argc, char const *argv[])
{
	pthread_t id;
	pthread_create(&id, NULL, (void *)thread, NULL);
	thread_join(id, NULL);
	print("This is main");
	return 0;
}