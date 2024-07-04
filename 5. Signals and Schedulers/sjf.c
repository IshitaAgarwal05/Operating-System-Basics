#include <stdio.h>
#include <stdlib.h>
#define MAX 100

struct Job {
    char name;
    int arrival_time;
    int execution_time;
    int start_time;
    int end_time;
};

void fcfs_scheduler(struct Job jobs[], int n) {
    int curr_time = 0;
    printf("Job\tStart\tEnd\n");
    for (int i = 0; i < n; i++) {
        if (curr_time < jobs[i].arrival_time) {
            printf("idle\t%d\t%d\n", curr_time, jobs[i].arrival_time);
            curr_time = jobs[i].arrival_time;
        }
        jobs[i].start_time = curr_time;
        jobs[i].end_time = curr_time + jobs[i].execution_time;
        printf("%c\t%d\t%d\n", jobs[i].name, jobs[i].start_time, jobs[i].end_time);
        curr_time = jobs[i].end_time;
    }
}

void sjf_scheduler(struct Job jobs[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (jobs[j].execution_time > jobs[j + 1].execution_time) {
                struct Job temp = jobs[j];
                jobs[j] = jobs[j + 1];
                jobs[j + 1] = temp;
            }
        }
    } fcfs_scheduler(jobs,n);
}

float avg_turnaround(struct Job jobs[], int n) {
    float total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_turnaround_time += jobs[i].end_time - jobs[i].arrival_time;
    } return total_turnaround_time / n;
}

int main() {
    struct Job jobs[MAX];
    int n = 0;
    FILE *file = fopen("Jobs", "r");
    if (file == NULL) {
        printf("Error opening file");
        return 1;
    }

    printf("Reading jobs from the file:\n");
    printf("Job\tArrival\tExecution\n");

    while (fscanf(file, " %c %d %d", &jobs[n].name, &jobs[n].arrival_time, &jobs[n].execution_time) == 3) {
        printf("%c\t%d\t%d\n", jobs[n].name, jobs[n].arrival_time, jobs[n].execution_time);
        n++;
    } fclose(file);
    printf("\nSJF Schedule:\n");
    sjf_scheduler(jobs, n);
    float sjf_avg_turnaround_time = avg_turnaround(jobs, n);
    printf("SJF Average Turnaround Time: %.2f\n", sjf_avg_turnaround_time);
    return 0;
}
