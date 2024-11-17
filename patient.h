#ifndef PATIENT_H
#define PATIENT_H

struct Patient {
    char id[20];
    char name[100];
    char gender[10];
    int age;
    char contact_num[15];
    char disease[100];
};

void add_patient();
void search_patient();
void update_patient();
void delete_patient();
void display_patients();
void user_patient();
void patient_menu();
int get_patient_name(const char* patient_id, char* patient_name);

#endif
