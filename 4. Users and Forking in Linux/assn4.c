#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/*
1. Ctrl+c - kill
2. ctrl + z - suspend
3. fg - continue
*/

struct Person {
    char name[20];
    int age;
};

int main(){
	
	printf("\033[1mQ1\033[0m\n");
	printf("Press any key to start!");
	getchar();
	pid_t PID = fork();
	if (PID<0){
		printf("Failed!\n");
		return 1;
	} else if (PID==0){
		int i = 1;
		while (1){
			printf("\nChild PID: %d for number %d", getpid(), i++);
			usleep(500000);
		}
	} else {
		int i = 1;
		while (1){
			printf("Parent PID: %d - Number: %d\n", getpid(), i++);
			usleep(500000);
		}
	}
	
	printf("\033[1mQ2\033[0m\n");
	int x = 10;
	int r = fork();

	if (r < 0) {perror("Fork failed");} 
	else if (r == 0) { // Child process
	x = 20;
	printf("Child process - x value: %d, x address: %p\n", x, (void *)&x);}
	else {
	printf("Parent process - x value: %d, x address: %p\n", x, (void *)&x); 		// Parent process
	}

	printf("Return value of fork: %d, fork address: %p\n", r, (void *)&r);
	
	
	
	printf("\033[1mQ3\033[0m\n");
	
	struct Person *person = malloc(sizeof(struct Person));
	if (person == NULL) {
	perror("Memory allocation failed");
	exit(EXIT_FAILURE);
	}

	pid_t pid = fork();
	if (pid < 0) {
	perror("Fork failed");
	exit(EXIT_FAILURE);
	} else if (pid == 0) { // Child process
	strcpy(person->name, "Alice");
	person->age = 25;
	printf("Child process - Person address: %p, Name: %s, Age: %d\n", (void *)person, person->name, person->age);
	} else { // Parent process
	sleep(1); // Wait for child process to finish
	printf("Parent process - Person address: %p, Name: %s, Age: %d\n", (void *)person, person->name, person->age);
	}

	free(person);
	return 0;
}
