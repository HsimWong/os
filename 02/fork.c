#include<stdio.h>
#include<unistd.h>

int main(int argc, char const *argv[])
{
	int pid;
	if(pid > 1){
		wait(pid);
		printf("a\n");
	}
	else{
		printf("b\n");
	}
	return 0;
}