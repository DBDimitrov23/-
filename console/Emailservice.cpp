#include "EmailService.h"
#include <iostream>

// Симулира изпращане на имейл, печатайки съдържанието му в конзолата
void EmailService::sendBookingConfirmation(const Customer& customer, const Booking& booking) {
    std::cout << "\n----- ИЗПРАЩАНЕ НА ИМЕЙЛ -----\n";
    std::cout << "До: " << customer.getEmail() << std::endl;                 // получател на имейла
    std::cout << "Относно: Потвърждение на резервация №" << booking.getId() << std::endl; // тема на писмото
    std::cout << "Здравейте, " << customer.getName() << "!\n";                 // обръщение към клиента
    std::cout << "Вашата резервация е успешно потвърдена.\n";                   // основно съобщение
    std::cout << "Обща сума: " << booking.getTotalPrice() << " лв.\n";          // обща сума за информация
    std::cout << "Благодарим Ви, че избрахте нашата система за резервации!\n";  // финален поздрав
    std::cout << "-------------------------------\n";
}