#include <stdio.h>
#include <pthread.h>

void* printNTimes(void* arg) {
    char* name = (char*)arg;
    for (int i = 0; i < 5; ++i) {
        printf("%s\n", name);
        for (int j = 0; j < 1000000; ++j) {
            // delay
        }
    } return NULL;
}

int main() {
    pthread_t threads[5];
    char* names[] = {"Thread 1", "Thread 2", "Thread 3", "Thread 4", "Thread 5"};
    for (int i = 0; i < 5; ++i) {
        pthread_create(&threads[i], NULL, printNTimes, (void*)names[i]);
    }
    // for (int i = 0; i < 5; ++i) {
    //      pthread_join(threads[i], NULL);
    //}
    return 0;
}

// 1)With pthread_join:
// The main thread waits for each child thread to finish executing before proceeding. Ensures all threads complete their tasks before the main program exits.

// 2)Without pthread_join:
// The main thread does not wait for child threads and continues execution immediately.
