#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define N 5
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + 4) % N
#define RIGHT (phnum + 1) % N

int flag[N] = {0};

int state[N] = { 2, 2, 2, 2, 2 };
int phil[N] = { 0, 1, 2, 3, 4 };
int j=0;
char status[][10] = {"EATING", "HUNGRY", "THINKING"};

sem_t mutex;
sem_t S[N];

void showStatus()
{

        printf("\n");
        for(int k=0; k<5; k++)
        {
            if(flag[k]!=0)
                printf("Philosopher %d is %s \t", k+1, status[state[k]]);
        }
        printf("\n");
        sleep(3);
}


void test(int phnum)
{
    if (state[phnum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        // state that eating
        state[phnum] = EATING;

        sleep(2);

        printf("\nPhilosopher %d takes fork %d and %d\n", phnum + 1, LEFT + 1, phnum + 1);

        //showStatus();

        printf("Philosopher %d is Eating\n", phnum + 1);

        sleep(2);

        // sem_post(&S[phnum]) has no effect during take_fork
        // used to wake up hungry philosophers during put_fork
        sem_post(&S[phnum]);
    }
}

// take up chopsticks
void take_fork(int phnum)
{

    sem_wait(&mutex);

    // state that hungry
    state[phnum] = HUNGRY;

    //showStatus();
    printf("Philosopher %d is Hungry\n", phnum + 1);

    // eat if neighbours are not eating
    test(phnum);

    sem_post(&mutex);

    // if unable to eat wait to be signalled
    sem_wait(&S[phnum]);

    sleep(1);
}

// put down chopsticks
void put_fork(int phnum)
{

    sem_wait(&mutex);

    // state that thinking
    state[phnum] = THINKING;

    printf("\nPhilosopher %d putting fork %d and %d down\n", phnum + 1, LEFT + 1, phnum + 1);

    //showStatus();
    printf("Philosopher %d is thinking\n", phnum + 1);

    test(LEFT);
    test(RIGHT);

    sem_post(&mutex);
}

void* philospher(void* num)
{

    while (j<1) {

        int* i = num;

        sleep(1);

        take_fork(*i);

        sleep(0);

        put_fork(*i);

        printf("\n\n");
        j++;
    }
}



int main()
{

    int i;
    pthread_t thread_id[N], showStatus_id;

    // initialize the semaphores
    sem_init(&mutex, 0, 1);

    for (i = 0; i < N; i++)

        sem_init(&S[i], 0, 0);

    for (i = 0; i < N; i++) {

        // create philosopher processes
        flag[i] = 1;
        pthread_create(&thread_id[i], NULL, philospher, &phil[i]);

        printf("\nPhilosopher %d is thinking\n", i + 1);
    }

    //pthread_create(&showStatus_id, NULL, showStatus, NULL);


    for (i = 0; i < N; i++)

        pthread_join(thread_id[i], NULL);

}
