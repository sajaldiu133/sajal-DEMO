#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// --- Constants ---
#define MAX_SERVICES 100
#define MAX_BOOKINGS 100
#define MAX_GOALS 100
#define ADMIN_PASSWORD "s@jal"
#define LOW_ATTENDANCE_THRESHOLD 3

// --- Data Structure (Structs) ---
struct Service {
    char id[20];
    char name[50];
    float price;
    int seats;
    float totalRatingScore;
    int ratingCount;
};

struct Booking {
    char memberName[50];
    char serviceId[20];
    char status[20]; // 'Pending', 'Confirmed', 'Cancelled'
};

struct MemberGoal {
    char name[50];
    char goal[100];
};

// --- Global Arrays (Data Storage) ---
struct Service serviceList[MAX_SERVICES];
int totalServices = 0;

struct Booking bookingList[MAX_BOOKINGS];
int totalBookings = 0;

struct MemberGoal goalList[MAX_GOALS];
int totalGoals = 0;


// --- Function Prototypes ---
void adminPanel();
void memberPanel();
int findServiceIndex(char *id);

void addService();
void displayServices();
void deleteService();
void updateService();
void manageBookingsAndWarnings();
void adminSearchService();

void searchService();
void bookService();
void showMyBookings();
void cancelBooking();
void updateWellnessGoal();
void rateService();


// --- MAIN FUNCTION (Switch & Function Call Used) ---
int main() {
    int choice;

    // Initial Data Setup
    strcpy(serviceList[0].id, "HHH001"); strcpy(serviceList[0].name, "Yoga_Classes");
    serviceList[0].price = 800.0; serviceList[0].seats = 10;
    serviceList[0].totalRatingScore = 0.0; serviceList[0].ratingCount = 0; totalServices++;

    strcpy(serviceList[1].id, "HHH002"); strcpy(serviceList[1].name, "Nutrition_Plans");
    serviceList[1].price = 1500.0; serviceList[1].seats = 5;
    serviceList[1].totalRatingScore = 0.0; serviceList[1].ratingCount = 0; totalServices++;

    strcpy(serviceList[2].id, "HHH003"); strcpy(serviceList[2].name, "Mental_Health_Checkups");
    serviceList[2].price = 2000.0; serviceList[2].seats = 3;
    serviceList[2].totalRatingScore = 0.0; serviceList[2].ratingCount = 0; totalServices++;

    strcpy(serviceList[3].id, "HHH004"); strcpy(serviceList[3].name, "Fitness_Programs");
    serviceList[3].price = 1200.0; serviceList[3].seats = 12;
    serviceList[3].totalRatingScore = 0.0; serviceList[3].ratingCount = 0; totalServices++;

    while(1) { // Loop Used
        printf("\n====================================\n");
        printf("      HARMONY HEALTH HUB SYSTEM     \n");
        printf("====================================\n");
        printf("1. Admin Login\n");
        printf("2. Member Panel\n");
        printf("3. Exit\n");
        printf("------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch(choice) { // Switch Used
            case 1: adminPanel(); break;
            case 2: memberPanel(); break;
            case 3:
                printf("Exiting System...\n");
                exit(0);
            default:
                printf("Invalid Choice!\n");
        }
    }
    return 0;
}

// ================= UTILITY FUNCTION (Function & Loop Used) =================
int findServiceIndex(char *id) {
    for(int i = 0; i < totalServices; i++) { // Loop Used
        if(strcmp(serviceList[i].id, id) == 0) {
            return i;
        }
    }
    return -1;
}

// ================= ADMIN SECTION (Functions, Switch & Loops Used) =================

void adminPanel() {
    char pass[20];
    printf("\n--- Admin Verification ---\n");
    printf("Enter Password: ");
    scanf("%s", pass);

    if(strcmp(pass, ADMIN_PASSWORD) != 0) {
        printf("\n[X] Access Denied! Wrong Password.\n");
        return;
    }

    int choice;
    while(1) { // Loop Used
        printf("\n>> ADMIN MENU <<\n");
        printf("1. Add New Service\n");
        printf("2. Display All Services\n");
        printf("3. Delete a Service\n");
        printf("4. Update Service Details\n");
        printf("5. Check Bookings & Warnings\n");
        printf("6. Search Service\n");
        printf("7. Back to Main Menu\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch(choice) { // Switch Used
            case 1: addService(); break;
            case 2: displayServices(); break;
            case 3: deleteService(); break;
            case 4: updateService(); break;
            case 5: manageBookingsAndWarnings(); break;
            case 6: adminSearchService(); break;
            case 7: return;
            default: printf("Invalid option!\n");
        }
    }
}

void addService() {
    if(totalServices >= MAX_SERVICES) { printf("\nMemory Full!\n"); return; }
    printf("\n--- Add New Service ---\n");
    printf("Enter Service ID: "); scanf("%s", serviceList[totalServices].id);
    printf("Enter Service Name (Use_Underscore_For_Space): "); scanf("%s", serviceList[totalServices].name);
    printf("Enter Price: "); scanf("%f", &serviceList[totalServices].price);
    printf("Enter Available Seats: "); scanf("%d", &serviceList[totalServices].seats);
    serviceList[totalServices].totalRatingScore = 0.0;
    serviceList[totalServices].ratingCount = 0;
    totalServices++;
    printf("\n[V] Service Added Successfully!\n");
}

void displayServices() {
    if (totalServices == 0) { printf("\nNo services available yet.\n"); return; }
    printf("\n------------------------------------------------------------------------\n");
    printf("%-10s %-25s %-10s %-10s %-15s\n", "ID", "Name", "Price", "Seats", "Avg. Rating");
    printf("------------------------------------------------------------------------\n");
    for(int i = 0; i < totalServices; i++) { // Loop Used
        float avgRating = (serviceList[i].ratingCount > 0) ? (serviceList[i].totalRatingScore / serviceList[i].ratingCount) : 0.0;
        printf("%-10s %-25s %-10.2f %-10d %-15.1f\n",
               serviceList[i].id, serviceList[i].name, serviceList[i].price, serviceList[i].seats, avgRating);
    }
    printf("------------------------------------------------------------------------\n");
}

void deleteService() {
    char targetId[20]; int foundIndex = -1;
    displayServices();
    printf("\nEnter Service ID to Delete: "); scanf("%s", targetId);
    foundIndex = findServiceIndex(targetId);

    if(foundIndex != -1) {
        for(int i = foundIndex; i < totalServices - 1; i++) { serviceList[i] = serviceList[i+1]; } // Loop Used
        totalServices--;
        printf("\n[V] Service Deleted Successfully!\n");
    } else {
        printf("\n[X] ID Not Found!\n");
    }
}

void updateService() {
    char targetId[20]; int foundIndex; int updateChoice;
    displayServices();
    printf("\n--- Update Service Details ---\n");
    printf("Enter Service ID to Update: "); scanf("%s", targetId);
    foundIndex = findServiceIndex(targetId);
    if(foundIndex != -1) {
        printf("Service found: %s\n", serviceList[foundIndex].name);
        printf("What to update?\n1. Price\n2. Seats\nChoice: "); scanf("%d", &updateChoice);
        if(updateChoice == 1) {
            printf("Enter New Price: "); scanf("%f", &serviceList[foundIndex].price);
            printf("[V] Price updated successfully!\n");
        } else if (updateChoice == 2) {
            printf("Enter New Available Seats: "); scanf("%d", &serviceList[foundIndex].seats);
            printf("[V] Seats updated successfully!\n");
        } else {
            printf("[X] Invalid update choice.\n");
        }
    } else {
        printf("[X] Service ID Not Found!\n");
    }
}

void manageBookingsAndWarnings() {
    char action; int serviceIndex = -1;

    // 1. Low-Attendance Warnings (Loop Used)
    printf("\n\n--- 1. Low Attendance Warnings ---\n");
    int warningFound = 0;
    for(int i = 0; i < totalServices; i++) {
        if(serviceList[i].seats <= LOW_ATTENDANCE_THRESHOLD) {
            printf("⚠️ WARNING: %s (%s) has only %d seats left.\n", serviceList[i].name, serviceList[i].id, serviceList[i].seats);
            warningFound = 1;
        }
    }
    if(!warningFound) printf("No low attendance warnings found.\n");


    // 2. Manage Pending Bookings (Loop Used)
    printf("\n\n--- 2. Manage Pending Bookings (Approve/Cancel) ---\n");
    int pendingFound = 0;
    for(int i = 0; i < totalBookings; i++) {
        if(strcmp(bookingList[i].status, "Pending") == 0) {
            printf("\nBooking Index: %d | Member: %s | Service ID: %s\n", i, bookingList[i].memberName, bookingList[i].serviceId);
            printf("Action (A=Approve / C=Cancel / N=Next): ");

            while (getchar() != '\n'); scanf(" %c", &action);

            if(action == 'A' || action == 'a') {
                serviceIndex = findServiceIndex(bookingList[i].serviceId);
                if (serviceIndex != -1 && serviceList[serviceIndex].seats > 0) {
                    strcpy(bookingList[i].status, "Confirmed");
                    serviceList[serviceIndex].seats--;
                    printf("[V] Booking Approved.\n");
                } else {
                    strcpy(bookingList[i].status, "Cancelled");
                    printf("[X] Cannot Approve (Fully Booked/Error). Status set to Cancelled.\n");
                }
            } else if (action == 'C' || action == 'c') {
                strcpy(bookingList[i].status, "Cancelled");
                printf("[V] Booking Cancelled by Admin.\n");
            }
            pendingFound = 1;
        }
    }
    if(!pendingFound) printf("No pending bookings to review.\n");
}

void adminSearchService() {
    char searchName[50]; int found = 0;
    printf("\n--- Admin Search Service ---\n");
    printf("Enter Name/Keyword to Search: "); scanf("%s", searchName);
    printf("\n--- Search Results ---\n");
    for(int i = 0; i < totalServices; i++) { // Loop Used
        if(strstr(serviceList[i].name, searchName) != NULL) {
            printf("Found: %s | Price: %.2f | Seats: %d | ID: %s\n",
                   serviceList[i].name, serviceList[i].price, serviceList[i].seats, serviceList[i].id);
            found = 1;
        }
    }
    if(!found) printf("No service found.\n");
}


// ================= MEMBER SECTION (Functions, Switch & Loops Used) =================

void memberPanel() {
    int choice;
    while(1) { // Loop Used
        printf("\n>> MEMBER MENU <<\n");
        printf("1. View Available Services\n");
        printf("2. Search for a Service\n");
        printf("3. Book a Service\n");
        printf("4. Cancel Booking\n");
        printf("5. Update Wellness Goal\n");
        printf("6. View My Booking History\n");
        printf("7. Rate a Service\n");
        printf("8. Back to Main Menu\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch(choice) { // Switch Used
            case 1: displayServices(); break;
            case 2: searchService(); break;
            case 3: bookService(); break;
            case 4: cancelBooking(); break;
            case 5: updateWellnessGoal(); break;
            case 6: showMyBookings(); break;
            case 7: rateService(); break;
            case 8: return;
            default: printf("Invalid option!\n");
        }
    }
}

void rateService() {
    char id[20]; char name[50]; int rating; int serviceIndex;

    printf("\n--- Rate a Service ---\n");
    printf("Enter Your Name: "); scanf("%s", name);
    printf("Enter Service ID to Rate: "); scanf("%s", id);

    serviceIndex = findServiceIndex(id);
    if (serviceIndex == -1) { printf("[X] Invalid Service ID!\n"); return; }

    printf("Enter your rating (1 to 5): ");
    if (scanf("%d", &rating) != 1 || rating < 1 || rating > 5) {
        printf("[X] Invalid rating input. Must be 1-5.\n");
        while (getchar() != '\n');
        return;
    }

    serviceList[serviceIndex].totalRatingScore += rating;
    serviceList[serviceIndex].ratingCount++;

    printf("\n[V] Thank you, %s! Your rating of %d for %s has been recorded.\n",
           name, rating, serviceList[serviceIndex].name);
}

void updateWellnessGoal() {
    char name[50]; char goal[100]; int foundIndex = -1;

    printf("\n--- Update Wellness Goal ---\n");
    printf("Enter Your Name: "); scanf("%s", name);

    for(int i = 0; i < totalGoals; i++) { // Loop Used
        if(strcmp(goalList[i].name, name) == 0) {
            foundIndex = i;
            break;
        }
    }

    printf("Enter Your New Goal (e.g., fitness_improvement): "); scanf("%s", goal);

    if (foundIndex != -1) {
        strcpy(goalList[foundIndex].goal, goal);
        printf("[V] Goal updated successfully! New Goal: %s\n", goal);
    } else if (totalGoals < MAX_GOALS) {
        strcpy(goalList[totalGoals].name, name);
        strcpy(goalList[totalGoals].goal, goal);
        totalGoals++;
        printf("[V] New goal set successfully! Goal: %s\n", goal);
    } else {
        printf("[X] Cannot save new goal (System capacity full).\n");
    }
}

void bookService() {
    char id[20]; char name[50]; int foundIndex = -1;

    displayServices();
    printf("\nEnter Service ID to Book: "); scanf("%s", id);
    foundIndex = findServiceIndex(id);

    if(foundIndex != -1) {
        if(serviceList[foundIndex].seats > 0) {
            if(totalBookings >= MAX_BOOKINGS) { printf("\n[X] Booking system full.\n"); return; }

            printf("Enter Your Name: "); scanf("%s", name);

            strcpy(bookingList[totalBookings].memberName, name);
            strcpy(bookingList[totalBookings].serviceId, id);
            strcpy(bookingList[totalBookings].status, "Pending");
            totalBookings++;

            printf("\n[V] Booking Request Submitted successfully for %s! Awaiting Admin Approval.\n", serviceList[foundIndex].name);
        } else {
            printf("\n[X] Sorry, No Seats Available!\n");
        }
    } else {
        printf("\n[X] Invalid Service ID!\n");
    }
}

void cancelBooking() {
    char name[50]; char serviceId[20]; int foundBookingIndex = -1; int serviceIndex = -1;

    printf("\n--- Cancel Booking ---\n");
    printf("Enter Your Name (as booked): "); scanf("%s", name);
    printf("Enter Service ID to Cancel: "); scanf("%s", serviceId);

    for(int i = 0; i < totalBookings; i++) { // Loop Used
        if(strcmp(bookingList[i].memberName, name) == 0 &&
           strcmp(bookingList[i].serviceId, serviceId) == 0 &&
           strcmp(bookingList[i].status, "Cancelled") != 0) {
            foundBookingIndex = i; break;
        }
    }

    if(foundBookingIndex != -1) {
        if (strcmp(bookingList[foundBookingIndex].status, "Confirmed") == 0) {
            serviceIndex = findServiceIndex(serviceId);
            if (serviceIndex != -1) { serviceList[serviceIndex].seats++; }
        }

        for(int i = foundBookingIndex; i < totalBookings - 1; i++) { bookingList[i] = bookingList[i+1]; } // Loop Used
        totalBookings--;

        printf("\n[V] Booking for %s successfully cancelled.\n", serviceId);
    } else {
        printf("\n[X] Booking not found or already cancelled.\n");
    }
}

void showMyBookings() {
    char name[50]; int found = 0;
    printf("\nEnter Your Name to view history: "); scanf("%s", name);

    printf("\n--- Booking History for %s ---\n", name);
    for(int i = 0; i < totalBookings; i++) { // Loop Used
        if(strcmp(bookingList[i].memberName, name) == 0) {
            printf("- Service ID: %s | Status: %s\n", bookingList[i].serviceId, bookingList[i].status);
            found = 1;
        }
    }
    if(!found) printf("No booking records found.\n");
}

void searchService() {
    char searchName[50]; int found = 0;
    printf("\nEnter Name/Keyword to Search: "); scanf("%s", searchName);
    printf("\n--- Search Results ---\n");
    for(int i = 0; i < totalServices; i++) { // Loop Used
        if(strstr(serviceList[i].name, searchName) != NULL) {
            printf("Found: %s | Price: %.2f | Seats: %d\n",
                   serviceList[i].name, serviceList[i].price, serviceList[i].seats);
            found = 1;
        }
    }
    if(!found) printf("No service found.\n");
}
