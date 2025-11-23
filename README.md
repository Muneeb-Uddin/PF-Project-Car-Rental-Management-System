CAR RENTAL MANAGEMENT SYSTEM

This project is a car rental system made in C language.

WHAT IT DOES:
- Add cars to the system
- Register customers
- Rent cars to customers
- Return cars and show bills
- Track money earned
- Save all data in files

WHO MADE IT:
Name: Muneeb Uddin
University: FAST NU
Course: Programming Fundamentals
Year: 2024

HOW TO RUN:
gcc main.c car_operations.c rental_operations.c customer_operations.c file_operations.c -o Project_PF
Project_PF.exe

TOOLS USED:
- Language: C
- Compiler: GCC
- Editor: VS Code

PROJECT FILES:
main.c - Main program
structures.h - Data definitions
utils.h - Helper functions
car_operations.c - Car functions
customer_operations.c - Customer functions
rental_operations.c - Rental functions
file_operations.c - File save/load functions

SAMPLE DATA:
cars.txt - 30 cars
customers.txt - 15 customers
rentals.txt - 17 rental records

FEATURES:
- Customer can rent many cars
- System tracks all rentals
- Money report shows earnings
- Data saved in text files
- Cars sorted by ID when saved