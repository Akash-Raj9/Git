#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "nurse.h"

#define MAX_LINE_LENGTH 1024
#define NURSE_FILE "nurses.csv"

void add_nurse() {
    struct Nurse n;
    FILE *fp = fopen(NURSE_FILE, "a");

    if (fp == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    printf("Enter Nurse ID: ");
    scanf("%s", n.id);
    printf("Enter Nurse Name: ");
    getchar();  
    fgets(n.name, sizeof(n.name), stdin);
    n.name[strcspn(n.name, "\n")] = '\0';
    printf("Enter Age: ");
    scanf("%d", &n.age);
    printf("Enter Salary: ");
    scanf("%d", &n.salary);
    printf("Enter Contact Number: ");
    getchar();  
    scanf("%s", n.contact_num);  
    printf("Enter Gender: ");
    scanf("%s", n.gender); 
    printf("Enter Department: ");
    getchar(); 
    fgets(n.department, sizeof(n.department), stdin);
    n.department[strcspn(n.department, "\n")] = '\0'; 

    fprintf(fp, "%s,%s,%s,%d,%d,%s,%s\n", n.id, n.name, n.gender, n.age, n.salary, n.contact_num, n.department);
    fclose(fp);

    printf("Nurse added successfully!\n");
}

void search_nurse() {
    char id[20], line[MAX_LINE_LENGTH];
    struct Nurse n;
    int found = 0;

    FILE *fp = fopen(NURSE_FILE, "r");
    if (fp == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    printf("Enter Nurse ID to search: ");
    scanf("%s", id);

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        sscanf(line, "%[^,],%[^,],%[^,],%d,%d,%[^,],%[^\n]", n.id, n.name, n.gender, &n.age, &n.salary, n.contact_num, n.department);
        
        if (strcmp(n.id, id) == 0) {
            printf("\nNurse Found:\n");
            printf("ID: %s\n", n.id);
            printf("Name: %s\n", n.name);
            printf("Gender: %s\n", n.gender);
            printf("Age: %d\n", n.age);
            printf("Salary: %d\n", n.salary); 
            printf("Contact Number: %s\n", n.contact_num);
            printf("Department: %s\n", n.department);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found) {
        printf("No nurse found with ID: %s\n", id);
    }
}

void update_nurse() {
    char id[20], line[MAX_LINE_LENGTH], new_file[] = "temp_nurses.csv";
    struct Nurse n;
    int found = 0;

    FILE *fp = fopen(NURSE_FILE, "r");
    FILE *temp_fp = fopen(new_file, "w");

    if (fp == NULL || temp_fp == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    printf("Enter Nurse ID to update: ");
    scanf("%s", id);

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        sscanf(line, "%[^,],%[^,],%[^,],%d,%d,%[^,],%[^\n]", n.id, n.name, n.gender, &n.age, &n.salary, n.contact_num, n.department);
        
        if (strcmp(n.id, id) == 0) {
            found = 1;
            printf("Enter new name: ");
            getchar();  
            fgets(n.name, sizeof(n.name), stdin);
            n.name[strcspn(n.name, "\n")] = '\0';  
            
            printf("Enter new age: ");
            scanf("%d", &n.age);
            
            printf("Enter new salary: ");
            scanf("%d", &n.salary);
            
            printf("Enter new contact number: ");
            getchar(); 
            scanf("%s", n.contact_num); 

            printf("Enter new gender: ");
            scanf("%s", n.gender);

            printf("Enter new department: ");
            getchar();  
            fgets(n.department, sizeof(n.department), stdin);
            n.department[strcspn(n.department, "\n")] = '\0';  

            printf("Nurse updated successfully!\n");
        }
        
        fprintf(temp_fp, "%s,%s,%s,%d,%d,%s,%s\n", n.id, n.name, n.gender, n.age, n.salary, n.contact_num, n.department);
    }

    fclose(fp);
    fclose(temp_fp);

    if (found) {
        remove(NURSE_FILE);       
        rename(new_file, NURSE_FILE); 
    } else {
        printf("No nurse found with ID: %s\n", id);
        remove(new_file); 
    }
}

void delete_nurse() {
    char id[20], line[MAX_LINE_LENGTH], new_file[] = "temp_nurses.csv";
    struct Nurse n;
    int found = 0;

    FILE *fp = fopen(NURSE_FILE, "r");
    FILE *temp_fp = fopen(new_file, "w");

    if (fp == NULL || temp_fp == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    printf("Enter Nurse ID to delete: ");
    scanf("%s", id);

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        sscanf(line, "%[^,],%[^,],%[^,],%d,%d,%[^,],%[^\n]", n.id, n.name, n.gender, &n.age, &n.salary, n.contact_num, n.department);
        
        if (strcmp(n.id, id) != 0) {
            fprintf(temp_fp, "%s,%s,%s,%d,%d,%s,%s\n", n.id, n.name, n.gender, n.age, n.salary, n.contact_num, n.department);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp_fp);

    if (found) {
        remove(NURSE_FILE);
        rename(new_file, NURSE_FILE);
        printf("Nurse deleted successfully!\n");
    } else {
        printf("No nurse found with ID: %s\n", id);
        remove(new_file);
    }
}

void display_nurses() {
    char line[MAX_LINE_LENGTH];
    struct Nurse n;

    FILE *fp = fopen(NURSE_FILE, "r");
    if (fp == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    printf("\n--- Nurse List ---\n");
    printf("ID\tName\t\tGender\tAge\tSalary\tContact\t\tDepartment\n");
    printf("----------------------------------------------------------------------------\n");

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        sscanf(line, "%[^,],%[^,],%[^,],%d,%d,%[^,],%[^\n]", n.id, n.name, n.gender, &n.age, &n.salary, n.contact_num, n.department);
        
        printf("%s\t%s\t%s\t%d\t%d\t%s\t%s\n", n.id, n.name, n.gender, n.age, n.salary, n.contact_num, n.department);
    }

    fclose(fp);
}

void nurse_menu() {
    int choice;

    do {
        printf("\n--- Nurse Management ---\n");
        printf("1. Add Nurse\n");
        printf("2. Search Nurse\n");
        printf("3. Update Nurse\n");
        printf("4. Delete Nurse\n");
        printf("5. Display all Nurses\n");
        printf("6. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_nurse(); break;
            case 2: search_nurse(); break;
            case 3: update_nurse(); break;
            case 4: delete_nurse(); break;
            case 5: display_nurses(); break;
            case 6: break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
}
