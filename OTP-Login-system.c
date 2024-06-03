#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define MAX_USERS 50
#define MAX_PHONE_NUMBER 11 // Including space for null terminator

struct User {
    char phoneNumber[MAX_PHONE_NUMBER];
    int otp;
    int otpVerified;
};

struct User users[MAX_USERS];
int numUsers = 0;

void signup() {
    if (numUsers >= MAX_USERS) {
        printf("Cannot add more users. Maximum user limit reached.\n");
        return;
    }

    printf("Enter phone number (10 digits): ");
    scanf("%s", users[numUsers].phoneNumber);

    users[numUsers].otpVerified = 0; // OTP not verified initially
    numUsers++;
    printf("User signed up successfully!\n");
}

void generateOTP(struct User *user) {
    srand(time(NULL));
    user->otp = rand() % 9000 + 1000; // Generate a 4-digit OTP
    printf("OTP for login: %d\n", user->otp); // Display OTP in terminal
}

int login() {
    char phoneNumber[MAX_PHONE_NUMBER];
    printf("Enter phone number (10 digits): ");
    scanf("%s", phoneNumber);

    for (int i = 0; i < numUsers; i++) {
        if (strcmp(phoneNumber, users[i].phoneNumber) == 0) {
            generateOTP(&users[i]); // Generate OTP for the logged-in user
            printf("Enter OTP: ");
            int otp;
            scanf("%d", &otp);

            if (otp == users[i].otp) {
                users[i].otpVerified = 1; // OTP verified
                printf("OTP verification successful!\n");
                return 1; // Return 1 for successful login
            } else {
                printf("Incorrect OTP. Login failed.\n");
                return 0; // Return 0 for failed login
            }
        }
    }

    printf("Phone number not found. Login failed.\n");
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
