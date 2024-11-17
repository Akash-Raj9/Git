#ifndef NURSE_H
#define NURSE_H

struct Nurse {
    char id[20];
    char name[100];
    char gender[10];       
    int age;
    int salary;
    char contact_num[15];
    char department[50];
};

void add_nurse();
void search_nurse();
void update_nurse();
void delete_nurse();
void display_nurses();
void nurse_menu();

#endif
