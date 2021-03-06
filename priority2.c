#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char **argv)
{
    printf(1, "\n---Process 2--- [PID: %d, Priority Value: %d]\n", getpid(), 5);
    set_priority(5);
    int i, k;
    const int loop = 40000;
    for(i = 0; i < loop; i++){
        asm("nop");
        for(k = 0; k < loop; k++){
            asm("nop");
        }
    }
    exit(0);
}