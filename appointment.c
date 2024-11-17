#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "appointment.h"

#define MAX_LINE_LENGTH 1024
#define APPOINTMENT_FILE "appointments.csv"
#define PATIENT_FILE "patients.csv"
#define DOCTOR_FILE "doctors.csv"

int is_patient_id_valid_appointment(const char* patient_id){
    FILE *fp = fopen(PATIENT_FILE, "r");
    char line[MAX_LINE_LENGTH], id[20], name[50];
    int age;

    if (fp == NULL) {
        printf("Error: Unable to open patient file.\n");
        return 0;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        sscanf(line, "%[^,],%[^,],%d", id, name, &age); 
        if (strcmp(id, patient_id) == 0) {
            fclose(fp);
            return 1; 
        }
    }

    fclose(fp);
    return 0;
}

int is_doctor_id_valid(const char* doctor_id) {
    FILE *fp = fopen(DOCTOR_FILE, "r");
    char line[MAX_LINE_LENGTH], id[20], name[50], specialization[50];

    if (fp == NULL) {
        printf("Error: Unable to open doctor file.\n");
        return 0;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        sscanf(line, "%[^,],%[^,],%s", id, name, specialization);
        if (strcmp(id, doctor_id) == 0) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0; 
}

void schedule_appointment() {
    struct Appointment a;
    FILE *fp = fopen(APPOINTMENT_FILE, "a");

    if (fp == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    printf("Enter appointment ID: ");
    scanf("%s", a.id);

    printf("Enter patient ID: ");
    scanf("%s", a.patient_id);

    if (!is_patient_id_valid_appointment(a.patient_id)) {
    printf("Error: Patient ID does not exist. Appointment scheduling failed.\n");
    fclose(fp);
    return;
}

    printf("Enter doctor ID: ");
    scanf("%s", a.doctor_id);

    if (!is_doctor_id_valid(a.doctor_id)) {
        printf("Error: Doctor ID %s does not exist. Appointment scheduling failed.\n", a.doctor_id);
        fclose(fp);
        return;
    }

    printf("Enter date in this format (YYYY-MM-DD): ");
    scanf("%s", a.date);

    fprintf(fp, "%s,%s,%s,%s\n", a.id, a.patient_id, a.doctor_id, a.date);
    fclose(fp);

    printf("Appointment scheduled successfully!\n");
}

void cancel_appointment() {
    char id[20], line[MAX_LINE_LENGTH], new_file[] = "temp_appointments.csv";
    struct Appointment a;
    int found = 0;

    FILE *fp = fopen(APPOINTMENT_FILE, "r");
    FILE *temp_fp = fopen(new_file, "w");

    if (fp == NULL || temp_fp == NULL) {
        printf("Error: can't open file.\n");
        return;
    }

    printf("enter appointment ID to cancel:- ");
    scanf("%s", id);

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        sscanf(line, "%[^,],%[^,],%[^,],%[^\n]", a.id, a.patient_id, a.doctor_id, a.date);
        if (strcmp(a.id, id) != 0) {
            fprintf(temp_fp, "%s,%s,%s,%s\n", a.id, a.patient_id, a.doctor_id, a.date);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp_fp);

    if (found) {
        remove(APPOINTMENT_FILE);
        rename(new_file, APPOINTMENT_FILE);
        printf("appointment canceled successfully!\n");
    } else {
        printf("No appointment found with ID: %s\n", id);
        remove(new_file);
    }
}

void reschedule_appointment() {
    char id[20], line[MAX_LINE_LENGTH], new_file[] = "temp_appointments.csv";
    struct Appointment a;
    int found = 0;

    FILE *fp = fopen(APPOINTMENT_FILE, "r");
    FILE *temp_fp = fopen(new_file, "w");

    if (fp == NULL || temp_fp == NULL) {
        printf("Error: can't open file.\n");
        return;
    }

    printf("enter appointment ID to reschedule:- ");
    scanf("%s", id);

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        sscanf(line, "%[^,],%[^,],%[^,],%[^\n]", a.id, a.patient_id, a.doctor_id, a.date);
        if (strcmp(a.id, id) == 0) {
            found = 1;
            printf("enter new date in the format (YYYY-MM-DD): ");
            scanf("%s", a.date);
            printf("appointment rescheduled successfully!\n");
        }
        fprintf(temp_fp, "%s,%s,%s,%s\n", a.id, a.patient_id, a.doctor_id, a.date);
    }

    fclose(fp);
    fclose(temp_fp);

    if (found) {
        remove(APPOINTMENT_FILE);
        rename(new_file, APPOINTMENT_FILE);
    } else {
        printf("No appointment found with ID: %s\n", id);
        remove(new_file);
    }
}

void display_appointments() {
    FILE *fp = fopen(APPOINTMENT_FILE, "r");
    char line[MAX_LINE_LENGTH];
    struct Appointment a;

    if (fp == NULL) {
        printf("Error: can't open file.\n");
        return;
    }

    printf("\n--- Appointment List ---\n");
    printf("Appointment ID\t Patient ID\t Doctor ID\t Date\n");
    printf("-------------------------------------------------------------\n");

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        sscanf(line, "%[^,],%[^,],%[^,],%[^\n]", a.id, a.patient_id, a.doctor_id, a.date);
        printf("%s\t\t %s\t\t %s\t\t %s\n", a.id, a.patient_id, a.doctor_id, a.date);
    }

    fclose(fp);
}

void appointment_menu() {
    int choice;

    do {
        printf("\n--- Appointment Management ---\n");
        printf("1. schedule appointment\n");
        printf("2. cancel appointment\n");
        printf("3. reschedule appointment\n");
        printf("4. display all appointments\n");
        printf("5. Back to main menu\n");
        printf("enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: schedule_appointment(); break;
            case 2: cancel_appointment(); break;
            case 3: reschedule_appointment(); break;
            case 4: display_appointments(); break;
            case 5: break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
}
