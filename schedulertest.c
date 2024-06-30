#include "types.h"
#include "stat.h"
#include "user.h"

#define NUM_RUNS 20
#define NUM_PROCESSES 50
#define WORK_ITERATIONS 1000000

void busy_work(int size) {
    int i;
    volatile int x = 0;
    for (i = 0; i < size; i++) {
        x = x + i;
    }
}

void create_processes(int num_processes, int same_size) {
    int pid;
    int i;
    for (i = 0; i < num_processes; i++) {
        pid = fork();
        if (pid < 0) {
            printf(1, "fork failed. i: %d\n", i);
            break;
        }
        if (pid == 0) {
            if(same_size == 1)
                busy_work(WORK_ITERATIONS);
            else
                busy_work(WORK_ITERATIONS * i);
            exit(); 
        }
    }
    for (i = 0; i < num_processes; i++) {
        wait();
    }
}

int main(void) 
{
    printf(1, "scheduler test started\n");
    int total_cs = 0;
    int total_time = 0;
    for (int i = 0; i < NUM_RUNS; i++)
    {
        int start_cs = getcontextswitches();
        int start_time = uptime();
        create_processes(NUM_PROCESSES, 1);
        total_cs += getcontextswitches() - start_cs;
        total_time += uptime() - start_time;
    }
    double average_cs = (double) total_cs / NUM_RUNS;
    double average_time = (double) total_time / NUM_RUNS;
    printf(1, "same size result:\n");
    printf(1, "average context switches: %d.%d\n", (int) average_cs, ((int) (average_cs * 1000 ) % 1000));
    printf(1, "average execution time: %d.%d\n", (int) average_time, ((int) (average_time * 1000 ) % 1000));
    for (int i = 0; i < NUM_RUNS; i++)
    {
        int start_cs = getcontextswitches();
        int start_time = uptime();
        create_processes(NUM_PROCESSES, 0);
        total_cs += getcontextswitches() - start_cs;
        total_time += uptime() - start_time;
    }
    printf(1, "different size result:\n");
    printf(1, "average context switches: %d.%d\n", (int) average_cs, ((int) (average_cs * 1000 ) % 1000));
    printf(1, "average execution time: %d.%d\n", (int) average_time, ((int) (average_time * 1000 ) % 1000));
    printf(1, "scheduler test ends\n");
    exit();
} 