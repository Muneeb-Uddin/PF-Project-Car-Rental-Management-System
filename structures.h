#ifndef STRUCTURES_H
#define STRUCTURES_H
#define MAX_CARS 50
#define MAX_CUSTOMERS 50
#define MAX_RENTALS 100
struct Car {
    int id;
    char brand[30];
    char model[30];
    float rent_per_day;
    int is_rented;
};
struct Customer {
    int id;
    char name[50];
    char phone[15];
    char address[100];
    int total_rentals;
};
struct Rental {
    int rental_id;
    int customer_id;
    int car_id;
    int days;
    float total_cost;
    int is_returned;
};
extern struct Car cars[MAX_CARS];
extern struct Customer customers[MAX_CUSTOMERS];
extern struct Rental rentals[MAX_RENTALS];
extern int car_count;
extern int customer_count;
extern int rental_count;
/*
The keyword extern means the real array is declared somewhere else and we can change it from here too
*/
#endif