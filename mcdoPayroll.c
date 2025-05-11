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
#define PAY_PERIOD_DAYS 30
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
int clockIns[MAX_EMPLOYEES];
int clockOuts[MAX_EMPLOYEES];
int daysWorked[MAX_EMPLOYEES];
int isClockedIn[MAX_EMPLOYEES];
time_t lastIn[MAX_EMPLOYEES];
time_t lastOut[MAX_EMPLOYEES];
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
void viewDeducted(int i);
void saveToFile();
void loadFromFile();
void viewAttendance();
void markAttendance(int i, int isIn);
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

        if (scanf("%d", &choice) != 1) {
            printf("\n\t\t\t\t                                     Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

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
        printf("\n\n\t\t\t\t                                        ADMIN MENU      ");
        printf("\n\n\t\t\t\t                                    1. VIEW   EMPLOYEE  ");
        printf("\n\n\t\t\t\t                                    2. ADD    EMPLOYEE  ");
        printf("\n\n\t\t\t\t                                    3. UPDATE   DETAIL  ");
        printf("\n\n\t\t\t\t                                    4. REMOVE EMPLOYEE  ");
        printf("\n\n\t\t\t\t                                    5. DEDUCT   SALARY  ");
        printf("\n\n\t\t\t\t                                    6. VIEW ATTENDANCE  ");
        printf("\n\n\t\t\t\t                                    7. BACK             ");
        printf("\n\n\n\t\t\t\t                                  Choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("\n\t\t\t\t                            Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

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
            default:
                printf("\n\t\t\t\t                                     Invalid choice.\n");
        }
    } while (choice != 7);
}

















// Display all employees
void viewEmployees() {
    system("cls");
    if (employeeCount == 0) {
        printf("\n\t\t\t\t                                    No employees yet\n");
        return;
    }

    printf("\n\t\t   %-5s      %-25.25s      %-20s      %-10s      %-15s      %-10s\n",
            "ID",   "Name",   "Position",   "Salary/Day",   "Days Worked",   "Total Salary");

    for (int i = 0; i < employeeCount; i++) {
        int totalSalary = salaries[i] * daysWorked[i];
        totalSalary -= deductions[i];
        if (totalSalary < 0) totalSalary = 0;


        printf("\t\t   %-5d      %-25.25s      %-20.20s      Php%-7d      %-15d      Php%-7d\n",
                ids[i],   names[i],   positions[i],   salaries[i],   daysWorked[i],   totalSalary);
    }
}

















// Add new employee
void addEmployee() {
    system("cls");
    if (employeeCount >= MAX_EMPLOYEES) {
        printf("\n\t\t\t\t                                      Employee limit reached.\n");
        return;
    }

    getchar();
    char tempName[50];
    int nameExists = 0;

    printf("\n\t\t\t\t                                      Enter Name: ");
    scanf(" %[^\n]", tempName);

    for (int i = 0; i < employeeCount; i++) {
        if (strcmp(tempName, names[i]) == 0) {
            nameExists = 1;
            break;
        }
    }

    if (nameExists) {
        printf("\n\t\t\t\t                             Name already exists. Cannot add employee.\n");
        return;
    }

    strcpy(names[employeeCount], tempName);
    ids[employeeCount] = employeeCount + 1;

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

    deductions[employeeCount] = 0;
    hoursWorked[employeeCount] = 0.0;
    lastPaidDay[employeeCount] = -1;
    balances[employeeCount] = 0;
    clockIns[employeeCount] = 0;
    clockOuts[employeeCount] = 0;
    daysWorked[employeeCount] = 0;
    isClockedIn[employeeCount] = 0;
    lastIn[employeeCount] = 0;
    lastOut[employeeCount] = 0;

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
    printf("\n\t\t\t\t                                      3. Back                  \n");
    printf("\n\n\t\t\t\t                                      Choice: ");
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
            printf("\n\n\t\t\t\t                                      Choice: ");
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
    }

    saveToFile();
    printf("\n\t\t\t\t                                      Employee updated.\n");
}

















// Remove employee
void removeEmployee() {
    system("cls");
    int id, i;
    printf("\n\t\t\t\t                                   Enter Employee ID to remove: ");
    scanf("%d", &id);

    char confirm;
    printf("\n\t\t\t\t                        Are you sure you want to remove this employee? (y/n): ");
    scanf(" %c", &confirm);
    if (confirm != 'y' && confirm != 'Y') return;

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
        clockIns[j] = clockIns[j + 1];
        clockOuts[j] = clockOuts[j + 1];
        daysWorked[j] = daysWorked[j + 1];
        isClockedIn[j] = isClockedIn[j + 1];
        lastIn[j] = lastIn[j + 1];
        lastOut[j] = lastOut[j + 1];
        balances[j] = balances[j + 1];
    }

    employeeCount--;
    saveToFile();
    printf("\n\t\t\t\t                                      Employee removed.\n");
}

















// Deduct salary
void deductSalary() {
    system("cls");
    int id, i;
    float sssContribution = 0.0;
    float pagIbigContribution = 0.0;
    float philHealthContribution = 0.0;

    printf("\n\t\t\t                                      Enter Employee ID to deduct from: ");
    scanf("%d", &id);
    i = findEmployee(id);
    if (i == -1) {
        printf("\n\t\t\t\t                                      Employee not found.\n");
        return;
    }

    sssContribution = salaries[i] * 0.045;
    if (sssContribution > 900) {
        sssContribution = 900;
    }

    if (salaries[i] < 1500) {
        pagIbigContribution = salaries[i] * 0.01;
    } else {
        pagIbigContribution = salaries[i] * 0.02;
        if (salaries[i] > 10000) {
            pagIbigContribution = 10000 * 0.02; 
        }
    }

    philHealthContribution = 100.0;

    deductions[i] += (int)(sssContribution + pagIbigContribution + philHealthContribution);

    strcpy(deductionReason[i], "SSS, PhilHealth, Pag-IBIG");

    saveToFile();

    printf("\n\t\t\t\t                                      Deductions applied.\n");
    printf("\n\t\t\t\t                          SSS: %.2f, PhilHealth: %.2f, Pag-IBIG: %.2f\n", sssContribution, philHealthContribution, pagIbigContribution);
}

















// View all employee attendance
void viewAttendance() {
    system("cls");
    int id, i;

    printf("\n\t\t\t\t                                  Enter Employee ID: ");
    scanf("%d", &id);

    i = findEmployee(id);
    if (i == -1) {
        printf("\n\t\t\t\t                                      ID not found.\n");
        return;
    }

    printf("\n\t\t\t\t                                %s: %-5d  |  %s: %-25.25s \n", "ID", ids[i], "Name", names[i]);

    printf("\n\t\t\t\t                            %-30s     %-30s  \n", "Clock In Time", "Clock Out Time");

    for (int j = 0; j < clockIns[i] || j < clockOuts[i]; j++) {
        char inTimeStr[35] = "N/A";
        char outTimeStr[35] = "N/A";

        if (j < clockIns[i]) {
            time_t inTime = lastIn[i];
            strftime(inTimeStr, sizeof(inTimeStr), "%Y-%m-%d %H:%M:%S", localtime(&inTime));
        }

        if (j < clockOuts[i]) {
            time_t outTime = lastOut[i]; 
            strftime(outTimeStr, sizeof(outTimeStr), "%Y-%m-%d %H:%M:%S", localtime(&outTime));
        }

        printf("\n\t\t\t\t                            %-30s     %-30s \n", inTimeStr, outTimeStr);
    }
}
















// Function to pay salaries
void paySalaries() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int currentDayOfYear = tm.tm_yday;

    printf("\n\t\t\t\t                                      PAYING MONTHLY SALARIES\n");
    for (int i = 0; i < employeeCount; i++) {
        if (lastPaidDay[i] == -1 ||
            (currentDayOfYear - lastPaidDay[i] >= PAY_PERIOD_DAYS) ||
            (currentDayOfYear < lastPaidDay[i] &&
            (365 - lastPaidDay[i] + currentDayOfYear) >= PAY_PERIOD_DAYS)) {

            int totalSalary = salaries[i] * daysWorked[i];
            totalSalary -= deductions[i];
            if (totalSalary < 0) totalSalary = 0;

            printf("\n\t\t                                      Paying MONTHLY salary to \"%s\": Php %d\n", names[i], totalSalary);
            balances[i] = totalSalary;
            lastPaidDay[i] = currentDayOfYear;
            daysWorked[i] = 0; 
        } else {
            printf("\n\t\t                                      \"%s\" hasn't completed 30 working days yet.\n", names[i]);
        }
    }
    saveToFile();
    printf("\n\t\t\t\t                                      Monthly salaries processed.\n");
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
        printf("\n\t\t\t                                ID: %-5d  Name: %-25.25s  Attendance: %d days\n", ids[i], names[i], daysWorked[i]);
        printf("\n\n\n\t\t\t\t                                      1. VIEW  BALANCE    \n");
        printf("\n\t\t\t\t                                      2. VIEW DEDUCTED        \n");
        printf("\n\t\t\t\t                                      3. CLOCK      IN        \n");
        printf("\n\t\t\t\t                                      4. CLOCK     OUT        \n");
        printf("\n\t\t\t\t                                      5. BACK                 \n");
        printf("\n\n\t\t\t\t                                      Choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\n\t\t\t\t                           Invalid input. Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                viewBalance(i);
                break;
            case 2:
                viewDeducted(i);
                break;
            case 3:
                markAttendance(i, 1); 
                break;
            case 4:
                markAttendance(i, 0); 
                break;
            case 5:
                break;
            default:
                printf("\n\t\t\t\t                                     Invalid choice.\n");
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

















// Show deductions
void viewDeducted(int i) {
    system("cls");
    printf("\n\t\t\t\t                                    Total Deducted:  %d\n", deductions[i]);
    printf("\n\t\t\t\t                                    Reason:          %s\n", deductionReason[i]);
}

















// Mark attendance IN and OUT
void markAttendance(int i, int isIn) {
    time_t now = time(NULL);

    if (isIn) {
        isClockedIn[i] = 1;
        clockIns[i]++;
        lastIn[i] = now;
        printf("\n\t\t\t\t                               Clocked IN successfully.\n");
    } else {
        if (!isClockedIn[i]) {
            printf("\n\t\t\t\t                               Not clocked IN. Cannot clock OUT.\n");
            return;
        }

        isClockedIn[i] = 0;
        clockOuts[i]++;
        lastOut[i] = now;
        daysWorked[i]++;  // Increment worked days
        
        // Automatically process salary after 30 days
        if (daysWorked[i] >= 30) {
            // Calculate deductions
            float sss = salaries[i] * 30 * 0.045;  // 4.5% of monthly salary
            if (sss > 900) sss = 900;
            
            float pagIbig;
            float monthlySalary = salaries[i] * 30;
            if (monthlySalary < 1500) {
                pagIbig = monthlySalary * 0.01;
            } else {
                pagIbig = monthlySalary * 0.02;
                if (pagIbig > 200) pagIbig = 200;  // Max Pag-IBIG contribution
            }
            
            float philhealth = 100.0;
            
            int totalDeductions = (int)(sss + pagIbig + philhealth);
            int totalSalary = (salaries[i] * 30) - totalDeductions;
            
            if (totalSalary < 0) totalSalary = 0;
            
            // Update balance and reset counters
            balances[i] += totalSalary;
            daysWorked[i] -= 30;
            
            printf("\n\t\t\t\t                               Salary paid automatically: Php%d\n", totalSalary);
        }
        
        printf("\n\t\t\t\t                               Clocked OUT successfully. Day counted.\n");
    }
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
        fprintf(file, "%d %s %s %d %d %f %d %s %d %d %d %d %ld %ld %d\n",   ids[i],   names[i],   positions[i],   salaries[i],   deductions[i],   hoursWorked[i],   lastPaidDay[i],   deductionReason[i],   clockIns[i],   clockOuts[i],   daysWorked[i],   isClockedIn[i],   (long)lastIn[i],   (long)lastOut[i],   balances[i]);
    }
    fclose(file);
}

















// Load employees from file
void loadFromFile() {
    FILE *file = fopen(FILENAME, "r");
    if (!file) {
        return;
    }

    if (fscanf(file, "%d", &employeeCount) != 1) {
        fprintf(stderr, "Error reading employee count from file.\n");
        fclose(file);
        return;
    }

    for (int i = 0; i < employeeCount; i++) {
        long lin, lout;
        if (fscanf(file, "%d %s %s %d %d %f %d %s %d %d %d %d %ld %ld %d",   &ids[i],   names[i],   positions[i],   &salaries[i],   &deductions[i],   &hoursWorked[i],   &lastPaidDay[i],   deductionReason[i],   &clockIns[i],   &clockOuts[i],   &daysWorked[i],   &isClockedIn[i],    &lin,   &lout,   &balances[i]) != 15) {
            fprintf(stderr, "Error reading employee data from file (employee %d).\n", i + 1);
            fclose(file);
            return;
        }
        lastIn[i] = (time_t)lin;
        lastOut[i] = (time_t)lout;
    }
    fclose(file);
}
















