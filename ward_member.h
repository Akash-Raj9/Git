#ifndef WARD_MEMBER_H
#define WARD_MEMBER_H

struct WardMember {
    char id[20];
    char name[100];
    char gender[10];
    int age;
    int salary;
    char contact_num[15];
    char department[50];
};

void add_ward_member();
void search_ward_member();
void update_ward_member();
void delete_ward_member();
void display_ward_members();
void ward_member_menu();

#endif
