#ifndef BILLING_H
#define BILLING_H

struct Bill {
    char id[20];
    char patient_id[20];
    float amount;
};

void generate_bill();
void display_bills();
void search_bill();
void delete_bill();
void billing_menu();

#endif
