#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* calcular_primo(void* arg){
	int candidato = 1;
	int n = *((int*)arg);
	int factor;
	int es_primo;

	while(1){
		es_primo = 1;
		for (factor = 2; factor < candidato; ++ factor){
			if(candidato % factor == 0){
				es_primo = 0;
				break;
			}
		}
		if(es_primo){
			if(--n == 0) return (void*)candidato;
		}
		++candidato;	
	}
	return NULL;
}

int main(int argc, char* argv[]){
	pthread_t id_hilo;
	int cual_primo;
	int primo = 0;
	struct timeval ti, tf;
	double tiempo;
	
	if(argc!=2){
		printf("ingrese el valor N-esimo primo como parametro. Ejemplo: ./a.out 4\n");
		exit(0);
	}
	cual_primo = atoi(argv[1]);

	pthread_create(&id_hilo, NULL, &calcular_primo, &cual_primo);
	gettimeofday(&ti,NULL);
	pthread_join(id_hilo, (void*)&primo);
	gettimeofday(&tf,NULL);
	printf("El número primo es %d \n", primo);
	tiempo= (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;
	printf("Tiempo total: %g milisegundos\n", tiempo);
	return 0;
}
