// MCDO PAYROLL SYSTEM
// Members:
// Samuel Angelo Udtohan
// Marchus Deligro
// David Gellasan
// 2sem final project
















// Include library
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

















// Define limits for employee data, PIN, Pay period day, hours per day and file name
#define MAX_EMPLOYEES 20
#define ADMIN_PIN 1234
#define FILENAME "mcdoPayroll.txt"
#define PAY_PERIOD_DAYS 7
#define HOURS_PER_DAY 8
















// Employee data storage
int employeeCount = 0;
int ids[MAX_EMPLOYEES];
char names[MAX_EMPLOYEES][50];
char positions[MAX_EMPLOYEES][20];
int salaries[MAX_EMPLOYEES];
int deductions[MAX_EMPLOYEES];
char deductionReason[MAX_EMPLOYEES][100];
float hoursWorked[MAX_EMPLOYEES];
int lastPaidDay[MAX_EMPLOYEES];
int attendance[MAX_EMPLOYEES];
int balances[MAX_EMPLOYEES];
















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
void viewBalance(int i);
void withdrawBalance(int i);
void viewDeducted(int i);
void saveToFile();
void loadFromFile();
void viewAttendance();
void markAttendance(int i);
void paySalaries();
















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
        printf("\n\n\n\t\t\t   **           **             ** ** **                                         **          **    **     \n");
        printf("\t\t\t   ** **     ** **     ** **   **      **    ** * **    ** ** **      ** ** **  **    ** ** **    **           \n");
        printf("\t\t\t   **  **  **   **   **        **      **  **       **  ***     **  **      **  **  **      **         ** **   \n");
        printf("\t\t\t   **    **     **  **         **      **  **       **  **      **  **      **  **  **      **        **       \n");
        printf("\t\t\t   **           **   **        **      **  **       **  **      **  **      **  **  **      **            **   \n");
        printf("\t\t\t   **           **     ** **   ** ** **      ** * **    **      **    ** ** **  **    ** ** **        ** **    \n");
        printf("\n\n\t\t\t\t                                      PAYROLL SYSTEM  ");
        printf("\n\n\t\t\t\t                                      1. ADMIN        ");
        printf("\n\n\t\t\t\t                                      2. EMPLOYEE     ");
        printf("\n\n\t\t\t\t                                      3. EXIT         ");
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
                printf("\n\t\t\t\t                                     Invalid choice.\n");
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
        printf("\n\n\t\t\t\t                                      ADMIN MENU          ");
        printf("\n\n\t\t\t\t                                      1. VIEW EMPLOYEE    ");
        printf("\n\n\t\t\t\t                                      2. ADD EMPLOYEE     ");
        printf("\n\n\t\t\t\t                                      3. UPDATE DETAIL    ");
        printf("\n\n\t\t\t\t                                      4. REMOVE EMPLOYEE  ");
        printf("\n\n\t\t\t\t                                      5. DEDUCT SALARY    ");
        printf("\n\n\t\t\t\t                                      6. VIEW ATTENDANCE  ");
        printf("\n\n\t\t\t\t                                      7. PAY SALARIES     ");
        printf("\n\n\t\t\t\t                                      8. BACK             ");
        printf("\n\n\n\t\t\t\t                                      Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewEmployees();
                break;
            case 2:
                addEmployee();
                break;
            case 3:
                updateEmployee();
                break;
            case 4:
                removeEmployee();
                break;
            case 5:
                deductSalary();
                break;
            case 6:
                viewAttendance();
                break;
            case 7:
                paySalaries();
                break;
        }
    } while (choice != 8);
}
















// Display all employees
void viewEmployees() {
    system("cls");
    if (employeeCount == 0) {
        printf("\n\t\t\t\t                                    No employees yet\n");
        return;
    }

    printf("\n\t\t   %-5s      %-25.25s      %-20s      %-10s      %-15s      %-10s\n",
            "ID", "Name", "Position", "Salary/Day", "Days Worked", "Total Salary");

    for (int i = 0; i < employeeCount; i++) {
        int totalSalary = salaries[i] * attendance[i];
        printf("\t\t   %-5d      %-25.25s      %-20.20s      Php%-7d      %-15d      Php%-7d\n",
                ids[i],   names[i],   positions[i],   salaries[i],   attendance[i],   totalSalary);
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
    printf("\n\t\t\t\t                                      SELECT NEW POSITION           \n");
    printf("\n\t\t\t\t                                      1. Service Crew (100 per day) \n");
    printf("\n\t\t\t\t                                      2. Cooker       (150 per day) \n");
    printf("\n\t\t\t\t                                      3. Counter Crew (120 per day) \n");
    printf("\n\n\t\t\t\t                                      Choice: ");
    scanf("%d", &pos);

    switch (pos) {
        case 1:
            strcpy(positions[employeeCount], "Service Crew  ");
            salaries[employeeCount] = 100;
            break;
        case 2:
            strcpy(positions[employeeCount], "Cooker        ");
            salaries[employeeCount] = 150;
            break;
        case 3:
            strcpy(positions[employeeCount], "Counter Crew  ");
            salaries[employeeCount] = 120;
            break;
        default:
            printf("\n\t\t\t\t                                      Invalid position.\n");
            return;
    }

    attendance[employeeCount]   = 0;
    deductions[employeeCount]   = 0;
    hoursWorked[employeeCount]  = 0.0;
    lastPaidDay[employeeCount]  = -1;
    balances[employeeCount]     = 0;

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

    printf("\n\t\t\t\t                                      UPDATE EMPLOYEE DETAILS  \n");
    printf("\n\t\t\t\t                                      1. Update Name           \n");
    printf("\n\t\t\t\t                                      2. Update Position       \n");
    printf("\n\t\t\t\t                                      3. Update Attendance     \n");
    printf("\n\t\t\t\t                                      4. Back                  \n");
    printf("\n\t\t\t\t                                      Choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            printf("\n\t\t\t\t                                      Enter new name: ");
            getchar();
            scanf(" %[^\n]", names[i]);
            break;
        case 2:
            printf("\n\t\t\t\t                                      SELECT NEW POSITION \n");
            printf("\n\t\t\t\t                                      1. Service Crew     \n");
            printf("\n\t\t\t\t                                      2. Cooker           \n");
            printf("\n\t\t\t\t                                      3. Counter Crew     \n");
            printf("\n\t\t\t\t                                      Choice: ");
            scanf("%d", &choice);
            switch (choice) {
                case 1:
                    strcpy(positions[i], "Service Crew  ");
                    salaries[i] = 100;
                    break;
                case 2:
                    strcpy(positions[i], "Cooker        ");
                    salaries[i] = 150;
                    break;
                case 3:
                    strcpy(positions[i], "Counter Crew  ");
                    salaries[i] = 120;
                    break;
                default:
                    printf("\n\t\t\t\t                                      Invalid position.\n");
                    return;
            }
            break;
        case 3:
            printf("\n\t\t\t\t                                      Enter new attendance days: ");
            scanf("%d", &attendance[i]);
            break;
    }

    saveToFile();
    printf("\n\t\t\t\t                                      Employee updated.\n");
}
















// Remove employee
void removeEmployee() {
    system("cls");
    int id, i;
    printf("\n\t\t\t\t                                  Enter Employee ID to remove: ");
    scanf("%d", &id);

    i = findEmployee(id);
    if (i == -1) {
        printf("\n\t\t\t\t                                      Employee not found.\n");
        return;
    }

    for (int j = i; j < employeeCount - 1; j++) {
        ids[j] = ids[j + 1];
        strcpy(names[j], names[j + 1]);
        strcpy(positions[j], positions[j + 1]);
        salaries[j] = salaries[j + 1];
        deductions[j] = deductions[j + 1];
        strcpy(deductionReason[j], deductionReason[j + 1]);
        hoursWorked[j] = hoursWorked[j + 1];
        lastPaidDay[j] = lastPaidDay[j + 1];
        attendance[j] = attendance[j + 1];
        balances[j] = balances[j + 1];
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

    printf("\n\t\t\t                                      Enter Employee ID to deduct from: ");
    scanf("%d", &id);
    i = findEmployee(id);
    if (i == -1) {
        printf("\n\t\t\t\t                                      Employee not found.\n");
        return;
    }

    printf("\n\t\t\t\t                                    Enter deduction amount: ");
    scanf("%d", &amount);
    getchar();
    printf("\n\t\t\t\t                                      Enter reason for deduction: ");
    scanf(" %[^\n]", reason);

    deductions[i] += amount;
    strcpy(deductionReason[i], reason);
    saveToFile();

    printf("\n\t\t\t\t                                      Salary deducted.\n");
}
















// View all employee attendance
void viewAttendance() {
    system("cls");
    if (employeeCount == 0) {
        printf("\n\t\t\t\t                                    No employees yet\n");
        return;
    }

    printf("\n\t\t\t   %-5s      %-25.25s      %-20s      %-20s      %s\n",
            "ID", "Name", "Position", "Attendance (Days)", "Hours Worked");

    for (int i = 0; i < employeeCount; i++) {
        printf("\t\t\t   %-5d      %-25.25s      %-20s      %-20d        %2.f\n",   
            ids[i],   names[i],   positions[i],   attendance[i],   hoursWorked[i]);
    }
}
















// Function to pay salaries
void paySalaries() {
    system("cls");
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int currentDayOfYear = tm.tm_yday;

    printf("\n\t\t\t\t                                      PAYING SALARIES\n");
    for (int i = 0; i < employeeCount; i++) {
        if (lastPaidDay[i] == -1 ||
            (currentDayOfYear - lastPaidDay[i] >= PAY_PERIOD_DAYS) ||
            (currentDayOfYear < lastPaidDay[i] &&
            (365 - lastPaidDay[i] + currentDayOfYear) >= PAY_PERIOD_DAYS)) {

            int totalSalary = salaries[i] * attendance[i];
                totalSalary -= deductions[i];

            printf("\n\t\t                                      Paying employee \"%s\": Php %d\n", names[i], totalSalary);
            balances[i]    = totalSalary;
            lastPaidDay[i] = currentDayOfYear;
            attendance[i]  = 0;
            hoursWorked[i] = 0.0;
        } else {
            printf("\n\t\t                                      It's not time to pay employee \"%s\" yet.\n", names[i]);
        }
    }
    saveToFile();
    printf("\n\t\t\t\t                                      Salaries paid.\n");
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
        printf("\n\n\t\t\t\t                                      EMPLOYEE MENU         \n");
        printf("\n\t\t\t                                ID: %-5d  Name: %-25.25s  Attendance: %d days\n\n",   ids[i],   names[i],   attendance[i]);
        printf("\n\t\t\t\t                                      1. VIEW BALANCE         \n");
        printf("\n\t\t\t\t                                      2. WITHDRAW SALARY      \n");
        printf("\n\t\t\t\t                                      3. VIEW DEDUCTED        \n");
        printf("\n\t\t\t\t                                      4. MARK ATTENDANCE (In) \n");
        printf("\n\t\t\t\t                                      5. BACK                 \n");
        printf("\n\t\t\t\t                                      Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewBalance(i);
                break;
            case 2:
                withdrawBalance(i);
                break;
            case 3:
                viewDeducted(i);
                break;
            case 4:
                markAttendance(i);
                break;
        }
    } while (choice != 5);
}
















// Show salary info
void viewBalance(int i) {
    system("cls");
    if (balances[i] == 0) {
        printf("\n\t\t\t\t                                      No Salary yet\n");
        return;
    }
    printf("\n\t\t\t\t                                      Balances: Php %d\n", balances[i]);
}

















// Withdraw salary
void withdrawBalance(int i) {
    system("cls");
    int amount, choice;

    printf("\n\t\t\t\t                                      Balance: %d", balances[i]);
    printf("\n\n\t\t\t\t                                      Withdrawal Options ");
    printf("\n\n\t\t\t\t                                      1. Cash            ");
    printf("\n\n\t\t\t\t                                      2. GCash           ");
    printf("\n\n\t\t\t\t                                      3. Maya            ");
    printf("\n\n\t\t\t\t                                      Choice: ");
    scanf("%d", &choice);

    printf("\n\t\t\t\t                              Enter amount to withdraw: ");
    scanf("%d", &amount);

    if (amount <= balances[i]) {
        balances[i] -= amount;
        switch (choice) {
            case 1:
                printf("\n\t\t\t\t                            Withdrawal successful. New Balance: %d\n", balances[i]);
                break;
            case 2:
                printf("\n\t\t\t\t                            Successfully transferred Php %d to your GCash account.\n", amount);
                printf("\n\t\t\t\t                            New Balance: %d\n", balances[i]);
                break;
            case 3:
                printf("\n\t\t\t\t                            Successfully transferred Php %d to your Maya account.\n", amount);
                printf("\n\t\t\t\t                            New Balance: %d\n", balances[i]);
                break;
            default:
                printf("\n\t\t\t\t                            Invalid choice. Withdrawal cancelled.\n");
                balances[i] += amount; 
        }
    } else {
        printf("\n\t\t\t\t                              Not enough balance to withdraw.\n");
    }
    saveToFile();
}

















// Show deductions
void viewDeducted(int i) {
    system("cls");
    printf("\n\t\t\t\t                                    Total Deducted:  %d\n", deductions[i]);
    printf("\n\t\t\t\t                                    Reason:          %s\n", deductionReason[i]);
}
















// Mark attendance (In)
void markAttendance(int i) {
    system("cls");
    hoursWorked[i] += HOURS_PER_DAY;
    attendance[i] += 1;
    saveToFile();
    printf("\n\t\t\t\t                               Attendance marked for today.\n");
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
        fprintf(file, "%d %s %s %d %d %f %d %s %d %d\n", ids[i], names[i], positions[i], salaries[i], deductions[i], hoursWorked[i], lastPaidDay[i], deductionReason[i], attendance[i], balances[i]);
    }
    fclose(file);
}
















// Load employees from file
void loadFromFile() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) return;
    fscanf(file, "%d", &employeeCount);
    for (int i = 0; i < employeeCount; i++) {
        fscanf(file, "%d %s %s %d %d %f %d %s %d %d", &ids[i], names[i], positions[i], &salaries[i], &deductions[i], &hoursWorked[i], &lastPaidDay[i], deductionReason[i], &attendance[i], &balances[i]);
    }
    fclose(file);
}















