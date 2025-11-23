#include "structures.h"
#include "utils.h"
#include "file_operations.h"
void sortCars(int n) 
{
    if(n <= 1)
        return;
    int i = 0;
    while(i < n - 1) 
    {
        if(cars[i].id > cars[i+1].id) 
        {
            struct Car temp = cars[i];
            cars[i] = cars[i+1];
            cars[i+1] = temp;
        }
        i++;
    }    
    sortCars(n - 1);
}
void sortCarsByID() 
{
    sortCars(car_count);
}
void saveCarsToFile() 
{
    sortCarsByID();    
    FILE *f = fopen("cars.txt", "w");    
    if(f == NULL) 
    {
        printf("Error saving cars!\n");
        return;
    }    
    fprintf(f, "%d\n", car_count);    
    int i = 0;
    while(i < car_count) 
    {
        char b[30], m[30];
        strcpy(b, cars[i].brand);
        strcpy(m, cars[i].model);        
        int j = 0;
        while(b[j]) 
        {
            if(b[j] == ' ') b[j] = '_';
            j++;
        }
        j = 0;
        while(m[j]) 
        {
            if(m[j] == ' ') m[j] = '_';
            j++;
        }        
        fprintf(f, "%d %s %s %.2f %d\n", cars[i].id, b, m, cars[i].rent_per_day, cars[i].is_rented);
        i++;
    }    
    fclose(f);
}
void loadCarsFromFile() 
{
    FILE *f = fopen("cars.txt", "r");
    if(f == NULL)
        return;
    fscanf(f, "%d", &car_count);    
    int i = 0;
    do 
    {
        fscanf(f, "%d %s %s %f %d", &cars[i].id, cars[i].brand, cars[i].model, &cars[i].rent_per_day, &cars[i].is_rented);        
        int j = 0;
        while(cars[i].brand[j]) 
        {
            if(cars[i].brand[j] == '_') cars[i].brand[j] = ' ';
            j++;
        }
        j = 0;
        while(cars[i].model[j]) 
        {
            if(cars[i].model[j] == '_') cars[i].model[j] = ' ';
            j++;
        }
        i++;
    }
    while(i < car_count);    
    fclose(f);
}
void saveCustomersToFile() 
{
    FILE *f = fopen("customers.txt", "w");
    if(f == NULL) 
    {
        printf("Error saving customers!\n");
        return;
    }
    fprintf(f, "%d\n", customer_count);
    int i = 0;
    while(i < customer_count) 
    {
        char n[50], a[100];
        strcpy(n, customers[i].name);
        strcpy(a, customers[i].address);
        int j = 0;
        while(n[j]) 
        {
            if(n[j] == ' ') n[j] = '_';
            j++;
        }
        j = 0;
        while(a[j]) 
        {
            if(a[j] == ' ') a[j] = '_';
            j++;
        }
        fprintf(f, "%d %s %s %s %d\n", customers[i].id, n, customers[i].phone, a, customers[i].total_rentals);
        i++;
    }
    
    fclose(f);
}
void loadCustomersFromFile() 
{
    FILE *f = fopen("customers.txt", "r");
    if(f == NULL)
        return; 
    fscanf(f, "%d", &customer_count);
    int i = 0;
    do 
    {
        fscanf(f, "%d %s %s %s %d", &customers[i].id, customers[i].name, customers[i].phone, customers[i].address, &customers[i].total_rentals);
        int j = 0;
        while(customers[i].name[j]) 
        {
            if(customers[i].name[j] == '_') customers[i].name[j] = ' ';
            j++;
        }
        j = 0;
        while(customers[i].address[j]) 
        {
            if(customers[i].address[j] == '_') customers[i].address[j] = ' ';
            j++;
        }
        i++;
    } 
    while(i < customer_count);
    fclose(f);
}
void saveRentalsToFile() 
{
    FILE *f = fopen("rentals.txt", "w");
    if(f == NULL) 
    {
        printf("Error saving rentals!\n");
        return;
    } 
    fprintf(f, "%d\n", rental_count);
    int i = 0;
    while(i < rental_count) 
    {
        fprintf(f, "%d %d %d %d %.2f %d\n", rentals[i].rental_id, rentals[i].customer_id, rentals[i].car_id, rentals[i].days, rentals[i].total_cost, rentals[i].is_returned);
        i++;
    }
    fclose(f);
}
void loadRentalsFromFile() 
{
    FILE *f = fopen("rentals.txt", "r");
    
    if(f == NULL)
        return;
    
    fscanf(f, "%d", &rental_count);
    int i = 0;
    do 
    {
        fscanf(f, "%d %d %d %d %f %d", 
               &rentals[i].rental_id, 
               &rentals[i].customer_id, 
               &rentals[i].car_id,
               &rentals[i].days,
               &rentals[i].total_cost,
               &rentals[i].is_returned);
        i++;
    }
    while(i < rental_count);
    fclose(f);
}