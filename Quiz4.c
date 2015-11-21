
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#define NUMTHREADS 3
#define TAMVECT 15

struct parameters{
	int down;
	int up;
};

//int sum = 0; /* this data is shared by the thread(s) */
void *runner(void *param); /* threads call this function */
int values[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

int main(int argc, char *argv[])
{
	pthread_t tid[NUMTHREADS]; /* the thread identifier */
	unsigned char cnt =0;
	int sum=0; 	
	double promedio=0;
	int *response[NUMTHREADS];
	
	int value = TAMVECT;
	struct parameters params[NUMTHREADS];
	
		
	params[0].down = 1;
	params[0].up = value/3;
	params[1].down = (value/3)+1;
	params[1].up = (value/3) +(value/3);
	params[2].down = (value/3) +(value/3)+1;
	params[2].up = value;

	/* create the thread */
	for(cnt=0; cnt < NUMTHREADS; cnt++){ 	
		pthread_create(&tid[cnt], NULL, runner, (void*)&params[cnt]);
	}
	/* wait for the thread to exit */
	for(cnt=0; cnt < NUMTHREADS; cnt++){
		pthread_join(tid[cnt], (void**) &response[cnt]);
		sum += *response[cnt];
	}	
	
	for(cnt=0; cnt < NUMTHREADS; cnt++){
		printf("Parcial result %d\n", *response[cnt]);
	}	
	
	printf("Total result = %d\n",sum);
	promedio=sum/15;
	printf("Promedio = %f\n",promedio);
	return EXIT_SUCCESS;
}

/* The thread will begin control in this function */
void *runner(void *param)
{
	int i =	0;
	struct parameters *ptr_params = (struct parameters *)param;
	int lower = ptr_params->down;
	int upper = ptr_params->up;
	int sum = 0;
	int *ptr = (void *) malloc(sizeof(int));
	
	printf("lower: %d     upper: %d \n",lower,upper);
	for (i = lower; i <= upper; i++){
		sum += values[i-1];
		//sum += i;
	}
		
	
	*ptr = sum;	
		
	pthread_exit(ptr);
}