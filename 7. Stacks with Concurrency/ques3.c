#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#define size 10000

struct stack{
    int *buffer;
    int top;
    pthread_mutex_t lock;
};

void init(struct stack *s){
    s->top = -1;
    pthread_mutex_init(&s->lock,NULL);
}

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

void push(struct stack *s,int n){
    pthread_mutex_lock(&s->lock);
    if(full(s)){printf("Stack is full\n");}
    else{
        s->top ++;
        s->buffer[s->top] = n;
    }
    pthread_mutex_unlock(&s->lock);
}

void pop(struct stack * s){
    pthread_mutex_lock(&s->lock);
    if(empty(s)){printf("Stack is empty\n");}
    else{s->top--;}
    pthread_mutex_unlock(&s->lock);
}

void display(struct stack *s){
    printf("Stack Elements: \n");
    for(int i = 0; i <= s->top; i++){
        printf("%d ", s->buffer[i]);
    }
    printf("\n");
}

void *thread1(void *arg){
    struct stack *stack1 = (struct stack *)arg;
    for(int i=0;i<5000;i++){push(stack1,i);}
    pthread_exit(NULL);
}

void *thread2(void*arg){
    struct stack * stack1 = (struct stack *)arg;
    for(int i=-1;i>=-4000;i--){push(stack1,i);}
    pthread_exit(NULL);
}

int main(){
    pthread_t t1, t2;
    struct stack *stack1 = create();
    pthread_create(&t1,NULL,thread1,stack1);
    pthread_create(&t2,NULL,thread2,stack1);
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    printf("Elements actually pushed to the stack: %d\n", stack1->top + 1);
    return 0;
}
