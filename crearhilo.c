#include <pthread.h>
#include <stdio.h>

void * imprime_x (void* unused){
	while(1) fputc ('x', stderr);
	return NULL;
}

int main (){
	pthread_t id_hilo;
	//Crea un nuevo hilo sobre la funcion imprime_x
	pthread_create (&id_hilo, NULL, &imprime_x, NULL);
	//Imprime 'o' en la salida de error stderr
	while(1) fputc ('o', stderr);
	return 0;
}


