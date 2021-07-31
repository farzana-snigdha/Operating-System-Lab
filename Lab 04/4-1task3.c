#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <pthread.h>


int matA[100][100], matB[100][100], matC[100][100];
int m, n, k;

struct matPosition
{
    int i;
    int j;
};

void *multiplication (void* Position)
{
   // printf("inside thread\n");
    struct matPosition* pos = (struct matPosition*) Position;

    int i = pos->i;
    int j = pos->j;

    free(pos);

    matC[i][j] = 0;

    for (int x = 0; x < k; x++)
    {
        matC[i][j] = matC[i][j] + (matA[i][x] * matB[x][j]);
    }

    pthread_exit(NULL);
}

void create_Thread()
{
    int c1,r2;
    printf("Matrix A,row & col: ");
    scanf("%d %d", &m, &c1);
    printf("Matrix B,row & col: ");
    scanf("%d %d", &r2, &n);
    if(c1!=r2)
    {
        printf("\ninvalid input\nprocess terminates\n");

    }
    else
    {
        k=c1;
    }

    printf("matrix A:\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < k; j++)
        {
            scanf("%d", &matA[i][j]);
        }
    }

    printf("Enter Matrix B :\n");
    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &matB[i][j]);
        }
    }



    // Creating a new thread
    pthread_t ptid[m*n];

    int index = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            struct matPosition *pos = malloc(sizeof(struct matPosition));
            pos->i = i;
            pos->j = j;

            pthread_create( &ptid[index++], NULL, multiplication, pos );

        }
    }

    // Waiting for the created thread to terminate
    index = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            pthread_join( ptid[index++], NULL );

        }
    }
    printf("\nMatrix C :\n");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", matC[i][j]);
        }
        printf("\n");
    }

    pthread_exit(NULL);

}

// Driver code
int main()
{
    create_Thread();
    return 0;
}
