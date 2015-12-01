#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#define MAXCHARS 255

typedef struct calcula_t{
	int *numArray;
	int desde;
	int hasta;
} calcula_t;

//Cuenta los numeros en un archivo que esten separados por espacios
int contarNums(FILE* in_file);
void leerNums(FILE* in_file, int *numArray);
void* sumarNums(void* datosEntrada);

int main(int argc, char const *argv[]){
	int tamVector = 0;
	FILE *in_file = NULL;
	int *numArray;
	int sumTotal = 0, sumParcial;
	calcula_t datos1;
	calcula_t datos2;
	pthread_t hilo_id1;
	pthread_t hilo_id2;

	if (argc != 2){
		fprintf(stderr,"uso: %s <numeros.txt>\n",argv[0]);
		fprintf(stderr, "ejemplo:\n%s nums.txt\n",argv[0] );
		exit(-1);
	}

	in_file = fopen(argv[1], "r");
	if(in_file == NULL){
		printf("cannot open %s\n",argv[1] );
		exit(8);
	}
	
	tamVector = contarNums(in_file);
	//printf("%d\n", contado);

	numArray = malloc(sizeof(int)*tamVector);

	leerNums(in_file,numArray);

	datos1.numArray = numArray;
	datos1.desde = 0;
	datos1.hasta = tamVector/2;

	datos2.numArray = numArray;
	datos2.desde = tamVector/2;
	datos2.hasta = tamVector;


	pthread_create(&hilo_id1, NULL, &sumarNums, &datos1);
	pthread_create(&hilo_id2, NULL, &sumarNums, &datos2);


	pthread_join(hilo_id1, (void*)&sumParcial);
	sumTotal = sumParcial;
	pthread_join(hilo_id2, (void*)&sumParcial);
	sumTotal += sumParcial;

	//sumTotal = sumarNums(datos1);

	printf("El total de la suma de los elementos es: %d\n", sumTotal );


	return 0;
}

void* sumarNums(void* datosEntrada){
	int i;
	int sumParcial = 0;
	calcula_t *datos = (calcula_t*)datosEntrada;
	for(i = datos->desde; i < datos->hasta; i++){
		sumParcial = sumParcial + *(datos->numArray+i);
	}
	return sumParcial;
}

void leerNums(FILE* in_file, int *numArray){
	char inBuf[MAXCHARS];
	int i = 0;
	char *resto;
	char *token;

	while(fgets(inBuf,MAXCHARS,in_file)){
		token = strtok_r(inBuf, " ", &resto);
		*(numArray+i) = atoi(token);
		i++;
		while((token = strtok_r(NULL, " ", &resto))){
			*(numArray+i) = atoi(token);
			i++;
		}
	}
	//rewind(in_file);
	return;
}

int contarNums(FILE* in_file){
	char inBuf[MAXCHARS];
	int cantNumeros = 0;
	char *resto;
	char *token;
	while(fgets(inBuf,MAXCHARS,in_file)){
		token = strtok_r(inBuf, " ", &resto);
		cantNumeros++;
		while((token = strtok_r(NULL, " ", &resto))){
			cantNumeros++;
		}
	}
	rewind(in_file);
	return cantNumeros;
}