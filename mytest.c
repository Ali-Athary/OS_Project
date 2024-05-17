#include "types.h"
#include "stat.h"
#include "user.h"
#include "process_info_t.h"

#define N  20

int main(void) 
{
    int n, pid;
    for(n=0; n<N; n++){
        pid = fork();
        if(pid < 0)
        break;
        if(pid == 0)
        exit();
    }

    if (pid != 0){
        struct process_info_t *my_struct;
        my_struct = malloc(sizeof(my_struct));

        ps(4, 2, my_struct);
        printf(1, "my_struct->name: %s\n", my_struct->name);
        printf(1, "my_struct->pid: %d\n", my_struct->pid);
        printf(1, "my_struct->state: %d\n", my_struct->state);
    }
    exit();
} 