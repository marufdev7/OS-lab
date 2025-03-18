#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 2  
#define MAX_ACTIONS 1  

sem_t chopstick[N]; 

void *philosopher(void *arg)
{
    int id = *(int *)arg;

    for (int i = 0; i < MAX_ACTIONS; i++)  
    {
        printf("Philosopher %d is thinking\n", id);
        sleep(1); 

        sem_wait(&chopstick[id]);
        printf("Philosopher %d picked up left chopstick\n", id);
        sem_wait(&chopstick[(id + 1) % N]);
        printf("Philosopher %d picked up right chopstick and is eating\n", id);

        sleep(1); 

        sem_post(&chopstick[(id + 1) % N]);
        sem_post(&chopstick[id]);
        printf("Philosopher %d put down chopsticks and is thinking again\n", id);
    }
    return NULL;
}

int main()
{
    pthread_t p[N];
    int id[N];

    for (int i = 0; i < N; i++)
    {
        sem_init(&chopstick[i], 0, 1);
    }

    for (int i = 0; i < N; i++)
    {
        id[i] = i;
        pthread_create(&p[i], NULL, philosopher, &id[i]);
    }

    for (int i = 0; i < N; i++)
    {
        pthread_join(p[i], NULL);
    }

    for (int i = 0; i < N; i++)
    {
        sem_destroy(&chopstick[i]);
    }

    return 0;
}

/*
Philosopher 0 is thinking
Philosopher 1 is thinking
Philosopher 0 picked up left chopstick
Philosopher 0 picked up right chopstick and is eating
Philosopher 0 put down chopsticks and is thinking again
Philosopher 1 picked up left chopstick
Philosopher 1 picked up right chopstick and is eating
Philosopher 1 put down chopsticks and is thinking again
*/
