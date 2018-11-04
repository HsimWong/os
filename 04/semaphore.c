#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

int buf[2];
sem_t need;
// sem_t read_1;
sem_t need_0;
sem_t need_1;

int get_sem_val(sem_t * sem){
	int sval;
	sem_getvalue(sem, &sval);
	return sval;
}

void read_1(){
	int temp;
	FILE * fp = fopen("1.dat", "r");
	if(!fp){
		printf("File open error");
		return;
	}
	
	for(int i = 0; !feof(fp); i++){
		sem_wait(&need);
		fscanf(fp, "%d", &temp);
	//	printf("%d", temp);
	//	if()			
	}
}



int main(int argc, char const * argv[]){
	sem_init(&need, 0, 2);
	printf("%d\n", get_sem_val(&need));
	sem_wait(&need);
	// sem_wait(&need);
	printf("%d\n", get_sem_val(&need));
	
}
