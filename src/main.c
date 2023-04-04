/* C Bench (main.c)
 * A single and multi-threaded benchmark made in the C programming language
 * Github:https://www.github.com/awesomelewis2007/c_bench
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>

#define YELLOW "\x1b[33m"
#define GREEN "\x1b[32m"
#define RESET "\x1b[0m"


#include "config.h"

/**
 * get_cores - A function that gets the number of cores on the system
 * 
 * @returns: The number of cores on the system
*/
int get_cores()
{
    return sysconf(_SC_NPROCESSORS_ONLN);
}

/**
 * spinner - A function that prints a spinner to the terminal
 * 
 * @message: The message to print before the spinner
 * 
 * @returns: void
*/
void *spinner(void *message)
{
    const char *animation[] = {"-", "\\", "|", "/"};
    while (1)
    {
        for (int i = 0; i < 4; i++)
        {
            printf("\r%s [%s]", message, animation[i]);
            fflush(stdout);
            usleep(100000);
        }
    }
}
/**
 * singleCoreTest - A function that tests the performance of the CPU
 * 
 * @returns: The time taken to run the test
*/
double singleCoreTest()
{
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    int x = 0;
    for (int i = 0; i < 1000000000; i++)
    {
        x += i;
    }

    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    return (double)(cpu_time_used); 
}

/**
 * dualCoreTest - A function that tests the performance of the CPU
 * 
 * @thread_id: The thread ID
 * 
 * @returns: void
*/
void *dualCoreTest(void *thread_id)
{
    int id = *((int *)thread_id);
    clock_t start, end;
    int x = 0;
    for (int i = id * 500000000; i < (id + 1) * 500000000; i++)
    {
        x += i;
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    if (argc == 2 && (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0))
    {
        printf("C Bench v%s\n", VERSION);
        return 0;
    }
    /* Get the number of threads available and leave two cores for system and the spinner */
    int num_threads = get_cores() - 2;
    pthread_t spinner_thread;
    pthread_create(&spinner_thread, NULL, spinner, (void *)"Benchmarking single-core performance ");
    double singleCoreTime = singleCoreTest();
    pthread_cancel(spinner_thread);
    printf("\x1b[2K");
    printf("\r%sFinished%s: Single-core test time: %f seconds\n", GREEN, RESET, singleCoreTime);

    pthread_t threads[num_threads];
    int thread_args[num_threads];
    int dualCoreTime;
    clock_t start, end;
    double cpu_time_used;

    printf("%sStarting%s: dual-core test with %d threads\n",YELLOW, RESET, num_threads); 
    start = clock();
    pthread_create(&threads[0], NULL, spinner, (void *)"Benchmarking dual-core performance ");
    for (int i = 0; i < num_threads; i++)
    {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, dualCoreTest, (void *)&thread_args[i]);
    }

    for (int i = 0; i < num_threads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    end = clock();
    pthread_cancel(spinner_thread);
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\x1b[2K");
    printf("\x1b[1A");
    printf("\x1b[2K");
    printf("\r%sFinished%s: Dual-core test time: %f seconds\n", GREEN, RESET, cpu_time_used);
    return 0;
}