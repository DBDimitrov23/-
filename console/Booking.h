#pragma once
#ifndef BOOKING_H
#define BOOKING_H

#include <string>
#include <vector>
#include <utility>
#include "Customer.h"
#include "Show.h"

class Booking {
private:
    int id;
    Customer customer;
    int showId;
    std::string movieTitle;
    std::string cinemaName;
    std::string hallName;
    std::string dateTime;
    std::vector<std::pair<int, int>> seats;
    double totalPrice;
    bool paymentCompleted;

public:
    Booking(int id, const Customer& customer, const Show& show,
        const std::vector<std::pair<int, int>>& seats, double totalPrice);

    int getId() const;

    Customer getCustomer() const;

    int getShowId() const;

    std::vector<std::pair<int, int>> getSeats() const;

    double getTotalPrice() const;

    bool isPaymentCompleted() const;

    void confirmPayment();

    void printTicket() const;
};

#endif // BOOKING_H
