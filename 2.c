#include <pthread.h>
#include <stdio.h>

struct parametros_hilo{
	char caracter;
	int contador;
};

void* imprimir_caracter (void* parametros){
	struct parametros_hilo* p = (struct parametros_hilo*) parametros;
	int i;
	for (i=0; i<p->contador; ++i)
		fputc(p->caracter, stderr);
	return NULL;
}

int main(){
	pthread_t id_hilo_1;
	pthread_t id_hilo_2;
	struct parametros_hilo hilo1_param;
	struct parametros_hilo hilo2_param;

	hilo1_param.caracter = 'x';
	hilo1_param.contador = 300;
	pthread_create (&id_hilo_1, NULL,&imprimir_caracter, &hilo1_param);

	hilo2_param.caracter = 'o';
	hilo2_param.contador = 200;
	pthread_create (&id_hilo_2, NULL,&imprimir_caracter, &hilo2_param);

	//pthread_join (id_hilo_1, NULL);
	//pthread_join (id_hilo_2, NULL);
	
	fputc('\n', stderr);
	return 0;
}
