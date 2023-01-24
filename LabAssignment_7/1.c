#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <threads.h>
#include<semaphore.h>

typedef int buffer_item;
#define BUFFER_SIZE 10


pthread_mutex_t mutex;
sem_t empty,full;
buffer_item buffer[BUFFER_SIZE];
int in = 0;
int out = 0;



void *producer(void *param)
{
    //pthread_mutex_lock(&mutex);
    buffer_item item;
    // while (1)
    // {
    //     /* sleep for a random period of time */
    //     sleep(10);
    //     /* generate a random number */
    //     item = rand();
    //     if (insertItem(item))
    //         printf("report error condition");
    //     else
    //         printf("producer produced %d\n", item);
    // }

    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        item = rand();
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        printf("Producer %d produced an item %d in buffer %d\n",*((int *)param),buffer[in],in);
        in = (in+1)%5;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    
    //pthread_mutex_unlock(&mutex);
}

void *consumer(void *param)
{
    //pthread_mutex_lock(&mutex);
    buffer_item item;
    // while (1)
    // {
    //     /* sleep for a random period of time */
    //     sleep(10);
    //     if (removeItem(&item))
    //         printf("report error condition");
    //     else
    //         printf("consumer consumed %d\n", item);
    // }
    // pthread_mutex_unlock(&mutex);

    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = buffer[out];
        printf("Consumer %d consumed an item %d from buffer %d\n",*((int *)param),item,out);
        out = (out+1)%5;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
    
}

// int insertItem(buffer_item item)
// {
//     int index = (rand() % 10);
//     buffer[index] = item;

//     return 0;
// }

// int removeItem(buffer_item *item)
// {
//     int index = rand() % 10;
//     item[index] = 0;

//     return 0;
// }

int main(int argc, char const *argv[])
{
    pthread_t prod[5],cons[5];
    pthread_mutex_init(&mutex,NULL);
    sem_init(&empty,0,5);
    sem_init(&full,0,0);


    int prodAndCons[5] = {1,2,3,4,5};

    for(int i=0;i<5;i++)
    pthread_create(&prod[i],NULL,(void *)producer,(void *)&prodAndCons[i]);

    for(int i=0;i<5;i++)
    pthread_create(&cons[i],NULL,(void *)consumer,(void *)&prodAndCons[i]);

    for(int i=0;i<5;i++)
    pthread_join(prod[i],NULL);

    for(int i=0;i<5;i++)
    pthread_join(cons[i],NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&full);


    // pthread_t p, c;
    // buffer_item *buffer = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    // pthread_mutex_init(&mutex,NULL);

    // if (pthread_create(&p, NULL, &producer, NULL) != 0) {
    //     return 3;
    // }
    // if (pthread_create(&c, NULL, &consumer, NULL) != 0) {
    //     return 4;
    // }
    // if (pthread_join(p, NULL) != 0) {
    //     return 5;
    // }
    // if (pthread_join(c, NULL) != 0) {
    //     return 6;
    // }


    // if (pthread_create(&c, NULL, &removeItem, NULL) == 0)
    // {

    //     return 0;
    // }
    pthread_mutex_destroy(&mutex);
    return 0;

    /* 1. Get command line arguments argv[1],argv[2],argv[3] */
    /* 2. Initialize buffer */
    /* 3. Create producer thread(s) */
    /* 4. Create consumer thread(s) */
    /* 5. Sleep */
    /* 6. Exit */
}
