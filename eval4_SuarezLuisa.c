#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>


void *sumkn(void *n);
int lim;

void *sumkn(void *n){

	int i, sum=0, j;
	double h;
	int *ptr = (void *) malloc(sizeof(int));
	int k=*((int *)n);

	if(k>0){
		//printf("limite %d numero %d  ", lim, n );
		h=(lim - 1)/k;
		
		//printf("Funciona %f \n", h );
		for (i=1; i<=h;i++){
			sum=sum+(k*i);
		}
	}

	printf("\nHilo para calcular la sumatoria de los multiplos de %d es: %d \n", k, sum );
	*ptr =sum;

	pthread_exit(ptr);
	//return ptr;
}

int main(int argc, char const *argv[]){
	int i, suma=0;
	int *sum[3];
	int num[3];
	pthread_t tid[3];

	
	if (argc != 4){
		fprintf(stderr,"Ejecute asi: a.out <numero1> <numero2> <limite>\n");
		return -1;
	}
    
	lim=atoi(argv[3]);
	num[0]=atoi(argv[1]);
	num[1]=atoi(argv[2]);
	num[2]=num[0]*num[1];
	
	/*
	for(i=0; i < 3; i++){ 
		sum[i]=sumkn(num[i]);
	
	}*/

	printf("________________________________________________________\n\n");
	for(i=0; i < 3; i++){ 	
		pthread_create(&tid[i], NULL, sumkn, (void*)&num[i]);
	}

	for(i=0; i < 3; i++){
		pthread_join(tid[i], (void**) &sum[i]);
		
	}
	suma=*sum[0]+*sum[1]-*sum[2];
	
	//printf("Hilo 1:%d \nHilo 2:%d \nHilo 3:%d \n",*sum[0], *sum[1], *sum[2] );
	printf("\nLa suma de los multiplos de %d y los multiplos de %d  (menores que %d) es: %d \n", num[0], num[1], lim, suma);
	printf("________________________________________________________\n\n");
}