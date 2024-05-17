#include "types.h"
#include "stat.h"
#include "user.h"
#include "process_info_t.h"

int main(void) 
{
    struct process_info_t *my_struct;
    my_struct = malloc(sizeof(my_struct));
    
    printf(0, "--- start pptable ---\n");
    ps(1, 12, my_struct);
    printf(0, "--- end pptable ---\n");
    printf(1, "my_struct->pid: %d\n", my_struct->pid);
    exit();
} 