// Members:
// Samuel Angelo Udtohan
// Marchus Deligro
// David Gellasan
// 2sem final project
// Mcdo Payroll System

















// Include library
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

















// DEfine limits for employee members, Pin code, and filename
#define MAX_EMPLOYEES 20
#define ADMIN_PIN 1234
#define FILENAME "mcdoPayroll.txt"

















// Employee data storage
int employeeCount = 0;
int ids[MAX_EMPLOYEES];
char names[MAX_EMPLOYEES][50];
char positions[MAX_EMPLOYEES][20];
int salaries[MAX_EMPLOYEES];
int monthsWorked[MAX_EMPLOYEES];
int deductions[MAX_EMPLOYEES];
char deductionReasons[MAX_EMPLOYEES][100];
int balances[MAX_EMPLOYEES];
int attendance[MAX_EMPLOYEES]; 
















// Function declarations
void mainMenu();
void adminMenu();
void employeeMenu();
int verifyPin();
void viewEmployees();
void addEmployee();
void updateEmployee();
void removeEmployee();
void deductSalary();
int findEmployee(int id);
void viewSalary(int i);
void withdrawSalary(int i);
void viewDeducted(int i);
void saveToFile();
void loadFromFile();
void viewAttendance();
void markAttendance(int i);


















// Main function
int main() {
    loadFromFile(); 
    mainMenu();
    return 0;
}

















// MAIN MENU
void mainMenu() {
    int choice;
    do {
        system("cls");
        printf("\n\n\n\t\t\t   **           **             ** ** **                                         **          **    **       \n");
        printf("\t\t\t   ** **     ** **     ** **   **      **    ** * **    ** ** **      ** ** **  **    ** ** **    **           \n");
        printf("\t\t\t   **  **  **   **   **        **      **  **       **  ***     **  **      **  **  **      **         ** **   \n");
        printf("\t\t\t   **    **     **  **         **      **  **       **  **      **  **      **  **  **      **        **       \n");
        printf("\t\t\t   **           **   **        **      **  **       **  **      **  **      **  **  **      **            **   \n");
        printf("\t\t\t   **           **     ** **   ** ** **      ** * **    **      **    ** ** **  **    ** ** **        ** **    \n");  
        printf("\n\n\t\t\t\t                                      PAYROLL SYSTEM");   
        printf("\n\n\t\t\t\t                                      1. ADMIN");
        printf("\n\n\t\t\t\t                                      2. EMPLOYEE");
        printf("\n\n\t\t\t\t                                      3. EXIT");
        printf("\n\n\t\t\t\t                                      Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (verifyPin()) adminMenu();
                break;
            case 2:
                employeeMenu();
                break;
            case 3:
                printf("\n\t\t\t\t                                      Exiting system.\n");
                break;
            default:
                printf("\n\t\t\t\t                                      Invalid choice.\n");
        }
    } while (choice != 3);
}

















// PIN verification
int verifyPin() {
    int pin;
    printf("\n\t\t\t\t                                  Enter Admin PIN: ");
    scanf("%d", &pin);
    return pin == ADMIN_PIN;
}

















// ADMIN MENU
void adminMenu() {
    system("cls");
    int choice;
    do {
        printf("\n\n\t\t\t\t                                      ADMIN MENU");
        printf("\n\n\t\t\t\t                                      1. VIEW EMPLOYEE");
        printf("\n\n\t\t\t\t                                      2. ADD EMPLOYEE");
        printf("\n\n\t\t\t\t                                      3. UPDATE DETAIL");
        printf("\n\n\t\t\t\t                                      4. REMOVE EMPLOYEE");
        printf("\n\n\t\t\t\t                                      5. DEDUCT SALARY");
        printf("\n\n\t\t\t\t                                      6. VIEW ATTENDANCE");  
        printf("\n\n\t\t\t\t                                      7. BACK");
        printf("\n\n\n\t\t\t\t                                      Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: viewEmployees();  break;
            case 2: addEmployee();    break;
            case 3: updateEmployee(); break;
            case 4: removeEmployee(); break;
            case 5: deductSalary();   break;
            case 6: viewAttendance(); break;  
        }
    } while (choice != 7);
}

















// View all employee attendance
void viewAttendance() {
    system("cls");
    if (employeeCount == 0) {
        printf("\n\t\t\t\t                                    No employees yet\n");
        return;
    }

    printf("\n\t\t\t\t   %-5s\t %-20s\t %-20s\t %-15s\n",
        "ID", "Name", "Position", "Attendance (Days)");

    for (int i = 0; i < employeeCount; i++) {
        printf("\t\t\t\t   %-5d\t %-20s\t %-20s\t %-15d\n",
            ids[i], names[i], positions[i], attendance[i]);
    }
}


















// Display all employees
void viewEmployees() {
    
    system("cls");
    if (employeeCount == 0) {
        printf("\n\t\t\t\t                                    No employees yet\n");
        return;
    }

    printf("\n\t\t   %-5s\t %-20s\t %-20s\t %-10s\t %-15s\t %-10s\n",
        "ID", "Name", "Position", "Salary/Day", "Days Worked", "Total Salary");

    for (int i = 0; i < employeeCount; i++) {
        int totalSalary = salaries[i] * attendance[i];
        printf("\t\t   %-5d\t %-20s\t %-20s\t Php%-7d\t %-15d\t Php%-7d\n",
            ids[i], names[i], positions[i], salaries[i], attendance[i], totalSalary);
    }
}


















// Add new employee
void addEmployee() {
    system("cls");
    if (employeeCount >= MAX_EMPLOYEES) {
        printf("\n\t\t\t\t                                      Employee limit reached.\n");
        return;
    }

    ids[employeeCount] = employeeCount + 1;

    getchar();
    printf("\n\t\t\t\t                                      Enter Name: ");
    scanf(" %[^\n]", names[employeeCount]);

    int pos;
    printf("\n\t\t\t\t                                      SELECT NEW POSITION\n");
    printf("\n\t\t\t\t                                      1. Service Crew (100 per day)\n");
    printf("\n\t\t\t\t                                      2. Cooker       (150 per day)\n");
    printf("\n\t\t\t\t                                      3. Counter Crew (120 per day)\n");
    printf("\n\n\t\t\t\t                                      Choice: ");
    scanf("%d", &pos);

    switch (pos) {
        case 1: strcpy(positions[employeeCount], "Service Crew  "); salaries[employeeCount] = 100; break;
        case 2: strcpy(positions[employeeCount], "Cooker        "); salaries[employeeCount] = 150; break;
        case 3: strcpy(positions[employeeCount], "Counter Crew  "); salaries[employeeCount] = 120; break;
        default: printf("\n\t\t\t\t                                      Invalid position.\n"); return;
    }

    attendance[employeeCount] = 0;
    deductions[employeeCount] = 0;
    balances[employeeCount] =   0;  

    employeeCount++;
    saveToFile();
    printf("\n\t\t\t\t                                      Employee added successfully.\n");
}

















// Update employee info
void updateEmployee() {
    system("cls");
    int id, choice, i;
    printf("\n\t\t\t\t                              Enter Employee ID: ");
    scanf("%d", &id);

    i = findEmployee(id);
    if (i == -1) {
        printf("\n\t\t\t\t                                 Employee not found.\n");
        return;
    }

    printf("\n\t\t\t\t                                      UPDATE EMPLOYEE DETAILS\n");
    printf("\n\t\t\t\t                                      1. Update Name\n");
    printf("\n\t\t\t\t                                      2. Update Position\n");
    printf("\n\t\t\t\t                                      3. Update Attendance\n");
    printf("\n\t\t\t\t                                      4. Back\n");
    printf("\n\t\t\t\t                                      Choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("\n\t\t\t\t                                      Enter new name: ");
            getchar();
            scanf(" %[^\n]", names[i]);
            break;
        case 2:
            printf("\n\t\t\t\t                                      SELECT NEW POSITION\n");
            printf("\n\t\t\t\t                                      1. Service Crew\n");
            printf("\n\t\t\t\t                                      2. Cooker\n");
            printf("\n\t\t\t\t                                      3. Counter Crew\n");
            printf("\n\t\t\t\t                                      Choice: ");
            scanf("%d", &choice);
            switch (choice) {
                case 1: strcpy(positions[i], "Service Crew  "); salaries[i] = 100; break;
                case 2: strcpy(positions[i], "Cooker        "); salaries[i] = 150; break;
                case 3: strcpy(positions[i], "Counter Crew  "); salaries[i] = 120; break;
                default: printf("\n\t\t\t\t                                      Invalid position.\n"); return;
            }
            break;
        case 3:
            printf("\n\t\t\t\t                                      Enter new attendance days: ");
            scanf("%d", &attendance[i]);
            balances[i] = salaries[i] * attendance[i] - deductions[i];
            break;
    }

    saveToFile();
    printf("\n\t\t\t\t                                      Employee updated.\n");
}

















// Remove employee
void removeEmployee() {
    system("cls");
    int id, i;
    printf("\n\t\t\t\t                                      Enter Employee ID to remove: ");
    scanf("%d", &id);

    i = findEmployee(id);
    if (i == -1) {
        printf("\n\t\t\t\t                                      Employee not found.\n");
        return;
    }

    for (int i = i; i < employeeCount - 1; i++) {
        ids[i] = ids[i + 1];
        strcpy(names[i], names[i + 1]);
        strcpy(positions[i], positions[i + 1]);
        salaries[i] = salaries[i + 1];
        monthsWorked[i] = monthsWorked[i + 1];
        deductions[i] = deductions[i + 1];
        strcpy(deductionReasons[i], deductionReasons[i + 1]);
        balances[i] = balances[i + 1];
    }

    employeeCount--;
    saveToFile();
    printf("\n\t\t\t\t                                      Employee removed.\n");
}

















// Deduct salary
void deductSalary() {
    system("cls");
    int id, amount, i;
    char reason[100];

    printf("\n\t\t\t\t                                      Enter Employee ID to deduct from: ");
    scanf("%d", &id);
    i = findEmployee(id);
    if (i == -1) {
        printf("\n\t\t\t\t                                      Employee not found.\n");
        return;
    }

    printf("\n\t\t\t\t                                      Enter deduction amount: ");
    scanf("%d", &amount);
    getchar(); 
    printf("\n\t\t\t\t                                      Enter reason for deduction: ");
    scanf(" %[^\n]", reason);  

    deductions[i] += amount;
    balances[i] -= amount;
    strcpy(deductionReasons[i], reason);
    saveToFile();

    printf("\n\t\t\t\t                                      Salary deducted.\n");
}


















// EMPLOYEE MENU
void employeeMenu() {
    system("cls");
    int id, i, choice;
    printf("\n\t\t\t\t                                  Enter Employee ID: ");
    scanf("%d", &id);

    i = findEmployee(id);
    if (i == -1) {
        printf("\n\t\t\t\t                                      ID not found.\n");
        return;
    }

    do {
        printf("\n\n\t\t\t\t                                      EMPLOYEE MENU\n");
        printf("\n\t\t\t\t                            ID: %d | Name: %s | Balance: %d | Attendance: %d days\n\n", ids[i], names[i], balances[i], attendance[i]);
        printf("\n\t\t\t\t                                      1. VIEW DETAILS\n");
        printf("\n\t\t\t\t                                      2. WITHDRAW SALARY\n");
        printf("\n\t\t\t\t                                      3. VIEW DEDUCTED\n");
        printf("\n\t\t\t\t                                      4. MARK ATTENDANCE (In)\n");
        printf("\n\t\t\t\t                                      5. BACK\n");
        printf("\n\t\t\t\t                                      Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: viewSalary(i);     break;
            case 2: withdrawSalary(i); break;
            case 3: viewDeducted(i);   break;
            case 4: markAttendance(i); break; 
        }
    } while (choice != 5);
}

















// Show salary info
void viewSalary(int i) {
    system("cls");
    printf("\n\t\t\t    ID: %d\t\t Name: %s\t\t Position: %s\t\t Days Worked: %d\n",ids[i], names[i], positions[i], attendance[i]);
    printf("\n\t\t\t\t                                      Salary: Php%d\n", balances[i]);
}

















// Withdraw salary
void withdrawSalary(int i) {
    system("cls");
    int amount;
    printf("\n\t\t\t\t                                      Balance: %d\n\n\t\t\t\t                            Enter amount to withdraw: ", balances[i]);
    scanf("%d", &amount);

    if (amount <= balances[i]) {
        balances[i] -= amount;
        printf("\n\t\t\t\t                             Withdrawal successful. New balance: %d\n", balances[i]);
    } else {
        printf("\n\t\t\t\t                                   Insufficient balance.\n");
    }
}

















// Show deductions
void viewDeducted(int i) {
    system("cls");
    printf("\n\t\t\t\t                                    Total Deducted:  %d\n", deductions[i]);
    printf("\n\t\t\t\t                                    Reason:          %s\n", deductionReasons[i]);
}

















// Mark attendance (In)
void markAttendance(int i) {
    system("cls");
    attendance[i]++;
    balances[i] = salaries[i] * attendance[i] - deductions[i];
    printf("\n\t\t\t\t                                Attendance marked as 'In' for today.\n");
    saveToFile();  
}


















// Find employee by ID
int findEmployee(int id) {
    for (int i = 0; i < employeeCount; i++) {
        if (ids[i] == id) return i;
    }
    return -1;
}

















// Save employees to file
void saveToFile() {
    FILE *file = fopen(FILENAME, "w");
    if (!file) {
        return;
    }

    fprintf(file, "%d\n", employeeCount);
    for (int i = 0; i < employeeCount; i++) {
        fprintf(file, "%d %s %s %d %d %d %d %d %s\n",  ids[i], names[i], positions[i],
            salaries[i], monthsWorked[i],
            deductions[i], balances[i], attendance[i], deductionReasons[i]);
    }
    fclose(file);
}

















// Load employees from file
void loadFromFile() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) return;

    fscanf(file, "%d", &employeeCount);
    for (int i = 0; i < employeeCount; i++) {
        fscanf(file, "%d %s %s %d %d %d %d %d %[^\n]", 
            &ids[i], names[i], positions[i],
            &salaries[i], &monthsWorked[i],
            &deductions[i], &balances[i], &attendance[i], deductionReasons[i]);
    }
    fclose(file);
}















