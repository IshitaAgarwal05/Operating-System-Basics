#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *child_function(void *arg) {
    for (int i = 0; i < 100; ++i) {
        printf("child\n");
	usleep(100);
            }
    return NULL;
}

void parent_function() {
    for (int i = 0; i < 100; ++i) {
        printf("parent\n");
    }
}

int main() {
    pthread_t child_thread;
    pthread_create(&child_thread, NULL, child_function, NULL);
    parent_function();

   // pthread_join(child_thread, NULL);

    return 0;
}


// 1)Without joining child thread: The main thread continued printing "parent" while the child thread prints "child" at the same time or in between. After the main thread finishes, the program might terminated before the child thread completes.

//2)With joining child thread: By calling pthread_join, the main thread waits for the child thread to finish execution before proceeding. This ensures that both "child" and "parent" prints complete before the program terminates.

