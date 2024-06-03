#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TABLES 10
#define MAX_ROWS 100
#define MAX_COLUMNS 10
#define MAX_COL_NAME_LEN 50
#define MAX_DATA_LEN 100

struct Column {
    char name[MAX_COL_NAME_LEN];
};

struct Table {
    char name[MAX_COL_NAME_LEN];
    struct Column columns[MAX_COLUMNS];
    int numColumns;
    char data[MAX_ROWS][MAX_COLUMNS][MAX_DATA_LEN];
    int numRows;
};

struct Table tables[MAX_TABLES];
int numTables = 0;

int findTableIndex(const char* tableName) {
    for (int i = 0; i < numTables; i++) {
        if (strcmp(tables[i].name, tableName) == 0) {
            return i;
        }
    }
    return -1;
}

void createTable() {
    if (numTables >= MAX_TABLES) {
        printf("Maximum number of tables reached!\n");
        return;
    }

    struct Table newTable;
    printf("Enter table name: ");
    scanf("%s", newTable.name);
    printf("Enter number of columns: ");
    scanf("%d", &newTable.numColumns);

    for (int i = 0; i < newTable.numColumns; i++) {
        printf("Enter column %d name: ", i + 1);
        scanf("%s", newTable.columns[i].name);
    }

    newTable.numRows = 0;
    tables[numTables++] = newTable;
    printf("Table created successfully.\n");
}

void insertData() {
    char tableName[MAX_COL_NAME_LEN];
    printf("Enter table name to insert data: ");
    scanf("%s", tableName);

    int tableIndex = findTableIndex(tableName);
    if (tableIndex != -1) {
        if (tables[tableIndex].numRows < MAX_ROWS) {
            printf("Enter data for each column:\n");
            for (int i = 0; i < tables[tableIndex].numColumns; i++) {
                printf("Enter %s: ", tables[tableIndex].columns[i].name);
                scanf("%s", tables[tableIndex].data[tables[tableIndex].numRows][i]);
            }
            tables[tableIndex].numRows++;
            printf("Data inserted successfully.\n");
        } else {
            printf("Maximum rows limit reached for this table.\n");
        }
    } else {
        printf("Table not found!\n");
    }
}

void selectData() {
    char tableName[MAX_COL_NAME_LEN];
    printf("Enter table name to select data: ");
    scanf("%s", tableName);

    int tableIndex = findTableIndex(tableName);
    if (tableIndex != -1) {
        printf("Data in table %s:\n", tableName);
        printf("--------------------------------------------------\n");
        printf("|");
        for (int i = 0; i < tables[tableIndex].numColumns; i++) {
            printf(" %-20s|", tables[tableIndex].columns[i].name);
        }
        printf("\n--------------------------------------------------\n");

        for (int i = 0; i < tables[tableIndex].numRows; i++) {
            printf("|");
            for (int j = 0; j < tables[tableIndex].numColumns; j++) {
                printf(" %-20s|", tables[tableIndex].data[i][j]);
            }
            printf("\n");
        }
        printf("--------------------------------------------------\n");
    } else {
        printf("Table not found!\n");
    }
}

int main() {
    int choice;
    do {
        printf("\nDatabase Management System Menu:\n");
        printf("1. Create Table\n");
        printf("2. Insert Data\n");
        printf("3. Select Data\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createTable();
                break;
            case 2:
                insertData();
                break;
            case 3:
                selectData();
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
