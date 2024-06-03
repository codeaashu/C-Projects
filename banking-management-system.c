#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100
#define MAX_TRANSACTIONS 100

struct Transaction {
    char type[20]; // "Deposit", "Withdrawal", "Transfer"
    float amount;
};

struct Account {
    int accountNumber;
    char name[50];
    float balance;
    struct Transaction transactions[MAX_TRANSACTIONS];
    int numTransactions;
};

struct Account accounts[MAX_ACCOUNTS];
int numAccounts = 0;

int findAccount(int accountNumber) {
    for (int i = 0; i < numAccounts; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            return i;
        }
    }
    return -1;
}

void createAccount() {
    if (numAccounts >= MAX_ACCOUNTS) {
        printf("Maximum number of accounts reached!\n");
        return;
    }

    struct Account newAccount;
    newAccount.accountNumber = numAccounts + 1;
    printf("Enter account holder's name: ");
    scanf("%s", newAccount.name);
    newAccount.balance = 0.0;
    newAccount.numTransactions = 0;

    accounts[numAccounts++] = newAccount;
    printf("Account created successfully. Account Number: %d\n", newAccount.accountNumber);
}

void deposit(int accountNumber, float amount) {
    int index = findAccount(accountNumber);
    if (index != -1) {
        accounts[index].balance += amount;
        strcpy(accounts[index].transactions[accounts[index].numTransactions].type, "Deposit");
        accounts[index].transactions[accounts[index].numTransactions].amount = amount;
        accounts[index].numTransactions++;
        printf("Deposit successful. Current balance: %.2f\n", accounts[index].balance);
    } else {
        printf("Account not found!\n");
    }
}

void withdraw(int accountNumber, float amount) {
    int index = findAccount(accountNumber);
    if (index != -1) {
        if (accounts[index].balance >= amount) {
            accounts[index].balance -= amount;
            strcpy(accounts[index].transactions[accounts[index].numTransactions].type, "Withdrawal");
            accounts[index].transactions[accounts[index].numTransactions].amount = amount;
            accounts[index].numTransactions++;
            printf("Withdrawal successful. Current balance: %.2f\n", accounts[index].balance);
        } else {
            printf("Insufficient balance!\n");
        }
    } else {
        printf("Account not found!\n");
    }
}

void transfer(int fromAccount, int toAccount, float amount) {
    int fromIndex = findAccount(fromAccount);
    int toIndex = findAccount(toAccount);

    if (fromIndex != -1 && toIndex != -1) {
        if (accounts[fromIndex].balance >= amount) {
            accounts[fromIndex].balance -= amount;
            accounts[toIndex].balance += amount;

            strcpy(accounts[fromIndex].transactions[accounts[fromIndex].numTransactions].type, "Transfer (To)");
            accounts[fromIndex].transactions[accounts[fromIndex].numTransactions].amount = amount;
            accounts[fromIndex].numTransactions++;

            strcpy(accounts[toIndex].transactions[accounts[toIndex].numTransactions].type, "Transfer (From)");
            accounts[toIndex].transactions[accounts[toIndex].numTransactions].amount = amount;
            accounts[toIndex].numTransactions++;

            printf("Transfer successful. Current balances:\n");
            printf("From Account %d: %.2f\n", fromAccount, accounts[fromIndex].balance);
            printf("To Account %d: %.2f\n", toAccount, accounts[toIndex].balance);
        } else {
            printf("Insufficient balance in the sender's account!\n");
        }
    } else {
        printf("One or both accounts not found!\n");
    }
}

void viewTransactions(int accountNumber) {
    int index = findAccount(accountNumber);
    if (index != -1) {
        printf("Transaction history for Account %d:\n", accountNumber);
        for (int i = 0; i < accounts[index].numTransactions; i++) {
            printf("%d. Type: %s, Amount: %.2f\n", i + 1, accounts[index].transactions[i].type, accounts[index].transactions[i].amount);
        }
    } else {
        printf("Account not found!\n");
    }
}

int main() {
    int choice, accountNumber, toAccount;
    float amount;

    do {
        printf("\nBanking System Menu:\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Transfer\n");
        printf("5. View Transactions\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                printf("Enter amount to deposit: ");
                scanf("%f", &amount);
                deposit(accountNumber, amount);
                break;
            case 3:
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                printf("Enter amount to withdraw: ");
                scanf("%f", &amount);
                withdraw(accountNumber, amount);
                break;
            case 4:
                printf("Enter sender's account number: ");
                scanf("%d", &accountNumber);
                printf("Enter recipient's account number: ");
                scanf("%d", &toAccount);
                printf("Enter amount to transfer: ");
                scanf("%f", &amount);
                transfer(accountNumber, toAccount, amount);
                break;
            case 5:
                printf("Enter account number: ");
                scanf("%d", &accountNumber);
                viewTransactions(accountNumber);
                break;
            case 6:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
