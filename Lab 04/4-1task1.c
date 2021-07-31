#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void * func(void * num)
{
    pthread_detach(pthread_self());
    int* n1 = (int*) num;
    printf("Inside thread, %d\n",*n1);

    printf("\nPrime numbers:\n");
    for(int i=2; i<=*n1; i++)
    {
        int c=0;
        for(int j=1; j<=i; j++)
        {
            if(i%j==0)
            {
                c++;
            }
        }

        if(c==2)
        {
            printf("%d\n",i);
        }
    }
    pthread_exit(NULL);

}

void fun()
{
    int n;
    printf("input\n");
    scanf("%d", &n);

    void *ptr = &n;

    pthread_t ptid;

    // Creating a new thread
    pthread_create(&ptid, NULL, func, ptr);
    /*  printf("This line may be printed before thread terminates\n");

      // The following line terminates the thread manually
      pthread_cancel(ptid);
    // Compare the two threads created
      if(pthread_equal(ptid, pthread_self()))
          printf("Threads are equal\n");
      else
          printf("Threads are not equal\n");
      pthread_join(ptid, NULL);*/

    printf("This line will be printed after thread ends\n");

    pthread_exit(NULL);
}

int main()
{
    fun();
    return 0;
}
