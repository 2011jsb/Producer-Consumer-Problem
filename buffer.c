#include "stdio.h"

#include "buffer.h"

/*- buffer structure-*/
#ifdef __linux__
#include "pthread.h"
#include "semaphore.h"

sem_t empty, full;// signal values
pthread_mutex_t mutex;// mutex lock

#elif _WIN32

#include "windows.h"

int index;// head index
HANDLE empty, full;// signal values
HANDLE mutex;// mutex lock

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
    eflag = !pthread_mutex_lock(&mutex) ? eflag: -1;

    int index;
    eflag = !sem_getvalue(&full, &index) ? eflag: -1;
    buffer[index] = item;

    eflag = !pthread_mutex_unlock(&mutex) ? eflag: -1;
    sem_post(&full);

    return eflag;
}

int remove_item(buffer_item *item){
    int eflag = 0;
    sem_wait(&full);
    eflag = !pthread_mutex_lock(&mutex) ? eflag: -1;

    int index;
    eflag = !sem_getvalue(&full, &index) ? eflag: -1;
    *item = buffer[index];

    eflag = !pthread_mutex_unlock(&mutex) ? eflag: -1;
    sem_post(&empty);

    return eflag;
}

void close_sems(){
    sem_close(&empty);
    sem_close(&full);
}
#elif _WIN32

void buffer_init(){
    empty = CreateSemaphore(NULL, BUFFER_SIZE, BUFFER_SIZE, NULL);
    full = CreateSemaphore(NULL, 0, BUFFER_SIZE, NULL);
    mutex = CreateMutex(NULL, FALSE, NULL);
    index = 0;
}

int insert_item(buffer_item item){
    int eflag = 0;
    eflag = !WaitForSingleObject(empty, INFINITE) ? eflag: -1;
    eflag = !WaitForSingleObject(mutex, INFINITE) ? eflag: -1;

    buffer[index] = item;
    ++index;

    eflag = ReleaseSemaphore(empty, -1, NULL)? eflag: -1;
    eflag = ReleaseSemaphore(full, 1, NULL) ? eflag: -1;

    eflag = ReleaseMutex(mutex) ? eflag: -1;
    
    return 0;
}

int remove_item(buffer_item *item){
    int eflag = 0;
    eflag = !WaitForSingleObject(full, INFINITE) ? eflag: -1;
    eflag = !WaitForSingleObject(mutex, INFINITE) ? eflag: -1;

    *item = buffer[index - 1];
    --index;

    eflag = ReleaseSemaphore(full, -1, NULL)? eflag: -1;
    eflag = ReleaseSemaphore(empty, 1, NULL) ? eflag: -1;

    eflag = ReleaseMutex(mutex) ? eflag: -1;
    
    return 0;
}

void close_sems(){
    CloseHandle(empty);
    CloseHandle(full);
    CloseHandle(mutex);
}

#endif
