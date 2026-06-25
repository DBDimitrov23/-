#pragma once
#ifndef EMAIL_SERVICE_H
#define EMAIL_SERVICE_H

#include "Customer.h"
#include "Booking.h"

// Класът EmailService симулира изпращане на имейл известие до клиента
// (в реален проект тук би имало връзка с истински SMTP сървър,
// но за учебни цели само извеждаме съобщение в конзолата)
class EmailService {
public:
    // Статичен метод - не изисква създаване на обект от класа, за да се извика
    // Изпраща (симулирано) потвърждение на резервация до клиента
    static void sendBookingConfirmation(const Customer& customer, const Booking& booking);
};

#endif // EMAIL_SERVICE_H