#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>

////////////////////////////// Variáveis Globais

int caldeirao = 12;
int iniciaThread;
pthread_t selvagens[30];
pthread_t cozinheiro;
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t selvagens_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t cozinheiro_cond = PTHREAD_COND_INITIALIZER;

////////////////////////////// Structs

struct structCanibal{
    int qntComeu;
};

struct structCozinheiro{
    int qtdCozinhou;
};

////////////////////////////// Métodos

void *metodoSelvagem(void *ptr);
void *adicionarCaldeirao(void *ptr);
void comer();
void servir();

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
    for(int i =0; i<30; i++){
        iniciaThread = pthread_create( &selvagens[i], NULL, (void*)&metodoSelvagem, (void*)i);
    }

    iniciaThread = pthread_create( &cozinheiro, NULL, (void*)&adicionarCaldeirao, (void*)cozinheiro);

    for(int i =0; i<30; i++){
        pthread_join(selvagens[i], NULL);
    }

    pthread_join(cozinheiro, NULL);

    return 0;
}

void *adicionarCaldeirao(void *ptr){
    while(true){
        pthread_mutex_lock(&mutex1);
        printf("Fazendo");
        caldeirao = 12;
        //sleep(7);
        pthread_cond_wait(&cozinheiro_cond, &mutex1);
        pthread_cond_broadcast(&selvagens_cond);
        pthread_mutex_unlock(&mutex1);
    }
}

void *metodoSelvagem(void *ptr){
    while(true){
        servir();

        comer();
    }
}

void servir(){
    pthread_mutex_lock(&mutex1);
    printf("%d ", caldeirao);
    if(caldeirao > 0){
        caldeirao--;
    }
    else{
        pthread_cond_wait(&selvagens_cond, &mutex1);
        pthread_cond_signal(&cozinheiro_cond);
    }
    pthread_mutex_unlock(&mutex1);
}

void comer(){
    printf("comendo");
    int dormir = rand() % 3;
    sleep(dormir + 1);
}

