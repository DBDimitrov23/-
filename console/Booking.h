#pragma once
#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <vector>
#include <utility>
#include "Customer.h"
#include "Show.h"

// Класът Booking представя една конкретна резервация на билети,
// направена от клиент за определена прожекция
class Booking {
private:
    int id;                                      // уникален идентификатор на резервацията
    Customer customer;                            // клиентът, който прави резервацията (копие)
    int showId;                                   // ID на прожекцията
    std::string movieTitle;                        // заглавие на филма (за удобство при показване)
    std::string cinemaName;                        // име на киното
    std::string hallName;                           // име на салона
    std::string dateTime;                           // дата и час на прожекцията
    std::vector<std::pair<int, int>> seats;          // списък от резервирани места (ред, номер)
    double totalPrice;                              // обща дължима сума
    bool paymentCompleted;                          // дали плащането е завършено

public:
    // Конструктор - създава резервация в статус "неплатена"
    Booking(int id, const Customer& customer, const Show& show,
        const std::vector<std::pair<int, int>>& seats, double totalPrice);

    // Връща ID на резервацията
    int getId() const;

    // Връща клиента
    Customer getCustomer() const;

    // Връща ID на прожекцията
    int getShowId() const;

    // Връща списъка с резервирани места
    std::vector<std::pair<int, int>> getSeats() const;

    // Връща обща сума за плащане
    double getTotalPrice() const;

    // Връща дали плащането е завършено
    bool isPaymentCompleted() const;

    // Маркира резервацията като платена (потвърдена)
    void confirmPayment();

    // Извежда подробна информация за резервацията (билет) в конзолата
    void printTicket() const;
};

#endif // BOOKING_H