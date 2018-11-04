#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

int buf[2];
sem_t need;
// sem_t read_1;
sem_t need_0;
sem_t need_1;

void read_1(){
	int temp;
	FILE * fp = fopen("1.dat", "r");
	if(!fp){
		printf("File open error");
		return;
	}
	
	for(int i = 0; !feof(fp); i++){
		wait(need);
		fscanf(fp, "%d", &temp);
	//	printf("%d", temp);
	//	if()			
	}
}

int main(int argc, char const * argv[]){
	// read_1();
	
	sem_init(&need, 0, 2);
	printf("need = %d", need);
	wait(need);
	printf("need after = %d", need);

}
