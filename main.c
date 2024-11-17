#include <stdio.h>
#include <string.h> 
#include "patient.h"
#include "appointment.h"
#include "billing.h"
#include "staff.h"


int main() {
    int role;
    char pswd[20];
    int exit_program = 0;
    int choice;

    do {
        printf("\n--- Main Menu ---\n");
        printf("Enter your role (1 for Manager/2 for Receptionist/3 for User/0 for quit): ");
        scanf("%d", &role);

        if (role == 0) {
            printf("Exiting the program.\n");
            exit_program = 1;
            break;
        }

        if (role == 3) {
            printf("You are logged in as User.\n");
            do {
            printf("1. Add patient\n");
            printf("2. exit\n");
            printf("enter your choice: ");
            scanf("%d", &choice);
                switch (choice) {
                    case 1: user_patient(); break;
                    case 2: break;
                    default: printf("Invalid choice. Please try again.\n");
                }
            } while (choice != 2);
        } 
        
        else if (role == 1) {
            printf("Enter password: ");
            scanf("%s", pswd);
            if (strcmp(pswd, "M@6205") == 0) {
                printf("Password accepted. ");
                printf("You are logged in as Manager.Full access granted.\n");
                do {
                    printf("1. Staff management\n");
                    printf("2. Patient management\n");
                    printf("3. Appointment management\n");
                    printf("4. Billing management\n");
                    printf("5. Exit\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);
                    switch (choice) {
                        case 1: staff_menu(); break;
                        case 2: patient_menu(); break;
                        case 3: appointment_menu(); break;
                        case 4: billing_menu(); break;
                        case 5: break;
                        default: printf("Invalid choice. Please try again.\n");
                    }
                } while (choice != 5);
            }   
            else {
                printf("Incorrect password for manager.\n");
            }
        } 

        else if (role== 2) {
            printf("Enter password for receptionist:- ");
            scanf("%s", pswd);
            if (strcmp(pswd, "R@6205") == 0) {
                printf("Password accepted. ");
                printf("You are logged in as receptionist.Partial access granted.\n");
                do {
                    printf("1. Patient management\n");
                    printf("2. Appointment management\n");
                    printf("3. Billing management\n");
                    printf("4. Exit\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);
                    switch (choice) {
                        case 1: patient_menu(); break;
                        case 2: appointment_menu(); break;
                        case 3: billing_menu(); break;
                        case 4: break;
                        default: printf("Invalid choice. Please try again.\n");
                    }
                } while (choice != 4);
                } 
                else {
                     printf("Incorrect password for receptionist.\n");
                }
        }

        else {
            printf("Invalid role entered. Please try again.\n");
        }

    } while (!exit_program);

    return 0;
}
