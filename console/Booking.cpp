#include "Booking.h"
#include <iostream>

// Конструктор - запазва данните от резервацията; плащането стартира като незавършено
Booking::Booking(int id, const Customer& customer, const Show& show,
    const std::vector<std::pair<int, int>>& seats, double totalPrice) {
    this->id = id;                              // запазваме ID на резервацията
    this->customer = customer;                  // запазваме копие на клиента
    this->showId = show.getId();                // запазваме ID на прожекцията
    this->movieTitle = show.getMovieTitle();     // запазваме заглавието на филма (за билета)
    this->cinemaName = show.getCinemaName();     // запазваме името на киното
    this->hallName = show.getHallName();         // запазваме името на салона
    this->dateTime = show.getDateTime();          // запазваме дата/час
    this->seats = seats;                          // запазваме списъка с резервирани места
    this->totalPrice = totalPrice;                // запазваме общата сума
    this->paymentCompleted = false;               // в началото резервацията НЕ е платена
}

// Геттър - ID на резервацията
int Booking::getId() const {
    return id;
}

// Геттър - връща клиента
Customer Booking::getCustomer() const {
    return customer;
}

// Геттър - ID на прожекцията
int Booking::getShowId() const {
    return showId;
}

// Геттър - списък с местата
std::vector<std::pair<int, int>> Booking::getSeats() const {
    return seats;
}

// Геттър - обща сума
double Booking::getTotalPrice() const {
    return totalPrice;
}

// Геттър - дали е платено
bool Booking::isPaymentCompleted() const {
    return paymentCompleted;
}

// Маркира резервацията като платена
void Booking::confirmPayment() {
    paymentCompleted = true; // сменяме флага - плащането е успешно
}

// Извежда билета на клиента в конзолата
void Booking::printTicket() const {
    std::cout << "\n========= БИЛЕТ =========\n";
    std::cout << "Резервация №: " << id << std::endl;            // номер на резервацията
    std::cout << "Клиент: " << customer.getName() << std::endl;   // име на клиента
    std::cout << "Филм: " << movieTitle << std::endl;             // заглавие на филма
    std::cout << "Кино: " << cinemaName << " - " << hallName << std::endl; // кино и салон
    std::cout << "Дата/час: " << dateTime << std::endl;            // дата и час на прожекцията
    std::cout << "Места: ";
    for (size_t i = 0; i < seats.size(); i++) {                    // обхождаме всички резервирани места
        char rowLetter = 'A' + seats[i].first;                      // превръщаме реда в буква
        std::cout << rowLetter << (seats[i].second + 1);              // показваме етикета, напр. "B4"
        if (i != seats.size() - 1) std::cout << ", ";                  // запетая между местата, освен след последното
    }
    std::cout << std::endl;
    std::cout << "Обща сума: " << totalPrice << " лв." << std::endl;     // обща дължима сума
    std::cout << "Статус на плащане: " << (paymentCompleted ? "ПЛАТЕНО" : "НЕПЛАТЕНО") << std::endl; // статус
    std::cout << "==========================\n";
}