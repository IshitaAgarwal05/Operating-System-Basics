#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handle_sigint(int signum){
    printf("Interrupt received. Program continued...\n");
}

int main(){
    signal(SIGINT, handle_sigint);
    while(1){
        printf("Hello World!\n");
        sleep(1);
    } return 0;
}


// SIGTSTP - for Ctrl+Z
