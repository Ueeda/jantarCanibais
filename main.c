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

/* VER SE ROLA ASSIM
pthread_t struct structCanibal{
    int qntComeu;
};
*/

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
//void servir();
void *servir(void *ptr);
////////////////////////////// Criação da Thread

int pthread_create(pthread_t *thread, //identificador)
    const pthread_attr_t *attr, //mudar estado da thread)
	void *(*start_routine)(void *), //funcao que ira rodar na thread)
	void *arg); //argumento para a funcao)

////////////////////////////// Juntar as informações das threads
int pthread_join(pthread_t th, //ID da thread)
	void **thread_return); //recebe o valor retornado na thread extra)


int pthread_cond_init(pthread_cond_t *restrict cond, const pthread_condattr_t *restrict attr);
int pthread_cond_destroy(pthread_cond_t *cond);
int pthread_cond_wait(pthread_cond_t *restrict cond, pthread_mutex_t *restrict mutex);
int pthread_cond_signal(pthread_cond_t *cond);
int pthread_cond_broadcast(pthread_cond_t *cond);

void  main()
{

    for(int i =0; i<30; i++){
        iniciaThread = pthread_create( &selvagens[i], NULL, (void*)&servir, (void*)i);
    }

    iniciaThread = pthread_create( &cozinheiro, NULL, (void*)&adicionarCaldeirao, "Cozinheiro");

    for(int i =0; i<30; i++){
        pthread_join(selvagens[i], NULL);
    }

    pthread_join(cozinheiro, NULL);

   // exit(EXIT_SUCCESS);
}

void *adicionarCaldeirao(void *ptr){
    while(true){
        pthread_mutex_lock(&mutex1);
        printf("Cozinhando");
        caldeirao = 12;
        sleep(7);

        pthread_cond_wait(&cozinheiro_cond, &mutex1);
        pthread_cond_broadcast(&selvagens_cond);
        pthread_mutex_unlock(&mutex1);
    }
}
/*
void *metodoSelvagem(void *ptr){
    while(true){
        servir();
    }
}
*/
void *servir(void *ptr){
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
    comer();
}

void comer(){
    printf("comendo");
    int dormir = rand() % 3;
    sleep(dormir + 1);
}

