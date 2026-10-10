#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int args, char **argv){
    while(fork() || (fork() && !fork())){
        if(!fork()){
                fork();
        }
        break;
    }
    sleep(100000);

    return 0;
}