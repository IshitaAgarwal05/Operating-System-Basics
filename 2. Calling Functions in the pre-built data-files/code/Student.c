#include <stdio.h>
#include <stdlib.h>

struct Student {
    char name[90];
    int rollno;
};

struct Node {
    struct Student data;
    struct Node* next;
};

struct ListStudents {
    struct Node* head;
};

void printNames(struct ListStudents* list) {
    struct Node* ptr = list->head;
    while (ptr != NULL) {
        printf("Name: %s\n", ptr->data.name);
        printf("Roll Number: %d\n", ptr->data.rollno);
        ptr = ptr->next;
    }
}

struct Node* createNode(char name[90], int rollnum) {
    struct Node* newnode = (struct Node*)malloc(sizeof(struct Node));
    if (newnode != NULL) {
        snprintf(newnode->data.name, sizeof(newnode->data.name), "%s", name);
        newnode->data.rollno = rollnum;
        newnode->next = NULL;
    } return newnode;
}

struct Node* searchStudent(struct ListStudents* list, int rollnum) {
    struct Node* ptr = list->head;
    while (ptr != NULL) {
        if (ptr->data.rollno == rollnum) {return ptr;} 
        ptr = ptr->next;
    } return NULL;  
}

void deleteStudent(struct ListStudents* list, int rollnum) {
    struct Node* current = list->head;
    struct Node* previous = NULL;
    while (current != NULL && current->data.rollno != rollnum) {
        previous = current;
        current = current->next;
    }
    
    if (current != NULL) {
        if (previous == NULL) {list->head = current->next;} 
        else {previous->next = current->next;}
        free(current);  
    }
}

void freeList(struct ListStudents* list) {
    struct Node* ptr = list->head;
    while (ptr != NULL) {
        struct Node* next = ptr->next;
        free(ptr);
        ptr = next;
    } list->head = NULL;
}

int main() {
    struct ListStudents studentList;
    studentList.head = NULL;

    FILE* file = fopen("../data/Students", "r");

    if (file == NULL) {
        printf("Error opening file");
        return 1;
    }
    
    struct Node* lastNode = NULL;
    while (1) {
        char name[90];
        int rollnum;
        if (fscanf(file, "%89[^\n]%*c%d", name, &rollnum) != 2) {
            break;
        }

        struct Node* newNode = createNode(name, rollnum);

        if (newNode == NULL) {
            printf("Memory allocation error");
            fclose(file);
            return 1;
        }

        if (lastNode == NULL) {studentList.head = newNode;} 
        else {lastNode->next = newNode;}

        lastNode = newNode;
        fgetc(file);  
    }
    
    fclose(file);

    int choice;
    int rollToSearch, rollToDelete;
    do {
        printf("\nMenu:\n");
        printf("1. Print the list\n");
        printf("2. Search for a student\n");
        printf("3. Delete a student\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nList of students:\n");
                printNames(&studentList);
                break;
            case 2:
                printf("\nEnter the roll number to search: ");
                scanf("%d", &rollToSearch);
                struct Node* foundStudent = searchStudent(&studentList, rollToSearch);
                if (foundStudent != NULL) {
                    printf("\nStudent found with roll number %d:\n", rollToSearch);
                    printf("Name: %s\n", foundStudent->data.name);
                    printf("Roll Number: %d\n", foundStudent->data.rollno);
                } else {
                    printf("\nStudent with roll number %d not found.\n", rollToSearch);
                }
                break;
            case 3:
                printf("\nEnter the roll number to delete: ");
                scanf("%d", &rollToDelete);
                deleteStudent(&studentList, rollToDelete);
                printf("\nStudent with roll number %d deleted.\n", rollToDelete);
                break;
            case 4:
                printf("Exiting from the program\n");
                break;
            default:
                printf("\nInvalid choice. Please enter a valid option.\n");
        }
    } while (choice != 4);
    freeList(&studentList);
    return 0;
}
