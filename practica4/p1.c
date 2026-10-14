#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char *argv[]){
    int n;
    printf("Ingrese la profundidad del árbol: ");
    scanf("%d", &n);
    printf("UID\tPID\tPPID\tTTY\t\tCOMMAND\n");
    while(n--){
        if(fork() && fork()){
            break;
        }
    }
    printf("%d\t%d\t%d\t%s\t%s\n", getuid(), getpid(), getppid(), ttyname(STDIN_FILENO), argv[0]);
    sleep(100);
    return 0;
}