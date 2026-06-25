#pragma once
#ifndef EMAIL_SERVICE_H
#define EMAIL_SERVICE_H

#include "Customer.h"
#include "Booking.h"

class EmailService {
public:
    static void sendBookingConfirmation(const Customer& customer, const Booking& booking);
};

#endif // EMAIL_SERVICE_H
