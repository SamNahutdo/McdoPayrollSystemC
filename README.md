***CCS 103 FINAL PROJECT***

Members

Sam Nahutdo - Programmer

Marchus *********

David *******




🔧 Functions and Their Uses
Function Name	Purpose
main()	Entry point. Loads data from file and shows the main menu.
mainMenu()	Displays the main options: Admin, Employee, or Exit.
verifyPin()	Asks for a PIN and verifies it for admin access.
adminMenu()	Displays the admin features like viewing, adding, and updating employees.
viewEmployees()	Lists all employees with their details and calculated salary.
addEmployee()	Adds a new employee to the system.
updateEmployee()	Modifies employee's name or position.
removeEmployee()	Deletes an employee by shifting arrays to remove their data.
deductSalary()	Applies salary deductions (SSS, PhilHealth, Pag-Ibig).
employeeMenu()	Menu for employee-specific actions (not shown in full yet).
viewBalance(int)	Views salary balance for a specific employee.
viewDeducted(int)	Views the amount and reason for salary deductions.
findEmployee(int)	Searches employee by ID and returns index, or -1 if not found.
saveToFile()	Saves all employee data to a file for persistence.
loadFromFile()	Loads employee data from the file when the system starts.
viewAttendance()	Displays attendance logs (if implemented).
markAttendance()	Marks clock-in and clock-out for employees (if implemented).
paySalaries()	Pays out salaries based on work days and deductions.

📚 Arrays Used and Their Purposes
Array Name	Type	Description
ids[]	int	Stores unique ID for each employee.
names[][]	char (2D array)	Stores names of employees (max 50 characters).
positions[][]	char (2D array)	Stores job titles (Service Crew, Cooker, etc.).
salaries[]	int	Daily salary for each employee depending on position.
deductions[]	int	Total amount deducted from each employee's salary.
deductionReason[][]	char (2D array)	Stores explanation or reason for deductions.
hoursWorked[]	float	Hours worked (not fully shown/used in the code yet).
lastPaidDay[]	int	Tracks the last day the salary was paid (for 7-day period).
clockIns[]	int	Count of clock-in events.
clockOuts[]	int	Count of clock-out events.
daysWorked[]	int	Number of full workdays completed.
isClockedIn[]	int (0/1)	Boolean to check if employee is currently clocked in.
lastIn[]	time_t	Stores last clock-in time (used for attendance tracking).
lastOut[]	time_t	Stores last clock-out time.
balances[]	int	Tracks salary available to be withdrawn.

🔤 Strings Used and Why
String/Char Array	Description
names[i]	Stores each employee's name (used for printing and searching).
positions[i]	Stores job title; used for display and assigning salary.
deductionReason[i]	Holds a short explanation of the deduction reason.
FILENAME (macro)	Name of the file used for saving/loading employee data.
ID: Auto-assigned integers (1–20)




