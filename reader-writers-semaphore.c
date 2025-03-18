#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t w;  
pthread_mutex_t m; 
int rc = 0;

void *r(void *arg)
{
    int id = *(int *)arg;
    for (int i = 0; i < 1; i++)
    {
        pthread_mutex_lock(&m);
        rc++;
        if (rc == 1)
            sem_wait(&w);
        pthread_mutex_unlock(&m);

        printf("Reader %d is reading\n", id);
        usleep((rand() % 500000) + 100000); 

        pthread_mutex_lock(&m);
        rc--;
        if (rc == 0)
            sem_post(&w); 
        pthread_mutex_unlock(&m);
    }
    return NULL;
}

void *wr(void *arg)
{
    int id = *(int *)arg;
    for (int i = 0; i < 1; i++)
    {
        sem_wait(&w); 
        printf("Writer %d is writing\n", id);
        usleep((rand() % 500000) + 100000); 
        sem_post(&w);
    }
    return NULL;
}

int main()
{
    int nr = 5, nw = 3;
    pthread_t r_t[nr], w_t[nw];
    int r_ids[nr], w_ids[nw];

    srand(time(NULL));
    sem_init(&w, 0, 1);
    pthread_mutex_init(&m, NULL);

    for (int i = 0; i < nr; i++)
    {
        r_ids[i] = i + 1;
        pthread_create(&r_t[i], NULL, r, &r_ids[i]);
    }
    for (int i = 0; i < nw; i++)
    {
        w_ids[i] = i + 1;
        pthread_create(&w_t[i], NULL, wr, &w_ids[i]);
    }

    for (int i = 0; i < nr; i++)
        pthread_join(r_t[i], NULL);
    for (int i = 0; i < nw; i++)
        pthread_join(w_t[i], NULL);

    sem_destroy(&w);
    pthread_mutex_destroy(&m);
    return 0;
}

/*
Reader 3 is reading
Reader 4 is reading
Reader 1 is reading
Reader 2 is reading
Reader 5 is reading
Writer 2 is writing
Writer 3 is writing
Writer 1 is writing
*/
