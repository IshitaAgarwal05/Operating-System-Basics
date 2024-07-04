#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define size 50000

struct stack{
    int *buffer;
    int top;
};

void init(struct stack *s){s->top = -1;}

struct stack *create(){
    struct stack *s = (struct stack *)malloc(sizeof(struct stack));
    s->buffer = (int *)malloc(size *sizeof(int));
    init(s);
    return s;
}

int empty(struct stack *s){
    if(s->top == -1){return 1;}
    else{return 0;}
}

int full(struct stack *s){
    if(s->top == size-1){return 1;}
    else{return 0;}
}

void push(struct stack *s, int n){
    if(full(s)){printf("Stack is full\n");}
    else{
        s->top ++;
        s->buffer[s->top] = n;
    }
}

void pop(struct stack *s){
    if(empty(s)){printf("Stack is empty\n");}
    else{s->top--;}
}

void display(struct stack *s){
    printf("Stack Elements: \n");
    for(int i = 0; i <= s->top; i++){
        printf("%d ", s->buffer[i]);
    }
    printf("\n");
}

void *thread_t1(void *arg){
    struct stack *stack1 = (struct stack *)arg;
    for(int i=0;i<10000;i++){push(stack1,i);}
    pthread_exit(NULL);
}

void *thread_t2(void *arg){
    struct stack *stack1 = (struct stack *)arg;
    for(int i=-1;i>=-10000;i--){push(stack1,i);}
    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2;
    struct stack *stack1 = create();
    pthread_create(&t1,NULL,thread_t1,stack1);
    pthread_create(&t2,NULL,thread_t2,stack1);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    printf("Elements actually pushed to the stack: %d\n", stack1->top + 1);
    return 0;
}

// Question: How many total elements should have been pushed to the stack? How many elements actually have been pushed to the stack? If you are seeing a discrepancy explain what is causing it? If you were pushing smaller number of elements (say t1 pushes 1 to 100 and t2 pushes -1 to -100) do you still see the discrepancy? Explain.

// Answer: If we were dealing with smaller sets of elements (for instance, if t1 pushes from 1 to 100 and t2 pushes from -1 to -100), the program should run smoothly without encountering any discrepancies. This is because the operations executed by the threads are more likely to complete without conflicts or race conditions when handling smaller data sets. However, when dealing with larger data sets, such as simultaneously pushing from 1 to 10,000 and from -1 to -10,000, discrepancies may arise due to race conditions or concurrent access to the stack, potentially leading to missing elements in the stack.
