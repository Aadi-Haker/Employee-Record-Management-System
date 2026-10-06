#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Employee {
    int eid;
    char name[30];
    char address[50];
    char contact[15];
    float salary;
    float tax;
};

void displayMenu();
void inputRecords(struct Employee e[], int *n);
void sortByName(struct Employee e[], int n);
void displayRecords(struct Employee e[], int n);
void displayByReducingTax(struct Employee e[], int n);
void searchByEid(struct Employee e[], int n);
void calculateTax(struct Employee *e);

int main() {
    struct Employee emp[MAX];
    int n = 0;
    int choice;

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inputRecords(emp, &n);
                break;

            case 2:
                sortByName(emp, n);
                displayRecords(emp, n);
                break;

            case 3:
                displayByReducingTax(emp, n);
                break;

            case 4:
                searchByEid(emp, n);
                break;

            case 5:
                printf("\nExiting the program...\n");
                exit(0);

            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }
    return 0;
}

void displayMenu() {
    printf("\n====================================\n");
    printf("EMPLOYEE RECORD MANAGEMENT SYSTEM\n");
    printf("====================================\n");
    printf("1. Input Records\n");
    printf("2. Display Records in Ascending Order by Name\n");
    printf("3. Display Salary After Tax Deduction\n");
    printf("4. Search Employee by EID\n");
    printf("5. Exit\n");
    printf("====================================\n");
}

void calculateTax(struct Employee *e) {
    e->tax = 0.01 * e->salary;
}

void inputRecords(struct Employee e[], int *n) {
    printf("\nEnter employee details:\n");
    printf("Employee ID: ");
    scanf("%d", &e[*n].eid);

    printf("Name: ");
    scanf("%s", e[*n].name);

    printf("Address: ");
    scanf("%s", e[*n].address);

    printf("Contact Number: ");
    scanf("%s", e[*n].contact);

    printf("Salary: ");
    scanf("%f", &e[*n].salary);

    calculateTax(&e[*n]);
    (*n)++;

    printf("Record inserted successfully.\n");
}

void sortByName(struct Employee e[], int n) {
    int i, j;
    struct Employee temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (strcmp(e[j].name, e[j + 1].name) > 0) {
                temp = e[j];
                e[j] = e[j + 1];
                e[j + 1] = temp;
            }
        }
    }
}

void displayRecords(struct Employee e[], int n) {
    int i;

    if (n == 0) {
        printf("\nNo records available.\n");
        return;
    }

    printf("\nEmployees in ascending order by Name:\n");
    printf("EID\tName\tAddress\tContact\tSalary\tTax\n");

    for (i = 0; i < n; i++) {
        printf("%d\t%s\t%s\t%s\t%.2f\t%.2f\n",
               e[i].eid,
               e[i].name,
               e[i].address,
               e[i].contact,
               e[i].salary,
               e[i].tax);
    }
}

void displayByReducingTax(struct Employee e[], int n) {
    int i;
    float totalSalary = 0.0, totalTax = 0.0;

    if (n == 0) {
        printf("\nNo records available.\n");
        return;
    }

    printf("\nSalary after tax deduction:\n");
    printf("EID\tName\tSalary\tTax\tNet Salary\n");

    for (i = 0; i < n; i++) {
        float netSalary = e[i].salary - e[i].tax;

        printf("%d\t%s\t%.2f\t%.2f\t%.2f\n",
               e[i].eid,
               e[i].name,
               e[i].salary,
               e[i].tax,
               netSalary);

        totalSalary += e[i].salary;
        totalTax += e[i].tax;
    }

    printf("\nTotal Salary: %.2f\n", totalSalary);
    printf("Total Tax: %.2f\n", totalTax);
    printf("Total Net Salary: %.2f\n", totalSalary - totalTax);
}

void searchByEid(struct Employee e[], int n) {
    int id, i, found = 0;

    printf("\nEnter Employee ID to search: ");
    scanf("%d", &id);

    for (i = 0; i < n; i++) {
        if (e[i].eid == id) {
            printf("\nEmployee found:\n");
            printf("EID: %d\n", e[i].eid);
            printf("Name: %s\n", e[i].name);
            printf("Address: %s\n", e[i].address);
            printf("Contact: %s\n", e[i].contact);
            printf("Salary: %.2f\n", e[i].salary);
            printf("Tax: %.2f\n", e[i].tax);
            printf("Net Salary: %.2f\n", e[i].salary - e[i].tax);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nEmployee with EID %d not found.\n", id);
    }
}