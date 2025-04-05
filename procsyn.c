#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "time.h"

#include "utils.h"
#include "buffer.h"

#ifdef __linux__
#include "pthread.h"
#include "unistd.h"
#define TMLEN linux_tmlen

#elif _WIN32
#include "windows.h"
#define sleep(A) Sleep(A)
#define TMLEN win_tmlen
#endif

// producer 
void *producer(){
    buffer_item item;

    while (true){
        srand((unsigned int)time(NULL));

        sleep((rand() % 10 + 1) * TMLEN);

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

        sleep((rand() % 10 + 1) * TMLEN);

        if(remove_item(&item))
            perror("consumer report error condition");
        else
            printf("consumer_consumed %d at timestamp %ld\n", item, time(NULL));
    }
}

int main(int argc, char **argv){
    if(argc != 4){
        perror("Param Num Error!");
        printf("[usage]: %s <sleep time> <producer nums> <consumer nums>", argv[0]);
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

    close_sems();

#elif _WIN32

// create procducer procs
for(int i = 0; i < pnums; ++i)
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)producer, NULL, 0, NULL);

// create comsumer
for(int i = 0; i < cnums; ++i)
    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)consumer, NULL, 0, NULL);

sleep(stime * TMLEN);

close_sems();

#endif

    return 0;
}
