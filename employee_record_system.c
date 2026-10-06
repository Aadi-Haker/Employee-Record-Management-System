#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYEES 100
#define NAME_SIZE 50
#define ADDRESS_SIZE 100
#define CONTACT_SIZE 20

struct Employee {
    int eid;
    char name[NAME_SIZE];
    char address[ADDRESS_SIZE];
    char contact[CONTACT_SIZE];
    float salary;
    float tax;
};

/* Function prototypes */
void displayMenu(void);
void inputRecord(struct Employee employees[], int *count);
void displayRecords(const struct Employee employees[], int count);
void sortByName(struct Employee employees[], int count);
void displaySalaryAfterTax(const struct Employee employees[], int count);
void searchByEid(const struct Employee employees[], int count);
void calculateTax(struct Employee *employee);
int eidExists(const struct Employee employees[], int count, int eid);
void clearInputBuffer(void);
void pauseScreen(void);

/* Main function */
int main(void)
{
    struct Employee employees[MAX_EMPLOYEES];
    int count = 0;
    int choice;

    while (1)
    {
        displayMenu();

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid input! Please enter a number.\n");
            clearInputBuffer();
            pauseScreen();
            continue;
        }

        clearInputBuffer();

        switch (choice)
        {
            case 1:
                inputRecord(employees, &count);
                break;

            case 2:
                if (count == 0)
                {
                    printf("\nNo employee records available.\n");
                }
                else
                {
                    sortByName(employees, count);
                    displayRecords(employees, count);
                }
                pauseScreen();
                break;

            case 3:
                displaySalaryAfterTax(employees, count);
                pauseScreen();
                break;

            case 4:
                searchByEid(employees, count);
                pauseScreen();
                break;

            case 5:
                printf("\nExiting the program...\n");
                return 0;

            default:
                printf("\nInvalid choice! Please enter 1-5.\n");
                pauseScreen();
        }
    }

    return 0;
}

/* Display menu */
void displayMenu(void)
{
    printf("\n============================================\n");
    printf("       EMPLOYEE RECORD MANAGEMENT SYSTEM\n");
    printf("============================================\n");
    printf("1. Input Employee Record\n");
    printf("2. Display Records by Name (Ascending)\n");
    printf("3. Display Salary After Tax Deduction\n");
    printf("4. Search Employee by EID\n");
    printf("5. Exit\n");
    printf("============================================\n");
}

/* Calculate 1% tax */
void calculateTax(struct Employee *employee)
{
    employee->tax = employee->salary * 0.01f;
}

/* Check whether EID already exists */
int eidExists(const struct Employee employees[], int count, int eid)
{
    int i;

    for (i = 0; i < count; i++)
    {
        if (employees[i].eid == eid)
        {
            return 1;
        }
    }

    return 0;
}

/* Input employee record */
void inputRecord(struct Employee employees[], int *count)
{
    struct Employee *employee;

    if (*count >= MAX_EMPLOYEES)
    {
        printf("\nEmployee database is full!\n");
        printf("Maximum capacity: %d employees.\n", MAX_EMPLOYEES);
        pauseScreen();
        return;
    }

    employee = &employees[*count];

    printf("\n========== ENTER EMPLOYEE DETAILS ==========\n");

    /* Employee ID */
    while (1)
    {
        printf("Employee ID: ");

        if (scanf("%d", &employee->eid) != 1)
        {
            printf("Invalid ID! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        if (employee->eid <= 0)
        {
            printf("Employee ID must be positive.\n");
            continue;
        }

        if (eidExists(employees, *count, employee->eid))
        {
            printf("This Employee ID already exists.\n");
            continue;
        }

        break;
    }

    /* Name */
    printf("Name: ");
    fgets(employee->name, NAME_SIZE, stdin);
    employee->name[strcspn(employee->name, "\n")] = '\0';

    /* Address */
    printf("Address: ");
    fgets(employee->address, ADDRESS_SIZE, stdin);
    employee->address[strcspn(employee->address, "\n")] = '\0';

    /* Contact */
    printf("Contact Number: ");
    fgets(employee->contact, CONTACT_SIZE, stdin);
    employee->contact[strcspn(employee->contact, "\n")] = '\0';

    /* Salary */
    while (1)
    {
        printf("Salary: ");

        if (scanf("%f", &employee->salary) != 1)
        {
            printf("Invalid salary! Please enter a number.\n");
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        if (employee->salary < 0)
        {
            printf("Salary cannot be negative.\n");
            continue;
        }

        break;
    }

    /* Calculate tax */
    calculateTax(employee);

    (*count)++;

    printf("\nRecord inserted successfully!\n");
    printf("Tax (1%%): %.2f\n", employee->tax);

    pauseScreen();
}

/* Sort employees alphabetically by name */
void sortByName(struct Employee employees[], int count)
{
    int i, j;
    struct Employee temp;

    for (i = 0; i < count - 1; i++)
    {
        for (j = 0; j < count - i - 1; j++)
        {
            if (strcmp(employees[j].name, employees[j + 1].name) > 0)
            {
                temp = employees[j];
                employees[j] = employees[j + 1];
                employees[j + 1] = temp;
            }
        }
    }
}

/* Display all employee records */
void displayRecords(const struct Employee employees[], int count)
{
    int i;

    if (count == 0)
    {
        printf("\nNo records available.\n");
        return;
    }

    printf("\n================ EMPLOYEE RECORDS ================\n");

    printf("%-8s %-20s %-25s %-15s %12s %10s\n",
           "EID",
           "Name",
           "Address",
           "Contact",
           "Salary",
           "Tax");

    printf("------------------------------------------------------------------------------------------\n");

    for (i = 0; i < count; i++)
    {
        printf("%-8d %-20s %-25s %-15s %12.2f %10.2f\n",
               employees[i].eid,
               employees[i].name,
               employees[i].address,
               employees[i].contact,
               employees[i].salary,
               employees[i].tax);
    }

    printf("------------------------------------------------------------------------------------------\n");
}

/* Display salary after tax */
void displaySalaryAfterTax(const struct Employee employees[], int count)
{
    int i;
    float totalSalary = 0.0f;
    float totalTax = 0.0f;
    float netSalary;

    if (count == 0)
    {
        printf("\nNo employee records available.\n");
        return;
    }

    printf("\n=============== SALARY AFTER TAX ===============\n");

    printf("%-8s %-20s %12s %12s %15s\n",
           "EID",
           "Name",
           "Salary",
           "Tax",
           "Net Salary");

    printf("---------------------------------------------------------------------\n");

    for (i = 0; i < count; i++)
    {
        netSalary = employees[i].salary - employees[i].tax;

        printf("%-8d %-20s %12.2f %12.2f %15.2f\n",
               employees[i].eid,
               employees[i].name,
               employees[i].salary,
               employees[i].tax,
               netSalary);

        totalSalary += employees[i].salary;
        totalTax += employees[i].tax;
    }

    printf("---------------------------------------------------------------------\n");

    printf("Total Salary    : %.2f\n", totalSalary);
    printf("Total Tax       : %.2f\n", totalTax);
    printf("Total Net Salary: %.2f\n", totalSalary - totalTax);
}

/* Search employee by EID */
void searchByEid(const struct Employee employees[], int count)
{
    int id;
    int i;

    if (count == 0)
    {
        printf("\nNo employee records available.\n");
        return;
    }

    printf("\nEnter Employee ID to search: ");

    if (scanf("%d", &id) != 1)
    {
        printf("Invalid Employee ID.\n");
        clearInputBuffer();
        return;
    }

    clearInputBuffer();

    for (i = 0; i < count; i++)
    {
        if (employees[i].eid == id)
        {
            printf("\n============== EMPLOYEE FOUND ==============\n");
            printf("Employee ID : %d\n", employees[i].eid);
            printf("Name        : %s\n", employees[i].name);
            printf("Address     : %s\n", employees[i].address);
            printf("Contact     : %s\n", employees[i].contact);
            printf("Salary      : %.2f\n", employees[i].salary);
            printf("Tax         : %.2f\n", employees[i].tax);
            printf("Net Salary  : %.2f\n",
                   employees[i].salary - employees[i].tax);
            printf("============================================\n");

            return;
        }
    }

    printf("\nEmployee with EID %d was not found.\n", id);
}

/* Clear unwanted characters from input buffer */
void clearInputBuffer(void)
{
    int character;

    while ((character = getchar()) != '\n' && character != EOF)
    {
        /* Discard input */
    }
}

/* Pause program */
void pauseScreen(void)
{
    printf("\nPress Enter to continue...");
    getchar();
}
