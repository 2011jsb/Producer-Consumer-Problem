#include "stdio.h"

#include "buffer.h"

/*- buffer structure-*/
#ifdef __linux__
#include "pthread.h"
#include "semaphore.h"

sem_t empty, full;// signal values
pthread_mutex_t mutex;// mutex lock

#elif _WIN32

#endif
buffer_item buffer[BUFFER_SIZE];// the buffer
/*- buffer structure-*/

#ifdef __linux__
void buffer_init(){
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex,NULL);
}

int insert_item(buffer_item item){
    int eflag = 0;
    sem_wait(&empty);
    eflag = !pthread_mutex_lock(&mutex) ? 0: -1;

    int index;
    eflag = !sem_getvalue(&full, &index) ? 0: -1;
    buffer[index] = item;

    eflag = !pthread_mutex_unlock(&mutex) ? 0: -1;
    sem_post(&full);

    return eflag;
}

int remove_item(buffer_item *item){
    int eflag = 0;
    sem_wait(&full);
    eflag = !pthread_mutex_lock(&mutex) ? 0: -1;

    int index;
    eflag = !sem_getvalue(&full, &index) ? 0: -1;
    *item = buffer[index];

    eflag = !pthread_mutex_unlock(&mutex) ? 0: -1;
    sem_post(&empty);

    return eflag;
}
#elif _WIN32

#endif
