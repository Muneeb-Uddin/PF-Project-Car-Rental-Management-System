#include "structures.h"
#include "utils.h"
#include "car_operations.h"
#include "rental_operations.h"
#include "customer_operations.h"
#include "file_operations.h"
struct Car cars[MAX_CARS];
struct Customer customers[MAX_CUSTOMERS];
struct Rental rentals[MAX_RENTALS];
int car_count = 0;
int customer_count = 0;
int rental_count = 0;
void displayMenu() 
{
    system("cls");
    printf("\n");
    printf("========================================\n");
    printf("   CAR RENTAL MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("1. Add New Car\n");
    printf("2. Display All Cars\n");
    printf("3. Register New Customer\n");
    printf("4. Rent a Car\n");
    printf("5. Return a Car\n");
    printf("6. Search Car by ID\n");
    printf("7. Display All Customers\n");
    printf("8. Revenue & Earnings Report\n");
    printf("9. Exit\n");
    printf("========================================\n");
}
int main() 
{
    int ch;
    loadCarsFromFile();
    loadCustomersFromFile();
    loadRentalsFromFile();
    system("cls");
    printf("\n========================================\n");
    printf("   CAR RENTAL MANAGEMENT SYSTEM\n");
    printf("========================================\n");
    printf("\n*** System Started Successfully! ***\n");
    printf("\nLoaded %d cars\n", car_count);
    printf("Loaded %d customers\n", customer_count);
    printf("Loaded %d rental records\n", rental_count);
    printf("\n========================================\n");
    pauseScreen();
    while(1) 
    {
        displayMenu();
        printf("Enter your choice: ");
        if(scanf("%d", &ch) != 1) 
        {
            clearBuffer();
            printf("\n*** Invalid input! Please enter a number ***\n");
            pauseScreen();
            continue;
        }
        clearBuffer();
        switch(ch) 
        {
            case 1:
                addCar();
                break;
            case 2:
                displayCars();
                break;
            case 3:
                registerNewCustomer();
                break;
            case 4:
                rentCar();
                break;
            case 5:
                returnCar();
                break;
            case 6:
                searchCarDetails();
                break;
            case 7:
                displayAllCustomers();
                break;
            case 8:
                displayRevenue();
                break;
            case 9:
                system("cls");
                printf("\n========================================\n");
                printf("\t\tSAVING DATA...\n");
                printf("========================================\n");
                saveCarsToFile();
                saveCustomersToFile();
                saveRentalsToFile();
                printf("\n*** Data saved successfully! ***\n");
                printf("\nTotal Cars: %d\n", car_count);
                printf("Total Customers: %d\n", customer_count);
                printf("Total Rentals: %d\n", rental_count);
                printf("\n========================================\n");
                printf("\t\tTHANK YOU!\n");
                printf("========================================\n");
                printf("\nDeveloped by: Muneeb Uddin 25K-0765\n");
                printf("Course: Programming Fundamentals CL1002\n");
                printf("\n========================================\n");
                pauseScreen();
                return 0;
            default:
                printf("\n*** Invalid choice! Please enter 1-9 ***\n");
                pauseScreen();
        }
    }
    return 0;
}