#include "EmailService.h"
#include <iostream>

void EmailService::sendBookingConfirmation(const Customer& customer, const Booking& booking) {
    std::cout << "\n----- Email Notification -----\n";
    std::cout << "To: " << customer.getEmail() << std::endl;
    std::cout << "Subject: Booking Confirmation #" << booking.getId() << std::endl;
    std::cout << "Hello, " << customer.getName() << "!\n";
    std::cout << "Your reservation has been successfully confirmed.\n";
    std::cout << "Total amount: $" << booking.getTotalPrice() << std::endl;
    std::cout << "Thank you for choosing our booking system!\n";
    std::cout << "-------------------------------\n";
}
