#include "structures.h"
#include "utils.h"
#include "car_operations.h"
#include "customer_operations.h"
#include "rental_operations.h"
void rentCar() 
{
    system("cls");
    printf("\n========================================\n");
    printf("          RENT A CAR\n");
    printf("========================================\n");
    int cid;
    printf("\nEnter Customer ID: ");
    if(scanf("%d", &cid) != 1) 
    {
        clearBuffer();
        printf("\n*** Error: Invalid Customer ID! ***\n");
        pauseScreen();
        return;
    }
    clearBuffer();
    int ci = findCustomerById(cid);
    if(ci == -1) 
    {
        printf("\n*** Error: Customer ID %d not found! ***\n", cid);
        printf("Please register the customer first (Option 3).\n");
        pauseScreen();
        return;
    }
    printf("\n--- Customer Details ---\n");
    printf("Name    : %s\n", customers[ci].name);
    printf("Phone   : %s\n", customers[ci].phone);
    printf("Address : %s\n", customers[ci].address);
    printf("Previous Rentals: %d\n", customers[ci].total_rentals);
    printf("------------------------\n");
    int carid;
    printf("\nEnter Car ID to rent: ");
    if(scanf("%d", &carid) != 1) 
    {
        clearBuffer();
        printf("\n*** Error: Invalid Car ID! ***\n");
        pauseScreen();
        return;
    }
    clearBuffer();
    int carind = searchCar(carid);
    if(carind == -1) 
    {
        printf("\n*** Error: Car ID %d not found! ***\n", carid);
        pauseScreen();
        return;
    }
    if(cars[carind].is_rented == 1) 
    {
        printf("\n*** Error: Car is already rented! ***\n");
        printf("Car: %s %s\n", cars[carind].brand, cars[carind].model);
        pauseScreen();
        return;
    }
    printf("\n--- Selected Car Details ---\n");
    printf("Brand: %s\n", cars[carind].brand);
    printf("Model: %s\n", cars[carind].model);
    printf("Rent per Day: Rs. %.2f\n", cars[carind].rent_per_day);
    printf("----------------------------\n");
    int d;
    printf("\nEnter Number of Days: ");
    if(scanf("%d", &d) != 1) 
    {
        clearBuffer();
        printf("\n*** Error: Invalid number of days! ***\n");
        pauseScreen();
        return;
    }
    clearBuffer();
    if(d <= 0) 
    {
        printf("\n*** Error: Days must be greater than 0! ***\n");
        pauseScreen();
        return;
    }
    struct Rental nr;
    nr.rental_id = rental_count + 1;
    nr.customer_id = cid;
    nr.car_id = carid;
    nr.days = d;
    nr.total_cost = d * cars[carind].rent_per_day;
    nr.is_returned = 0;
    cars[carind].is_rented = 1;
    customers[ci].total_rentals++;
    rentals[rental_count] = nr;
    rental_count++;
    printf("\n========================================\n");
    printf("  Car Rented Successfully!\n");
    printf("========================================\n");
    printf("Rental ID: %d\n", nr.rental_id);
    printf("Customer: %s (ID: %d)\n", customers[ci].name, cid);
    printf("Car: %s %s (ID: %d)\n", cars[carind].brand, cars[carind].model, carid);
    printf("Days: %d\n", d);
    printf("Estimated Cost: Rs. %.2f\n", nr.total_cost);
    printf("========================================\n");
    printf("\nThis customer can rent more cars using same ID: %d\n", cid);
    pauseScreen();
}
void returnCar() 
{
    system("cls");
    printf("\n========================================\n");
    printf("          RETURN A CAR\n");
    printf("========================================\n");
    int carid;
    printf("\nEnter Car ID to return: ");
    if(scanf("%d", &carid) != 1) 
    {
        clearBuffer();
        printf("\n*** Error: Invalid Car ID! ***\n");
        pauseScreen();
        return;
    }
    clearBuffer();
    int carind = searchCar(carid);
    if(carind == -1) 
    {
        printf("\n*** Error: Car ID %d not found! ***\n", carid);
        pauseScreen();
        return;
    }
    if(cars[carind].is_rented == 0)
    {
        printf("\n*** Error: This car is not currently rented! ***\n");
        printf("Car: %s %s\n", cars[carind].brand, cars[carind].model);
        pauseScreen();
        return;
    }
    int rind = -1;
    int i = 0;
    while(i < rental_count) 
    {
        if(rentals[i].car_id == carid && rentals[i].is_returned == 0) 
        {
            rind = i;
            break;
        }
        i++;
    }
    if(rind == -1) 
    {
        printf("\n*** Error: Rental record not found! ***\n");
        pauseScreen();
        return;
    }
    int ci = findCustomerById(rentals[rind].customer_id);
    if(ci == -1) 
    {
        printf("\n*** Error: Customer record not found! ***\n");
        pauseScreen();
        return;
    }
    printf("\n");
    printf("================================================\n");
    printf("            RENTAL BILL INVOICE\n");
    printf("================================================\n");
    printf("Rental ID        : %d\n", rentals[rind].rental_id);
    printf("------------------------------------------------\n");
    printf("Customer ID      : %d\n", customers[ci].id);
    printf("Customer Name    : %s\n", customers[ci].name);
    printf("Phone Number     : %s\n", customers[ci].phone);
    printf("Address          : %s\n", customers[ci].address);
    printf("------------------------------------------------\n");
    printf("Car ID           : %d\n", cars[carind].id);
    printf("Car              : %s %s\n", cars[carind].brand, cars[carind].model);
    printf("------------------------------------------------\n");
    printf("Days Rented      : %d days\n", rentals[rind].days);
    printf("Rent per Day     : Rs. %.2f\n", cars[carind].rent_per_day);
    printf("------------------------------------------------\n");
    printf("TOTAL AMOUNT     : Rs. %.2f\n", rentals[rind].total_cost);
    printf("================================================\n");
    cars[carind].is_rented = 0;
    rentals[rind].is_returned = 1;
    printf("\n*** Car returned successfully! ***\n");
    printf("*** Payment of Rs. %.2f received! ***\n", rentals[rind].total_cost);
    pauseScreen();
}
float calcRevenue(int idx, int type, float sum) 
{
    if(idx >= rental_count)
        return sum;
    if(type == 1 && rentals[idx].is_returned == 1)
        return calcRevenue(idx + 1, type, sum + rentals[idx].total_cost);
    if(type == 0 && rentals[idx].is_returned == 0)
        return calcRevenue(idx + 1, type, sum + rentals[idx].total_cost);
    return calcRevenue(idx + 1, type, sum);
}
int countRentals(int idx, int type, int cnt)
{
    if(idx >= rental_count)
        return cnt;
    if(type == 1 && rentals[idx].is_returned == 1)
        return countRentals(idx + 1, type, cnt + 1);
    if(type == 0 && rentals[idx].is_returned == 0)
        return countRentals(idx + 1, type, cnt + 1);
    return countRentals(idx + 1, type, cnt);
}
void displayRevenue() 
{
    system("cls");
    printf("\n========================================\n");
    printf("       REVENUE & EARNINGS REPORT\n");
    printf("========================================\n");
    float te = calcRevenue(0, 1, 0.0);
    int rt = countRentals(0, 1, 0);
    float ee = calcRevenue(0, 0, 0.0);
    int ar = countRentals(0, 0, 0);
    printf("\n--- TODAY'S EARNINGS ---\n");
    printf("Total Returns Today     : %d\n", rt);
    printf("Cash Received Today     : Rs. %.2f\n", te);
    printf("\n--- ESTIMATED EARNINGS ---\n");
    printf("Active Rentals          : %d\n", ar);
    printf("Expected Revenue        : Rs. %.2f\n", ee);
    printf("\n--- TOTAL SUMMARY ---\n");
    printf("Total Revenue (Today)   : Rs. %.2f\n", te);
    printf("Pending Revenue         : Rs. %.2f\n", ee);
    printf("Combined Total          : Rs. %.2f\n", te + ee);
    printf("========================================\n");
    if(rt > 0) 
    {
        printf("\n--- RETURNED CARS TODAY ---\n");
        printf("%-8s %-20s %-15s %-10s\n", "Rent.ID", "Customer", "Car", "Amount");
        printf("------------------------------------------------------------\n");
        int i = 0;
        while(i < rental_count) 
        {
            if(rentals[i].is_returned == 1) 
            {
                int carind = searchCar(rentals[i].car_id);
                int ci = findCustomerById(rentals[i].customer_id);
                if(carind != -1 && ci != -1) 
                {
                    char cn[30];
                    snprintf(cn, sizeof(cn), "%s %s", cars[carind].brand, cars[carind].model);
                    printf("%-8d %-20s %-15s Rs. %.2f\n", rentals[i].rental_id, customers[ci].name, cn, rentals[i].total_cost);
                }
            }
            i++;
        }
        printf("------------------------------------------------------------\n");
    }
    if(ar > 0) 
    {
        printf("\n--- ACTIVE RENTALS (PENDING) ---\n");
        printf("%-8s %-20s %-15s %-10s\n", "Rent.ID", "Customer", "Car", "Expected");
        printf("------------------------------------------------------------\n");
        int i = 0;
        while(i < rental_count) 
        {
            if(rentals[i].is_returned == 0) {
                int carind = searchCar(rentals[i].car_id);
                int ci = findCustomerById(rentals[i].customer_id);
                if(carind != -1 && ci != -1) 
                {
                    char cn[30];
                    snprintf(cn, sizeof(cn), "%s %s", cars[carind].brand, cars[carind].model);
                    printf("%-8d %-20s %-15s Rs. %.2f\n", rentals[i].rental_id, customers[ci].name, cn, rentals[i].total_cost);
                }
            }
            i++;
        }
        printf("------------------------------------------------------------\n");
    }    
    pauseScreen();
}