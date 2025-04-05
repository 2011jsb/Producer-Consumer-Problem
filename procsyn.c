#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "time.h"

#ifdef __linux__
#include "pthread.h"
#include "semaphore.h"
#include "unistd.h"
#elif _WIN32
#include "windows.h"
#endif

#include "buffer.h"
#include "utils.h"

// producer 
void *producer(){
    buffer_item item;

    while (true){
        srand((unsigned int)time(NULL));

        sleep(rand() % 10 + 1);

        item = rand();
        
        if(insert_item(item))
            perror("producer report error condition");
        else
            printf("producer_produced %d at timestamp %ld\n", item, time(NULL));
    }
}

// consumer
void *consumer(){
    buffer_item item;


    while (true){
        srand((unsigned int)time(NULL) * 1000);

        sleep(rand() % 10 + 1);

        if(remove_item(&item))
            perror("consumer report error condition");
        else
            printf("consumer_consumed %d at timestamp %ld\n", item, time(NULL));
    }
}

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
    buffer_init();

#ifdef __linux__

    // create procducer procs
    for(int i = 0; i < pnums; ++i){
        pthread_t tmp;
        pthread_create(&tmp, NULL, producer, NULL);
        pthread_detach(tmp);
    }

    // create comsumer
    for(int i = 0; i < cnums; ++i){
        pthread_t tmp;
        pthread_create(&tmp, NULL, consumer, NULL);
        pthread_detach(tmp);
    }

    sleep(stime);

#elif _WIN32

#endif

    return 0;
}
