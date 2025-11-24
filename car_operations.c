#include "structures.h"
#include "utils.h"
#include "car_operations.h"
void addCar() 
{
    system("cls");
    printf("\n========================================\n");
    printf("          ADD NEW CAR\n");
    printf("========================================\n");
    if(car_count >= MAX_CARS) 
    {
        printf("\n*** Error: Car storage is full! ***\n");
        pauseScreen();
        return;
    }
    struct Car newcar;
    printf("\nEnter Car ID: ");
    if(scanf("%d", &newcar.id) != 1) 
    {
        clearBuffer();
        printf("\n*** Error: Invalid ID! ***\n");
        pauseScreen();
        return;
    }
    clearBuffer();
    int i = 0;
    while(i < car_count) 
    {
        if(cars[i].id == newcar.id) 
        {
            printf("\n*** Error: Car ID %d already exists! ***\n", newcar.id);
            pauseScreen();
            return;
        }
        i++;
    }
    printf("Enter Brand (e.g. Toyota): ");
    fgets(newcar.brand, sizeof(newcar.brand), stdin);
    newcar.brand[strcspn(newcar.brand, "\n")] = 0;
    printf("Enter Model (e.g. Corolla): ");
    fgets(newcar.model, sizeof(newcar.model), stdin);
    newcar.model[strcspn(newcar.model, "\n")] = 0;
    printf("Enter Rent per Day (Rs.): ");
    if(scanf("%f", &newcar.rent_per_day) != 1) 
    {
        clearBuffer();
        printf("\n*** Error: Invalid rent amount! ***\n");
        pauseScreen();
        return;
    }
    clearBuffer();
    if(newcar.rent_per_day <= 0) 
    {
        printf("\n*** Error: Rent must be greater than 0! ***\n");
        pauseScreen();
        return;
    }
    newcar.is_rented = 0;
    cars[car_count] = newcar;
    car_count++;
    printf("\n========================================\n");
    printf("\tCar Added Successfully!\n");
    printf("========================================\n");
    printf("Car ID: %d\n", newcar.id);
    printf("Brand: %s\n", newcar.brand);
    printf("Model: %s\n", newcar.model);
    printf("Rent/Day: Rs. %.2f\n", newcar.rent_per_day);
    pauseScreen();
}
void displayCars() 
{
    system("cls");
    printf("\n========================================\n");
    printf("          ALL CARS LIST\n");
    printf("========================================\n");
    if(car_count == 0) 
    {
        printf("\n*** No cars available in system! ***\n");
        pauseScreen();
        return;
    }
    printf("\nTotal Cars: %d\n", car_count);
    printf("\n%-5s %-15s %-15s %-12s %-10s\n", "ID", "Brand", "Model", "Rent/Day", "Status");
    printf("----------------------------------------------------------------\n");
    int i = 0;
    do 
    {
        printf("%-5d %-15s %-15s Rs. %-8.2f %-10s\n", cars[i].id, cars[i].brand, cars[i].model, cars[i].rent_per_day, cars[i].is_rented ? "RENTED" : "Available");
        i++;
    } 
    while(i < car_count);
    printf("----------------------------------------------------------------\n");
    pauseScreen();
}
int searchCar(int car_id) 
{
    int i = 0;
    while(i < car_count) 
    {
        if(cars[i].id == car_id) 
            return i;
        i++;
    }
    return -1;
}