#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "billing.h"
#include "patient.h"

#define MAX_LINE_LENGTH 1024
#define PATIENT_FILE "patients.csv"
#define BILLING_FILE "billing.csv"

int is_patient_id_valid(const char* patient_id) {
    FILE *fp = fopen(PATIENT_FILE, "r");
    char line[MAX_LINE_LENGTH];
    struct Patient p;

    if (fp == NULL) {
        printf("Error: can't open patient file.\n");
        return 0;
    }

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        sscanf(line, "%[^,],%[^,],%d", p.id, p.name, &p.age);
        if (strcmp(p.id, patient_id) == 0) {
            fclose(fp);
            return 1; 
        }
    }

    fclose(fp);
    return 0; 
}

void generate_bill() {
    struct Bill b;
    char patient_name[50];
    FILE *fp = fopen(BILLING_FILE, "a");

    if (fp == NULL) {
        printf("Error: can't open billing file.\n");
        return;
    }

    printf("Enter Bill ID: ");
    scanf("%s", b.id);

    printf("Enter Patient ID: ");
    scanf("%s", b.patient_id);
    
    if (!is_patient_id_valid(b.patient_id)) {
        printf("Error: Patient ID %s does not exist. Bill generation failed.\n", b.patient_id);
        fclose(fp);
        return;
    }

    if (!get_patient_name(b.patient_id, patient_name)) {
        printf("Error: Unable to retrieve patient name for ID: %s. Bill generation failed.\n", b.patient_id);
        fclose(fp);
        return;
    }

    int days;
    printf("Enter number of days the patient is hospitalized: ");
    scanf("%d", &days);
    int hosp_cost = 50 * days;

    float med_price;
    printf("Enter total price of medicines: ");
    scanf("%f", &med_price);

    float care_price;
    printf("Enter amount for care services or any additional operations: ");
    scanf("%f", &care_price);

    b.amount = med_price + care_price + hosp_cost;

    fprintf(fp, "%s,%s,%s,%.2f\n", b.id, b.patient_id, patient_name, b.amount);
    fclose(fp);

    printf("Bill generated successfully for Patient: %s!\n", patient_name);
}

void delete_bill() {
    char bill_id[20], line[MAX_LINE_LENGTH], temp_file[] = "temp_billing.csv";
    struct Bill b;
    char patient_name[50];
    int found = 0;

    FILE *fp = fopen(BILLING_FILE, "r");
    FILE *temp_fp = fopen(temp_file, "w");

    if (fp == NULL || temp_fp == NULL) {
        printf("Error: can't open file.\n");
        return;
    }

    printf("Enter Bill ID to delete: ");
    scanf("%s", bill_id);

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        sscanf(line, "%[^,],%[^,],%[^,],%f", b.id, b.patient_id, patient_name, &b.amount);

        if (strcmp(b.id, bill_id) != 0) {
            fprintf(temp_fp, "%s,%s,%s,%.2f\n", b.id, b.patient_id, patient_name, b.amount);
        } else {
            found = 1; 
        }
    }

    fclose(fp);
    fclose(temp_fp);

    if (found) {
        if (remove(BILLING_FILE) == 0) {
            if (rename(temp_file, BILLING_FILE) == 0) {
                printf("Bill with ID %s deleted successfully!\n", bill_id);
            } else {
                printf("Error: Unable to rename the temporary file.\n");
            }
        } else {
            printf("Error: Unable to delete the old billing file.\n");
        }
    } else {
        printf("No bill found with ID: %s\n", bill_id);
        remove(temp_file); 
    }
}


void search_bill() {
    char search_query[50], line[MAX_LINE_LENGTH], choice;
    struct Bill b;
    char patient_name[50];
    int found = 0;

    FILE *bill_fp = fopen(BILLING_FILE, "r");
    FILE *patient_fp;

    if (bill_fp == NULL) {
        printf("Error: can't open billing file.\n");
        return;
    }

    printf("Search by (I)D or (N)ame: ");
    scanf(" %c", &choice);

    if (choice == 'I' || choice == 'i') {
        printf("Enter Patient ID or Bill ID to search: ");
        scanf("%s", search_query);

        while (fgets(line, sizeof(line), bill_fp) != NULL) {
            sscanf(line, "%[^,],%[^,],%[^,],%f", b.id, b.patient_id, patient_name, &b.amount);

            if (strcmp(b.id, search_query) == 0 || strcmp(b.patient_id, search_query) == 0) {
                found = 1;
                printf("\n--- Bill Details ---\n");
                printf("Bill ID: %s\nPatient ID: %s\nPatient Name: %s\nAmount: %.2f\n", b.id, b.patient_id, patient_name, b.amount);
                break;
            }
        }

    } 
    else if (choice == 'N' || choice == 'n') {
        printf("Enter Patient Name to search: ");
        scanf("%s", search_query);

        patient_fp = fopen(PATIENT_FILE, "r");
        if (patient_fp == NULL) {
            printf("Error: Unable to open patient file.\n");
            fclose(bill_fp);
            return;
        }

        while (fgets(line, sizeof(line), patient_fp) != NULL) {
            struct Patient p;
            sscanf(line, "%[^,],%[^,],%d", p.id, p.name, &p.age);

            if (strcmp(p.name, search_query) == 0) {
                printf("Patient Name: %s (ID: %s)\n", p.name, p.id);
                
                rewind(bill_fp);  
                while (fgets(line, sizeof(line), bill_fp) != NULL) {
                    sscanf(line, "%[^,],%[^,],%[^,],%f", b.id, b.patient_id, patient_name, &b.amount);
                    
                    if (strcmp(b.patient_id, p.id) == 0) {
                        found = 1;
                        printf("\n--- Bill Details ---\n");
                        printf("Bill ID: %s\nPatient ID: %s\nPatient Name: %s\nAmount: %.2f\n", b.id, b.patient_id, p.name, b.amount);
                    }
                }
            }
        }

        fclose(patient_fp);

    } else {
        printf("Invalid choice! Please select 'I' for ID or 'N' for Name.\n");
    }

    if (!found) {
        printf("No bills found for the given search criteria.\n");
    }

    fclose(bill_fp);
}


void display_bills() {
    struct Bill b;
    char patient_name[50];
    FILE *fp = fopen(BILLING_FILE, "r");
    char line[MAX_LINE_LENGTH];

    if (fp == NULL) {
        printf("Error: can't open billing file.\n");
        return;
    }

    printf("\n--- Billing Details ---\n");
    printf("B.ID\tPatient ID\tPatient Name\tAmount\n");
    printf("------------------------------------------------------\n");

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%[^,],%[^,],%[^,],%f", b.id, b.patient_id, patient_name, &b.amount);

        printf("%s\t%s\t\t%s\t%.2f\n", b.id, b.patient_id, patient_name, b.amount);
    }


    fclose(fp);
}

void billing_menu() {
    int choice;

    do {
        printf("\n--- Billing Management ---\n");
        printf("1. generate Bill\n");
        printf("2. display Bills\n");
        printf("3. search Bills\n");
        printf("4. delete Bills\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: generate_bill(); break;
            case 2: display_bills(); break;
            case 3: search_bill(); break;
            case 4: delete_bill(); break;
            case 5: break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
}