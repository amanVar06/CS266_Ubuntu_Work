#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <semaphore.h>

typedef int buffer_item;
#define BUFFER_SIZE 3

int in = 0, out = 0;
sem_t empty, full;
buffer_item buffer[BUFFER_SIZE];
pthread_mutex_t mutex;

void *producer(void *producerNumber);
void *consumer(void *consumerNumber);

int main()
{
    printf("\nALL THREADS RUNNING IN PARALLEL\n");
    printf("WE ARE STORING HERE INTEGER VALUES FROM 101 TO 999 IN BUFFER ARRAY HAVING BUFFER SIZE = %d\n",BUFFER_SIZE);
    printf("WHICH IS NOTHING BUT THE VALUE PRODUCED BY THE PRODUCER LATER THIS VALUE WILL BE\n");
    printf("CONSUMED BY THE CONSUMER.\n\n");
    
    pthread_t prod[BUFFER_SIZE], cons[BUFFER_SIZE];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    buffer_item prodAndCons[BUFFER_SIZE];
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        prodAndCons[i] = i+1;
    }
    

    for (int i = 0; i < BUFFER_SIZE; i++)
        pthread_create(&prod[i], NULL, (void *)producer, (void *)&prodAndCons[i]);

    for (int i = 0; i < BUFFER_SIZE; i++)
        pthread_create(&cons[i], NULL, (void *)consumer, (void *)&prodAndCons[i]);

    for (int i = 0; i < BUFFER_SIZE; i++)
        pthread_join(prod[i], NULL);

    for (int i = 0; i < BUFFER_SIZE; i++)
        pthread_join(cons[i], NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&full);

    return 0;
}

void *producer(void *producerNumber)
{
    buffer_item item;
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        item = (rand() % 899) + 101;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        printf("Buffer Index: %d, Produced  item: %d and Producer Number: %d\n", in, item, *((int *)producerNumber));
        in = (in + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *consumerNumber)
{
    buffer_item item;
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        item = buffer[out];
        printf("\nBuffer Index: %d, Removed/Consumed item: %d and Consumer Number: %d\n", out, item, *((int *)consumerNumber));
        out = (out + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
}