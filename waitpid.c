#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[])
{
	int pid;
    int status = 12;

    set_priority(5);
    pid = fork();
    debug();

    if(pid){
        int tempPid = waitpid(pid, &status, 0);
//        printf(1, "\n parent pid: %d \t child pid: %d \t status: %d", getpid(), tempPid, status);
        printf(1,"\n\n   This is the parent process. ");
        printf(1, "\n         Terminated Child ID: %d \t End Status: %d", tempPid, status);

        //debug();
        exit(3);
    }else{
        printf(1,"\n\n   This is the child. ");
//        printf(1, "\n child pid: %d \t status: %d", getpid(), status);
        printf(1, "\n        End Status: %d", status);

        //debug();
        exit(3);
    }

}