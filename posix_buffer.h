#ifndef POSIX_BUFFER_H
#define POSIX_BUFFER_H
#include "pthread.h"
#include "semaphore.h"

#define buffer_item int
#define BUFFER_SIZE 5

/*- buffer structure-*/
sem_t *empty, *full;// signal values
pthread_mutex_t mutex;// mutex lock
buffer_item buffer[BUFFER_SIZE];// the buffer
/*- buffer structure-*/

// insert item into buffer
int insert_item(buffer_item item);

// remove an object from buffer
int remove_item(buffer_item *item);
#endif