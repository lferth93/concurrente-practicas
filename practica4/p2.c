#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    for(int i = 0; i < 7; i++){
        if(4 <= i){
            if(fork()){
                fork() || (fork() && fork() && fork() && fork());
                break;
            }
        }else{
            if(fork()){
                break;
            }
        }
    }
    sleep(100);
    return 0;
}