#ifndef DOCTOR_H
#define DOCTOR_H

struct Doctor {
    char id[20];
    char name[50];
    char specialization[50];
    int salary;
    char contact_num[15];
    char gender[10];
};

void add_doctor();
void search_doctor();
void update_doctor();
void delete_doctor();
void display_doctors();
void doctor_menu();

#endif
