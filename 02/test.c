#include<stdio.h>
#include<unistd.h>
void main(int argc, char const *argv[])
{
	int pid;
	char buf[20];
	int a[2];
	pipe(a);
	pid = fork();
	if(!pid){
		close(a[0]);
		write(a[1],"aaaaa", 5);
	}
	else{
		close(a[1]);
		read(a[0], buf, 5);
		printf("%s\n", buf);
	}
}