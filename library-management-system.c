#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_NAME_LENGTH 50
#define MAX_ID_LENGTH 10

typedef struct {
    char id[MAX_ID_LENGTH];
    char title[MAX_NAME_LENGTH];
    char author[MAX_NAME_LENGTH];
    int available;
} Book;

Book books[MAX_BOOKS];
int numBooks = 0;

void addBook() {
    if (numBooks >= MAX_BOOKS) {
        printf("Cannot add more books. Library is full.\n");
        return;
    }

    Book newBook;
    printf("Enter book ID: ");
    scanf("%s", newBook.id);
    printf("Enter book title: ");
    scanf(" %[^\n]s", newBook.title);
    printf("Enter author name: ");
    scanf(" %[^\n]s", newBook.author);
    newBook.available = 1;  // Assume new books are available
    books[numBooks++] = newBook;
    printf("Book added successfully.\n");
}

void displayBooks() {
    printf("ID\tTitle\tAuthor\tAvailable\n");
    for (int i = 0; i < numBooks; i++) {
        printf("%s\t%s\t%s\t%s\n", books[i].id, books[i].title, books[i].author,
               (books[i].available == 1) ? "Yes" : "No");
    }
}

void deleteBook() {
    char idToDelete[MAX_ID_LENGTH];
    printf("Enter book ID to delete: ");
    scanf("%s", idToDelete);

    for (int i = 0; i < numBooks; i++) {
        if (strcmp(books[i].id, idToDelete) == 0) {
            // Shift remaining books to fill the gap
            for (int j = i; j < numBooks - 1; j++) {
                books[j] = books[j + 1];
            }
            numBooks--;
            printf("Book deleted successfully.\n");
            return;
        }
    }
    printf("Book not found.\n");
}

void updateBook() {
    char idToUpdate[MAX_ID_LENGTH];
    printf("Enter book ID to update: ");
    scanf("%s", idToUpdate);

    for (int i = 0; i < numBooks; i++) {
        if (strcmp(books[i].id, idToUpdate) == 0) {
            printf("Enter new title: ");
            scanf(" %[^\n]s", books[i].title);
            printf("Enter new author: ");
            scanf(" %[^\n]s", books[i].author);
            printf("Book updated successfully.\n");
            return;
        }
    }
    printf("Book not found.\n");
}

void issueBook() {
    char idToIssue[MAX_ID_LENGTH];
    printf("Enter book ID to issue: ");
    scanf("%s", idToIssue);

    for (int i = 0; i < numBooks; i++) {
        if (strcmp(books[i].id, idToIssue) == 0) {
            if (books[i].available == 1) {
                books[i].available = 0;  // Mark as not available
                printf("Book issued successfully.\n");
            } else {
                printf("Book is already issued.\n");
            }
            return;
        }
    }
    printf("Book not found.\n");
}

void returnBook() {
    char idToReturn[MAX_ID_LENGTH];
    printf("Enter book ID to return: ");
    scanf("%s", idToReturn);

    for (int i = 0; i < numBooks; i++) {
        if (strcmp(books[i].id, idToReturn) == 0) {
            if (books[i].available == 0) {
                books[i].available = 1;  // Mark as available
                printf("Book returned successfully.\n");
            } else {
                printf("Book is already available.\n");
            }
            return;
        }
    }
    printf("Book not found.\n");
}

void generateReport() {
    int availableBooks = 0;
    for (int i = 0; i < numBooks; i++) {
        if (books[i].available == 1) {
            availableBooks++;
        }
    }
    printf("Total books: %d\n", numBooks);
    printf("Available books: %d\n", availableBooks);
    printf("Issued books: %d\n", numBooks - availableBooks);
}

int main() {
    int choice;
    do {
        printf("\nLibrary Management System Menu:\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Delete Book\n");
        printf("4. Update Book\n");
        printf("5. Issue Book\n");
        printf("6. Return Book\n");
        printf("7. Generate Report\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                displayBooks();
                break;
            case 3:
                deleteBook();
                break;
            case 4:
                updateBook();
                break;
            case 5:
                issueBook();
                break;
            case 6:
                returnBook();
                break;
            case 7:
                generateReport();
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}
