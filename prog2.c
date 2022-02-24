#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char **argv)
{
    printf(1, "\nProg 2 [PID: %d, Priority Value: %d]\n", getpid(), 5);
    set_priority(5);
    int i, k;
    for (i = 0; i < 43000; i++)
    {
        asm("nop");
        for (k = 0; k < 43000; k++)
        {
            asm("nop");
        }
    }
    exit(0);
}