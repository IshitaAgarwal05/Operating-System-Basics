#include <stdio.h>
#include <pthread.h>

#define ARRAY_SIZE 5000
#define THREAD_COUNT 100

int array[ARRAY_SIZE] = {0}; 
long long sum = 0; // Global sum variable

void *sum_array(void *arg) {
    int start_index = *((int *)arg);
    long long local_sum = 0;
    
    for (int i = start_index; i < start_index + ARRAY_SIZE / THREAD_COUNT; i++) 
    {local_sum += array[i];}
    
    sum += local_sum;
    return NULL;
}

int main() {
    pthread_t threads[THREAD_COUNT];
    int indexes[THREAD_COUNT];
    for (int i = 0; i < ARRAY_SIZE; i++) {array[i] = i + 1;}
    
    for (int i = 0; i < THREAD_COUNT; i++) {
        indexes[i] = i * (ARRAY_SIZE / THREAD_COUNT);
        pthread_create(&threads[i], NULL, sum_array, &indexes[i]);
    }
    
    for (int i = 0; i < THREAD_COUNT; i++) {pthread_join(threads[i], NULL);}   
    printf("Sum: %lld\n", sum);
    return 0;
}
