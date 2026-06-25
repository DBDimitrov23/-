#include "Booking.h"
#include <iostream>

Booking::Booking(int id, const Customer& customer, const Show& show,
    const std::vector<std::pair<int, int>>& seats, double totalPrice) {
    this->id = id;
    this->customer = customer;
    this->showId = show.getId();
    this->movieTitle = show.getMovieTitle();
    this->cinemaName = show.getCinemaName();
    this->hallName = show.getHallName();
    this->dateTime = show.getDateTime();
    this->seats = seats;
    this->totalPrice = totalPrice;
    this->paymentCompleted = false;
}

int Booking::getId() const {
    return id;
}

Customer Booking::getCustomer() const {
    return customer;
}

int Booking::getShowId() const {
    return showId;
}

std::vector<std::pair<int, int>> Booking::getSeats() const {
    return seats;
}

double Booking::getTotalPrice() const {
    return totalPrice;
}

bool Booking::isPaymentCompleted() const {
    return paymentCompleted;
}

void Booking::confirmPayment() {
    paymentCompleted = true;
}

void Booking::printTicket() const {
    std::cout << "\n========= TICKET =========\n";
    std::cout << "Booking #: " << id << std::endl;
    std::cout << "Customer: " << customer.getName() << std::endl;
    std::cout << "Movie: " << movieTitle << std::endl;
    std::cout << "Cinema: " << cinemaName << " - " << hallName << std::endl;
    std::cout << "Date/Time: " << dateTime << std::endl;
    std::cout << "Seats: ";
    for (size_t i = 0; i < seats.size(); i++) {
        char rowLetter = 'A' + seats[i].first;
        std::cout << rowLetter << (seats[i].second + 1);
        if (i != seats.size() - 1) std::cout << ", ";
    }
    std::cout << std::endl;
    std::cout << "Total Price: $" << totalPrice << std::endl;
    std::cout << "Payment Status: " << (paymentCompleted ? "Paid" : "Unpaid") << std::endl;
    std::cout << "==========================\n";
}
