#include "structures.h"
#include "utils.h"
#include "car_operations.h"
#include "customer_operations.h"
int findCustomer(int cid, int index) 
{
    if(index >= customer_count)
        return -1;
    if(customers[index].id == cid)
        return index;
    return findCustomer(cid, index + 1);
}
int findCustomerById(int customer_id) {
    return findCustomer(customer_id, 0);
}
void registerNewCustomer() 
{
    system("cls");
    printf("\n========================================\n");
    printf("       REGISTER NEW CUSTOMER\n");
    printf("========================================\n");
    if(customer_count >= MAX_CUSTOMERS) 
    {
        printf("\n*** Error: Customer storage is full! ***\n");
        pauseScreen();
        return;
    }
    struct Customer nc; //New customer
    printf("\nEnter Customer ID (Unique Number): ");
    if(scanf("%d", &nc.id) != 1) 
    {
        clearBuffer();
        printf("\n*** Error: Invalid ID! ***\n");
        pauseScreen();
        return;
    }
    clearBuffer();
    if(findCustomerById(nc.id) != -1) 
    {
        printf("\n*** Error: Customer ID %d already exists! ***\n", nc.id);
        pauseScreen();
        return;
    }
    printf("Enter Full Name: ");
    fgets(nc.name, sizeof(nc.name), stdin);
    nc.name[strcspn(nc.name, "\n")] = 0;
    if(strlen(nc.name) == 0) 
    {
        printf("\n*** Error: Name cannot be empty! ***\n");
        pauseScreen();
        return;
    }
    printf("Enter Phone Number (e.g. 03001234567): ");
    fgets(nc.phone, sizeof(nc.phone), stdin);
    nc.phone[strcspn(nc.phone, "\n")] = 0;
    printf("Enter Address: ");
    fgets(nc.address, sizeof(nc.address), stdin);
    nc.address[strcspn(nc.address, "\n")] = 0;
    nc.total_rentals = 0;
    customers[customer_count] = nc;
    customer_count++;
    printf("\n========================================\n");
    printf("  Customer Registered Successfully!\n");
    printf("========================================\n");
    printf("Customer ID: %d\n", nc.id);
    printf("Name: %s\n", nc.name);
    printf("Phone: %s\n", nc.phone);
    printf("Address: %s\n", nc.address);
    printf("\nThis customer can now rent cars using ID: %d\n", nc.id);
    pauseScreen();
}
void searchCarDetails() 
{
    system("cls");
    printf("\n========================================\n");
    printf("          SEARCH CAR\n");
    printf("========================================\n");
    int cid;
    printf("\nEnter Car ID to search: ");
    if(scanf("%d", &cid) != 1) 
    {
        clearBuffer();
        printf("\n*** Error: Invalid Car ID! ***\n");
        pauseScreen();
        return;
    }
    clearBuffer();
    int found = searchCar(cid);
    if(found == -1) 
    {
        printf("\n*** Car ID %d not found! ***\n", cid);
        pauseScreen();
        return;
    }
    printf("\n========================================\n");
    printf("          CAR DETAILS\n");
    printf("========================================\n");
    printf("Car ID           : %d\n", cars[found].id);
    printf("Brand            : %s\n", cars[found].brand);
    printf("Model            : %s\n", cars[found].model);
    printf("Rent per Day     : Rs. %.2f\n", cars[found].rent_per_day);
    printf("Status           : %s\n", cars[found].is_rented ? "RENTED" : "AVAILABLE");
    if(cars[found].is_rented == 1) 
    {
        printf("\n--- Currently Rented By ---\n");
        int i = 0;
        while(i < rental_count) 
        {
            if(rentals[i].car_id == cid && rentals[i].is_returned == 0) 
            {
                int ci = findCustomerById(rentals[i].customer_id);
                if(ci != -1) 
                {
                    printf("Customer ID   : %d\n", customers[ci].id);
                    printf("Customer Name : %s\n", customers[ci].name);
                    printf("Phone         : %s\n", customers[ci].phone);
                    printf("Days          : %d\n", rentals[i].days);
                    printf("Expected Cost : Rs. %.2f\n", rentals[i].total_cost);
                }
                break;
            }
            i++;
        }
    }
    printf("========================================\n");
    pauseScreen();
}
void displayAllCustomers() 
{
    system("cls");
    printf("\n========================================\n");
    printf("       ALL CUSTOMERS (SUMMARY)\n");
    printf("========================================\n");
    if(customer_count == 0) 
    {
        printf("\n*** No customers registered! ***\n");
        pauseScreen();
        return;
    }
    printf("\nTotal Customers: %d\n\n", customer_count);
    printf("%-6s %-25s %-15s %-8s %-10s\n", 
           "ID", "Name", "Phone", "Rentals", "Status");
    printf("-----------------------------------------------------------------------\n");
    int i = 0;
    while(i < customer_count) 
    {
        int ar = 0;
        int j = 0;
        while(j < rental_count) 
        {
            if(rentals[j].customer_id == customers[i].id && rentals[j].is_returned == 0)
                ar++;
            j++;
        }
        char st[15];
        if(ar > 0) 
            sprintf(st, "Active (%d)", ar);
        else if(customers[i].total_rentals > 0) 
            strcpy(st, "Regular");
        else
            strcpy(st, "New");
        printf("%-6d %-25s %-15s %-8d %-10s\n", customers[i].id, customers[i].name, customers[i].phone, customers[i].total_rentals, st);
        i++;
    }
    printf("-----------------------------------------------------------------------\n");
    printf("\nOptions:\n");
    printf("  Enter Customer ID to view details\n");
    printf("  Enter 0 to go back\n");
    printf("\nYour choice: ");
    int ch;
    if(scanf("%d", &ch) != 1) {
        clearBuffer();
        printf("\n*** Invalid input! ***\n");
        pauseScreen();
        return;
    }
    clearBuffer();
    if(ch == 0)
        return;
    int ci = findCustomerById(ch);
    if(ci == -1) 
    {
        printf("\n*** Customer ID %d not found! ***\n", ch);
        pauseScreen();
        return;
    }
    displayCustomerDetails(ci);
}

void displayCustomerDetails(int ci) 
{
    system("cls");
    printf("\n========================================\n");
    printf("      CUSTOMER DETAILED VIEW\n");
    printf("========================================\n");
    printf("\n--- CUSTOMER INFORMATION ---\n");
    printf("ID      : %d\n", customers[ci].id);
    printf("Name    : %s\n", customers[ci].name);
    printf("Phone   : %s\n", customers[ci].phone);
    printf("Address : %s\n", customers[ci].address);
    int tr = 0;
    int ar = 0;
    int cr = 0;
    float ts = 0.0;
    float pa = 0.0;
    int i = 0;
    do 
    {
        if(rentals[i].customer_id == customers[ci].id) 
        {
            tr++;
            if(rentals[i].is_returned == 0) 
            {
                ar++;
                pa += rentals[i].total_cost;
            } 
            else 
            {
                cr++;
                ts += rentals[i].total_cost;
            }
        }
        i++;
    } 
    while(i < rental_count);
    printf("\n--- RENTAL STATISTICS ---\n");
    printf("Total Rentals     : %d\n", tr);
    printf("Completed         : %d\n", cr);
    printf("Active/Ongoing    : %d\n", ar);
    printf("Total Spent       : Rs. %.2f\n", ts);
    printf("Pending Payment   : Rs. %.2f\n", pa);
    if(ar > 0) 
    {
        printf("\n--- ACTIVE RENTALS ---\n");
        printf("%-10s %-20s %-8s %-12s\n", "Rental ID", "Car", "Days", "Amount");
        printf("-------------------------------------------------------\n");
        int i = 0;
        while(i < rental_count) 
        {
            if(rentals[i].customer_id == customers[ci].id && rentals[i].is_returned == 0) 
               {
                int cind = searchCar(rentals[i].car_id);
                if(cind != -1) 
                {
                    char cn[30];
                    snprintf(cn, sizeof(cn), "%s %s", cars[cind].brand, cars[cind].model);
                    printf("%-10d %-20s %-8d Rs. %.2f\n", rentals[i].rental_id, cn, rentals[i].days, rentals[i].total_cost);
                }
            }
            i++;
        }
        printf("-------------------------------------------------------\n");
    }
    if(cr > 0) 
    {
        printf("\n--- RENTAL HISTORY (Last %d) ---\n", cr > 5 ? 5 : cr);
        printf("%-10s %-20s %-8s %-12s\n", "Rental ID", "Car", "Days", "Paid");
        printf("-------------------------------------------------------\n");
        int cnt = 0;
        int i = rental_count - 1;
        while(i >= 0 && cnt < 5) 
        {
            if(rentals[i].customer_id == customers[ci].id && rentals[i].is_returned == 1) 
               {
                int cind = searchCar(rentals[i].car_id);
                if(cind != -1) 
                {
                    char cn[30];
                    snprintf(cn, sizeof(cn), "%s %s", cars[cind].brand, cars[cind].model);
                    printf("%-10d %-20s %-8d Rs. %.2f\n", rentals[i].rental_id, cn, rentals[i].days, rentals[i].total_cost);
                    cnt++;
                }
            }
            i--;
        }
        printf("-------------------------------------------------------\n");
    }
    if(tr == 0)
        printf("\n*** No rental history for this customer ***\n");
    printf("\n========================================\n");
    pauseScreen();
}