#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 50
#define MAX_USERNAME 50
#define MAX_PASSWORD 50

struct User {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
};

struct User users[MAX_USERS];
int numUsers = 0;

void signup() {
    if (numUsers >= MAX_USERS) {
        printf("Cannot add more users. Maximum user limit reached.\n");
        return;
    }

    printf("Enter username: ");
    scanf("%s", users[numUsers].username);

    printf("Enter password: ");
    scanf("%s", users[numUsers].password);

    numUsers++;
    printf("User signed up successfully!\n");
}

int login() {
    char username[MAX_USERNAME], password[MAX_PASSWORD];
    printf("Enter username: ");
    scanf("%s", username);

    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < numUsers; i++) {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) {
            printf("Login successful!\n");
            return 1; // Return 1 for successful login
        }
    }

    printf("Invalid username or password. Login failed.\n");
    return 0; // Return 0 for failed login
}

int main() {
    int choice;
    do {
        printf("1. Signup\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                signup();
                break;
            case 2:
                if (login()) {
                    // Continue to user's menu or other functionalities
                    printf("Welcome to the system!\n");
                }
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 3);

    return 0;
}
