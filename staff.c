#include <stdio.h>
#include "staff.h"
#include "doctor.h"
#include "nurse.h"
#include "ward_member.h"

void staff_menu() {
    int choice;

    do {
        printf("\n--- Staff Management ---\n");
        printf("1. Doctor Management\n");
        printf("2. Nurse Management\n");
        printf("3. Ward Member Management\n");
        printf("4. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: doctor_menu(); break;
            case 2: nurse_menu(); break;
            case 3: ward_member_menu(); break;
            case 4: break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
}
