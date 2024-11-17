#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doctor.h"

#define MAX_LINE_LENGTH 1024
#define DOCTOR_DB "doctors.csv"

void add_doctor() {
    struct Doctor d;
    FILE *fp = fopen(DOCTOR_DB, "a");

    if (fp == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    printf("Enter Doctor ID: ");
    scanf("%s", d.id);
    printf("Enter Doctor Name: ");
    getchar(); 
    fgets(d.name, sizeof(d.name), stdin);
    d.name[strcspn(d.name, "\n")] = '\0'; 
    printf("Enter Salary: ");
    scanf("%d", &d.salary);
    printf("Enter Contact Number: ");
    getchar(); 
    scanf("%s", d.contact_num);
    printf("Enter Gender: ");
    getchar();  
    scanf("%s", d.gender);
    printf("Enter Specialization: ");
    scanf("%s", d.specialization); 
    
    fprintf(fp, "%s,%s,%s,%d,%s,%s\n", d.id, d.name, d.gender, d.salary, d.contact_num, d.specialization);
    fclose(fp);

    printf("Doctor added successfully!\n");
}

void search_doctor() {
    char id[20], line[MAX_LINE_LENGTH];
    struct Doctor d;
    int found = 0;

    FILE *fp = fopen(DOCTOR_DB, "r");
    if (fp == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    printf("Enter Doctor ID to search: ");
    scanf("%s", id);

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        sscanf(line, "%[^,],%[^,],%[^,],%d,%[^,],%[^\n]", d.id, d.name, d.gender, &d.salary, d.contact_num, d.specialization);
        
        if (strcmp(d.id, id) == 0) {
            printf("\nDoctor Found:\n");
            printf("ID: %s\n", d.id);
            printf("Name: %s\n", d.name);
            printf("Gender: %s\n", d.gender);
            printf("Salary: %d\n", d.salary);
            printf("Contact Number: %s\n", d.contact_num);
            printf("Specialization: %s\n", d.specialization);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found) {
        printf("No doctor found with ID: %s\n", id);
    }
}

void update_doctor() {
    char id[20], line[MAX_LINE_LENGTH], new_file[] = "temp_doctors.csv";
    struct Doctor d;
    int found = 0;

    FILE *fp = fopen(DOCTOR_DB, "r");
    FILE *temp_fp = fopen(new_file, "w");

    if (fp == NULL || temp_fp == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    printf("Enter Doctor ID to update: ");
    scanf("%s", id);

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        sscanf(line, "%[^,],%[^,],%[^,],%d,%[^,],%[^\n]", d.id, d.name, d.gender, &d.salary, d.contact_num, d.specialization);
        
        if (strcmp(d.id, id) == 0) {
            found = 1;
            printf("Enter new name: ");
            getchar(); 
            fgets(d.name, sizeof(d.name), stdin);
            d.name[strcspn(d.name, "\n")] = '\0';
            printf("Enter new salary: ");
            scanf("%d", &d.salary);
            getchar(); 
            printf("Enter new contact number: ");
            scanf("%s", d.contact_num); 
            printf("Enter new gender: ");
            scanf("%s", d.gender);
            printf("Enter new specialization: ");
            scanf("%s", d.specialization);
            printf("Doctor updated successfully!\n");
        }
        
        fprintf(temp_fp, "%s,%s,%s,%d,%s,%s\n", d.id, d.name, d.gender, d.salary, d.contact_num, d.specialization);
    }

    fclose(fp);
    fclose(temp_fp);

    if (found) {
        remove(DOCTOR_DB);        
        rename(new_file, DOCTOR_DB); 
    } else {
        printf("No doctor found with ID: %s\n", id);
        remove(new_file); 
    }
}

void delete_doctor() {
    char id[20], line[MAX_LINE_LENGTH], new_file[] = "temp_doctors.csv";
    struct Doctor d;
    int found = 0;

    FILE *fp = fopen(DOCTOR_DB, "r");
    FILE *temp_fp = fopen(new_file, "w");

    if (fp == NULL || temp_fp == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    printf("Enter Doctor ID to delete: ");
    scanf("%s", id);

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        sscanf(line, "%[^,],%[^,],%[^,],%d,%[^,],%[^\n]", d.id, d.name, d.gender, &d.salary, d.contact_num, d.specialization);
        
        if (strcmp(d.id, id) != 0) {
            fprintf(temp_fp, "%s,%s,%s,%d,%s,%s\n", d.id, d.name, d.gender, d.salary, d.contact_num, d.specialization);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp_fp);

    if (found) {
        remove(DOCTOR_DB);
        rename(new_file, DOCTOR_DB);
        printf("Doctor deleted successfully!\n");
    } else {
        printf("No doctor found with ID: %s\n", id);
        remove(new_file);
    }
}

void display_doctors() {
    char line[MAX_LINE_LENGTH];
    struct Doctor d;

    FILE *fp = fopen(DOCTOR_DB, "r");
    if (fp == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    printf("\n--- Doctor List ---\n");
    printf("ID\tName\t\tGender\tSalary\tContact\t\tSpecialization\n");
    printf("--------------------------------------------------------------------\n");

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        sscanf(line, "%[^,],%[^,],%[^,],%d,%[^,],%[^\n]", d.id, d.name, d.gender, &d.salary, d.contact_num, d.specialization);
        printf("%s\t%s\t%s\t%d\t%s\t%s\n", d.id, d.name, d.gender, d.salary, d.contact_num, d.specialization);
    }

    fclose(fp);
}


void doctor_menu() {
    int choice;

    do {
        printf("\n--- Doctor Management ---\n");
        printf("1. Add Doctor\n");
        printf("2. Search Doctor\n");
        printf("3. Update Doctor\n");
        printf("4. Delete Doctor\n");
        printf("5. Display all Doctor\n");
        printf("6. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_doctor(); break;
            case 2: search_doctor(); break;
            case 3: update_doctor(); break;
            case 4: delete_doctor(); break;
            case 5: display_doctors(); break;
            case 6: break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
}
