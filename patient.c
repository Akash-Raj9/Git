#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patient.h"

#define MAX_LINE_LENGTH 1024
#define PATIENT_FILE "patients.csv"

void add_patient() {
    struct Patient patient;
    FILE *fp = fopen(PATIENT_FILE, "a");

    if (fp == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    printf("Enter Patient ID: ");
    scanf("%s", patient.id);
    
    printf("Enter Patient Name: ");
    getchar();  
    fgets(patient.name, sizeof(patient.name), stdin);
    patient.name[strcspn(patient.name, "\n")] = '\0';  

    printf("Enter Age: ");
    scanf("%d", &patient.age);

    printf("Enter Contact Number: ");
    getchar();  
    scanf("%s", patient.contact_num);  

    printf("Enter Gender: ");
    scanf("%s", patient.gender);  

    printf("Enter Disease: ");
    getchar();  
    fgets(patient.disease, sizeof(patient.disease), stdin);
    patient.disease[strcspn(patient.disease, "\n")] = '\0';

    fprintf(fp, "%s,%s,%s,%d,%s,%s\n", patient.id, patient.name, patient.gender, patient.age, patient.contact_num, patient.disease);
    fclose(fp);

    printf("Patient added successfully!\n");
}

void search_patient() {
    char id[20], line[MAX_LINE_LENGTH];
    struct Patient patient;
    int found = 0;

    FILE *fp = fopen(PATIENT_FILE, "r");
    if (fp == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    printf("Enter Patient ID to search: ");
    scanf("%s", id);

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        sscanf(line, "%[^,],%[^,],%[^,],%d,%[^,],%[^\n]", patient.id, patient.name, patient.gender, &patient.age, patient.contact_num, patient.disease);
        
        if (strcmp(patient.id, id) == 0) {
            printf("\nPatient Found:\n");
            printf("ID: %s\n", patient.id);
            printf("Name: %s\n", patient.name);
            printf("Gender: %s\n", patient.gender);
            printf("Age: %d\n", patient.age);
            printf("Contact Number: %s\n", patient.contact_num);
            printf("Disease: %s\n", patient.disease);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found) {
        printf("No patient found with ID: %s\n", id);
    }
}

void update_patient() {
    char id[20], line[MAX_LINE_LENGTH], new_file[] = "temp_patients.csv";
    struct Patient patient;
    int found = 0;

    FILE *fp = fopen(PATIENT_FILE, "r");
    FILE *temp_fp = fopen(new_file, "w");

    if (fp == NULL || temp_fp == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    printf("Enter Patient ID to update: ");
    scanf("%s", id);

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        sscanf(line, "%[^,],%[^,],%[^,],%d,%[^,],%[^\n]", patient.id, patient.name, patient.gender, &patient.age, patient.contact_num, patient.disease);
        
        if (strcmp(patient.id, id) == 0) {
            found = 1;
            printf("Enter new name: ");
            getchar(); 
            fgets(patient.name, sizeof(patient.name), stdin);
            patient.name[strcspn(patient.name, "\n")] = '\0'; 
            
            printf("Enter new age: ");
            scanf("%d", &patient.age);
            
            printf("Enter new contact number: ");
            getchar();  
            scanf("%s", patient.contact_num);  

            printf("Enter new gender: ");
            scanf("%s", patient.gender);

            printf("Enter new disease: ");
            getchar();  
            fgets(patient.disease, sizeof(patient.disease), stdin);
            patient.disease[strcspn(patient.disease, "\n")] = '\0';  

            printf("Patient updated successfully!\n");
        }
        
        fprintf(temp_fp, "%s,%s,%s,%d,%s,%s\n", patient.id, patient.name, patient.gender, patient.age, patient.contact_num, patient.disease);
    }

    fclose(fp);
    fclose(temp_fp);

    if (found) {
        remove(PATIENT_FILE);        
        rename(new_file, PATIENT_FILE); 
    } else {
        printf("No patient found with ID: %s\n", id);
        remove(new_file);  
    }
}

void delete_patient() {
    char id[20], line[MAX_LINE_LENGTH], new_file[] = "temp_patients.csv";
    struct Patient patient;
    int found = 0;

    FILE *fp = fopen(PATIENT_FILE, "r");
    FILE *temp_fp = fopen(new_file, "w");

    if (fp == NULL || temp_fp == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    printf("Enter Patient ID to delete: ");
    scanf("%s", id);

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        sscanf(line, "%[^,],%[^,],%[^,],%d,%[^,],%[^\n]", patient.id, patient.name, patient.gender, &patient.age, patient.contact_num, patient.disease);
        
        if (strcmp(patient.id, id) != 0) {
            fprintf(temp_fp, "%s,%s,%s,%d,%s,%s\n", patient.id, patient.name, patient.gender, patient.age, patient.contact_num, patient.disease);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp_fp);

    if (found) {
        remove(PATIENT_FILE);
        rename(new_file, PATIENT_FILE);
        printf("Patient deleted successfully!\n");
    } else {
        printf("No patient found with ID: %s\n", id);
        remove(new_file);
    }
}

void display_patients() {
    char line[MAX_LINE_LENGTH];
    struct Patient patient;

    FILE *fp = fopen(PATIENT_FILE, "r");
    if (fp == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    printf("\n--- Patient List ---\n");
    printf("ID\tName\t\tGender\tAge\tContact\t\tDisease\n");
    printf("---------------------------------------------------------------------\n");

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        sscanf(line, "%[^,],%[^,],%[^,],%d,%[^,],%[^\n]", patient.id, patient.name, patient.gender, &patient.age, patient.contact_num, patient.disease);
        printf("%s\t%s\t%s\t%d\t%s\t%s\n", patient.id, patient.name, patient.gender, patient.age, patient.contact_num, patient.disease);
    }

    fclose(fp);
}

void patient_menu() {
    int choice;

    do {
        printf("\n--- Patient Management ---\n");
        printf("1. Add Patient\n");
        printf("2. Search Patient\n");
        printf("3. Update Patient\n");
        printf("4. Delete Patient\n");
        printf("5. Display all Patients\n");
        printf("6. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_patient(); break;
            case 2: search_patient(); break;
            case 3: update_patient(); break;
            case 4: delete_patient(); break;
            case 5: display_patients(); break;
            case 6: break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
}

void user_patient() {
    int choice;

    do {
        printf("\n--- Patient Management ---\n");
        printf("1. Add Patient\n");
        printf("2. Back to main menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_patient(); break;
            case 2: break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 2);
}

int get_patient_name(const char* patient_id, char* patient_name) {
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
            strcpy(patient_name, p.name); 
            fclose(fp);
            return 1;  
        }
    }

    fclose(fp);
    return 0; 
}

