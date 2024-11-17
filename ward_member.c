#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ward_member.h"

#define MAX_LINE_LENGTH 1024
#define WARD_MEMBER_FILE "ward_members.csv"

void add_ward_member() {
    struct WardMember wm;
    FILE *fp = fopen(WARD_MEMBER_FILE, "a");

    if (fp == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    printf("Enter Ward Member ID: ");
    scanf("%s", wm.id);
    
    printf("Enter Ward Member Name: ");
    getchar();  
    fgets(wm.name, sizeof(wm.name), stdin);
    wm.name[strcspn(wm.name, "\n")] = '\0';  

    printf("Enter Age: ");
    scanf("%d", &wm.age);

    printf("Enter Salary: ");
    scanf("%d", &wm.salary);

    printf("Enter Contact Number: ");
    getchar();  
    scanf("%s", wm.contact_num);  

    printf("Enter Gender: ");
    scanf("%s", wm.gender);  

    printf("Enter Department: ");
    getchar();  
    fgets(wm.department, sizeof(wm.department), stdin);
    wm.department[strcspn(wm.department, "\n")] = '\0'; 

    fprintf(fp, "%s,%s,%s,%d,%d,%s,%s\n", wm.id, wm.name, wm.gender, wm.age, wm.salary, wm.contact_num, wm.department);
    fclose(fp);

    printf("Ward Member added successfully!\n");
}

void search_ward_member() {
    char id[20], line[MAX_LINE_LENGTH];
    struct WardMember wm;
    int found = 0;

    FILE *fp = fopen(WARD_MEMBER_FILE, "r");
    if (fp == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    printf("Enter Ward Member ID to search: ");
    scanf("%s", id);

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        sscanf(line, "%[^,],%[^,],%[^,],%d,%d,%[^,],%[^\n]", wm.id, wm.name, wm.gender, &wm.age, &wm.salary, wm.contact_num, wm.department);
        
        if (strcmp(wm.id, id) == 0) {
            printf("\nWard Member Found:\n");
            printf("ID: %s\n", wm.id);
            printf("Name: %s\n", wm.name);
            printf("Gender: %s\n", wm.gender);
            printf("Age: %d\n", wm.age);
            printf("Salary: %d\n", wm.salary); 
            printf("Contact Number: %s\n", wm.contact_num);
            printf("Department: %s\n", wm.department);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found) {
        printf("No ward member found with ID: %s\n", id);
    }
}

void update_ward_member() {
    char id[20], line[MAX_LINE_LENGTH], new_file[] = "temp_ward_members.csv";
    struct WardMember wm;
    int found = 0;

    FILE *fp = fopen(WARD_MEMBER_FILE, "r");
    FILE *temp_fp = fopen(new_file, "w");

    if (fp == NULL || temp_fp == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    printf("Enter Ward Member ID to update: ");
    scanf("%s", id);

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        sscanf(line, "%[^,],%[^,],%[^,],%d,%d,%[^,],%[^\n]", wm.id, wm.name, wm.gender, &wm.age, &wm.salary, wm.contact_num, wm.department);
        
        if (strcmp(wm.id, id) == 0) {
            found = 1;
            printf("Enter new name: ");
            getchar(); 
            fgets(wm.name, sizeof(wm.name), stdin);
            wm.name[strcspn(wm.name, "\n")] = '\0'; 
            
            printf("Enter new age: ");
            scanf("%d", &wm.age);
            
            printf("Enter new salary: ");
            scanf("%d", &wm.salary);
            
            printf("Enter new contact number: ");
            getchar(); 
            scanf("%s", wm.contact_num); 

            printf("Enter new gender: ");
            scanf("%s", wm.gender);

            printf("Enter new department: ");
            getchar();  
            fgets(wm.department, sizeof(wm.department), stdin);
            wm.department[strcspn(wm.department, "\n")] = '\0';  

            printf("Ward Member updated successfully!\n");
        }
        
        fprintf(temp_fp, "%s,%s,%s,%d,%d,%s,%s\n", wm.id, wm.name, wm.gender, wm.age, wm.salary, wm.contact_num, wm.department);
    }

    fclose(fp);
    fclose(temp_fp);

    if (found) {
        remove(WARD_MEMBER_FILE);       
        rename(new_file, WARD_MEMBER_FILE);  
    } else {
        printf("No ward member found with ID: %s\n", id);
        remove(new_file); 
    }
}

void delete_ward_member() {
    char id[20], line[MAX_LINE_LENGTH], new_file[] = "temp_ward_members.csv";
    struct WardMember wm;
    int found = 0;

    FILE *fp = fopen(WARD_MEMBER_FILE, "r");
    FILE *temp_fp = fopen(new_file, "w");

    if (fp == NULL || temp_fp == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    printf("Enter Ward Member ID to delete: ");
    scanf("%s", id);

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        sscanf(line, "%[^,],%[^,],%[^,],%d,%d,%[^,],%[^\n]", wm.id, wm.name, wm.gender, &wm.age, &wm.salary, wm.contact_num, wm.department);
        
        if (strcmp(wm.id, id) != 0) {
            fprintf(temp_fp, "%s,%s,%s,%d,%d,%s,%s\n", wm.id, wm.name, wm.gender, wm.age, wm.salary, wm.contact_num, wm.department);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp_fp);

    if (found) {
        remove(WARD_MEMBER_FILE);
        rename(new_file, WARD_MEMBER_FILE);
        printf("Ward Member deleted successfully!\n");
    } else {
        printf("No ward member found with ID: %s\n", id);
        remove(new_file);
    }
}

void display_ward_members() {
    char line[MAX_LINE_LENGTH];
    struct WardMember wm;

    FILE *fp = fopen(WARD_MEMBER_FILE, "r");
    if (fp == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    printf("\n--- Ward Member List ---\n");
    printf("ID\tName\t\tGender\tAge\tSalary\tContact\t\tDepartment\n");
    printf("----------------------------------------------------------------------------\n");

    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
        sscanf(line, "%[^,],%[^,],%[^,],%d,%d,%[^,],%[^\n]", wm.id, wm.name, wm.gender, &wm.age, &wm.salary, wm.contact_num, wm.department);
        
        printf("%s\t%s\t%s\t%d\t%d\t%s\t%s\n", wm.id, wm.name, wm.gender, wm.age, wm.salary, wm.contact_num, wm.department);
    }

    fclose(fp);
}

void ward_member_menu() {
    int choice;

    do {
        printf("\n--- Ward Member Management ---\n");
        printf("1. Add Ward Member\n");
        printf("2. Search Ward Member\n");
        printf("3. Update Ward Member\n");
        printf("4. Delete Ward Member\n");
        printf("5. Display all Ward Members\n");
        printf("6. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_ward_member(); break;
            case 2: search_ward_member(); break;
            case 3: update_ward_member(); break;
            case 4: delete_ward_member(); break;
            case 5: display_ward_members(); break;
            case 6: break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);
}
