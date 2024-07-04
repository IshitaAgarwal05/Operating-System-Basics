#include <stdio.h>
#include <stdlib.h>

struct StudentInfo {
    char student_name[90];
    int student_rollno;
};

struct Node {
    struct StudentInfo info;
    struct Node* next_node;
};

struct StudentList {
    struct Node* list_head;
};

void display_student_names(struct StudentList* list) {
    struct Node* current_node = list->list_head;

    while (current_node != NULL) {
        printf("%s\n", current_node->info.student_name);
        printf("%d\n", current_node->info.student_rollno);
        current_node = current_node->next_node;
    }
}

struct Node* create_student_node(char name[90], int rollnum) {
    struct Node* new_student_node = (struct Node*)malloc(sizeof(struct Node));

    if (new_student_node != NULL) {
        snprintf(new_student_node->info.student_name, sizeof(new_student_node->info.student_name), "%s", name);
        new_student_node->info.student_rollno = rollnum;
        new_student_node->next_node = NULL;
    } return new_student_node;
}

int main() {
    struct StudentList class_students;
    class_students.list_head = NULL;

    FILE* data_file = fopen("/home/ishita05/Desktop/clg/oslab/assn1/data/Students", "r");
    if (data_file == NULL) {
        printf("Error opening file");
        return 1;
    }

    struct Node* last_student_node = NULL; // Keep track of the last node
    while (1) {
        char student_name[90];
        int student_rollnum;
        if (fscanf(data_file, "%89[^\n]%*c%d", student_name, &student_rollnum) != 2) {break;}
        struct Node* new_student = create_student_node(student_name, student_rollnum);
        if (new_student == NULL) {
            printf("Memory allocation error");
            fclose(data_file);
            return 1;
        }
        if (last_student_node == NULL) {class_students.list_head = new_student;} 
        else {last_student_node->next_node = new_student;}
        last_student_node = new_student; 
        fgetc(data_file);
    }

    fclose(data_file);
    display_student_names(&class_students);
    struct Node* current_node = class_students.list_head;
    while (current_node != NULL) {
        struct Node* next_node = current_node->next_node;
        free(current_node);
        current_node = next_node;
    }
    return 0;
}
