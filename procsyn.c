#include "stdlib.h"
#include "stdio.h"
#include "string.h"

#include "buffer.h"
#include "utils.h"

// producer 
void *producer(void *param){
    buffer_item item;

    srand((unsigned int)time(NULL));

    while (true){
        sleep(rand() % 1000 + 1);

        item = rand();
        if(insert_item(item))
            perror("report error condition");
        else
            printf("producer_produced %d \n", item);
    }
}

// consumer
void *consumer(void *param){
    buffer_item item;

    srand((unsigned int)time(NULL));

    while (true){
        sleep(rand() % 1000 + 1);

        if(remove_item(&item))
            perror("report error condition");
        else
            printf("consumer_consumed %d \n", item);
    }
}

#ifdef _WIN32
#include "windows.h"
int main(int argc, char **argv){
    if(argc != 4){
        perror("Param Num Error!");
        exit(EXIT_FAILURE);
    }

    //get params
    int stime = strtol(argv[1], NULL, 10);//sleep time
    int pnums = strtol(argv[2], NULL, 10);//num of procuders
    int cnums = strtol(argv[3], NULL, 10);//num of comsumers

    if(!(stime && pnums && cnums)){
        perror("Param Error!");
        exit(EXIT_FAILURE);
    }

    // initialize buffer structure
    

    sleep(stime);

    return 0;
}
#elif __linux__
#include "pthread.h"
#include "semaphore.h"
#include "unistd.h"
int main(int argc, char **argv){
    if(argc != 4){
        perror("Param Num Error!");
        exit(EXIT_FAILURE);
    }

    //get params
    int stime = strtol(argv[1], NULL, 10);//sleep time
    int pnums = strtol(argv[2], NULL, 10);//num of procuders
    int cnums = strtol(argv[3], NULL, 10);//num of comsumers

    if(!(stime && pnums && cnums)){
        perror("Param Error!");
        exit(EXIT_FAILURE);
    }

    // initialize buffer structure
    sem_init(empty, 0, BUFFER_SIZE);
    sem_init(full, 0, 0);
    pthread_mutex_init(&mutex,NULL);

    for(int i = 0; i < pnums; ++i){
        pthread_t tmp;
        pthread_create(tmp, NULL, producer, NULL);
        pthread_detach(tmp);
    }

    for(int i = 0; i < cnums; ++i){
        pthread_t tmp;
        pthread_create(tmp, NULL, consumer, NULL);
        pthread_detach(tmp);
    }

    sleep(stime);

    return 0;
}
#endif



