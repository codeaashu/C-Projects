#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_SUBJECTS 5
#define MAX_NAME_LENGTH 50

struct Subject {
    char name[50];
    int grade;
};

struct Student {
    char name[MAX_NAME_LENGTH];
    struct Subject subjects[MAX_SUBJECTS];
    float gpa;
};

struct Student students[MAX_STUDENTS];
int numStudents = 0;

void addStudent() {
    if (numStudents >= MAX_STUDENTS) {
        printf("Maximum number of students reached!\n");
        return;
    }

    struct Student newStudent;
    printf("Enter student name: ");
    scanf("%s", newStudent.name);

    for (int i = 0; i < MAX_SUBJECTS; i++) {
        printf("Enter subject name and grade (e.g., Math 90, or enter 'done' to stop): ");
        scanf("%s", newStudent.subjects[i].name);
        if (strcmp(newStudent.subjects[i].name, "done") == 0) {
            break;
        }
        scanf("%d", &newStudent.subjects[i].grade);
    }

    students[numStudents++] = newStudent;
}

void calculateGPA(struct Student *student) {
    float totalGrade = 0.0;
    for (int i = 0; i < MAX_SUBJECTS; i++) {
        totalGrade += student->subjects[i].grade;
    }
    student->gpa = totalGrade / MAX_SUBJECTS;
}

void updateGrades() {
    char name[MAX_NAME_LENGTH];
    printf("Enter student name to update grades: ");
    scanf("%s", name);

    for (int i = 0; i < numStudents; i++) {
        if (strcmp(students[i].name, name) == 0) {
            for (int j = 0; j < MAX_SUBJECTS; j++) {
                printf("Enter new grade for %s (or enter 'done' to stop): ", students[i].subjects[j].name);
                scanf("%s", name);
                if (strcmp(name, "done") == 0) {
                    break;
                }
                scanf("%d", &students[i].subjects[j].grade);
            }
            calculateGPA(&students[i]);
            printf("Grades updated successfully!\n");
            return;
        }
    }
    printf("Student not found!\n");
}

void generateReport() {
    printf("Student Name\tGPA\n");
    for (int i = 0; i < numStudents; i++) {
        printf("%s\t%.2f\n", students[i].name, students[i].gpa);
    }
}

int main() {
    int choice;
    do {
        printf("\nStudent Grade Tracker Menu:\n");
        printf("1. Add Student\n");
        printf("2. Update Grades\n");
        printf("3. Generate Report\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                updateGrades();
                break;
            case 3:
                generateReport();
                break;
            case 4:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}
