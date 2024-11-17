#ifndef APPOINTMENT_H
#define APPOINTMENT_H

struct Appointment {
    char id[20];
    char patient_id[20];
    char doctor_id[20];
    char date[20];
};

void schedule_appointment();
void cancel_appointment();
void reschedule_appointment();
void display_appointments();
void appointment_menu();

#endif
