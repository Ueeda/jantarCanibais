#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <bool.h>
#include <unistd.h>

////////////////////////////// Variáveis Globais

int caldeirao = 0;
int iniciaThread;
pthread_t selvagens[30];
pthread_t cozinheiro;
pthread_mutex_t mutex1 = pthread_mutex_init (&mutex1, NULL );;

////////////////////////////// Structs

////////////////////////////// Métodos

void adicionarCaldeirao();
void consumirCaldeirao();

////////////////////////////// Criação da Thread

// iret1 = pthread_create( &thread(i), NULL, comer, (void*)  i);

int pthread_create(pthread_t *thread, //identificador)
	pthread_attr_t *attr, //mudar estado da thread)
	void *(*start_routine)(void *), //funcao que ira rodar na thread)
	void *arg); //argumento para a funcao)

////////////////////////////// Juntar as informações das threads
int pthread_join(pthread_t th, //ID da thread)
	void **thread_return); //recebe o valor retornado na thread extra)



int main()
{
    for(int i =0; i<30; i++){
        iniciaThread = pthread_create( &consumidor[i], NULL, consumirCaldeirao, (void*)  i);
    }

    iniciaThread = pthread_create( &cozinheiro, NULL, adicionarCaldeirao, (void*) cozinheiro);

    printf("Hello Word");
    return 0;
}

void *adicionarCaldeirao(void*ptr){
    caldeirao = 12;
    sleep(7000);
}

void *consumirCaldeirao(void*ptr){
    if(caldeirao > 0){
        pthread_mutex_lock(&mutex1);
        caldeirao--;
        pthread_mutex_unlock(&mutex1);
    }
    else{

    }
}
