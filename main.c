#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

////////////////////////////// Variáveis Globais

int caldeirao = 0;
int iniciaThread;
pthread_t selvagens[30];
pthread_t cozinheiro;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

////////////////////////////// Structs

struct structCanibal{
    int qntComeu;
};

struct structCozinheiro{
    int qtdCozinhou;
};

////////////////////////////// Métodos

void *adicionarCaldeirao(void *ptr);
void comer();
void *servir(void *ptr);

////////////////////////////// Criação da Thread

int pthread_create(pthread_t *thread, //identificador)
    const pthread_attr_t *attr, //mudar estado da thread)
	void *(*start_routine)(void *), //funcao que ira rodar na thread)
	void *arg); //argumento para a funcao)

////////////////////////////// Juntar as informações das threads
int pthread_join(pthread_t th, //ID da thread)
	void **thread_return); //recebe o valor retornado na thread extra)



int main()
{
    int cont = 0;
    for(int i =0; i<30; i++){
        iniciaThread = pthread_create( &selvagens[i], NULL, (void*)&servir, (void*)i);
    }

    iniciaThread = pthread_create( &cozinheiro, NULL, (void*)&adicionarCaldeirao, (void*)cozinheiro);
    cont++;
    return 0;
}

void *adicionarCaldeirao(void *ptr){
    pthread_mutex_lock(&mutex1);
    caldeirao = 12;
    sleep(7000);
    pthread_mutex_unlock(&mutex1);
}

void *servir(void *ptr){
    printf("comendo ");
    if(caldeirao > 0){
        pthread_mutex_lock(&mutex1);
        caldeirao--;
        pthread_mutex_unlock(&mutex1);
        comer();
    }
    else{
        *adicionarCaldeirao(&cozinheiro);
    }
}

void comer(){
    int dormir = rand() % 3;
    sleep(dormir + 1);
}

