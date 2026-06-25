#pragma once
#ifndef SEAT_H
#define SEAT_H

#include <string>

class Seat {
private:
    int row;
    int number;
    bool booked;

public:
    Seat(int row = 0, int number = 0);

    int getRow() const;

    int getNumber() const;

    bool isBooked() const;

    void book();

    void cancel();

    std::string getLabel() const;
};

#endif // SEAT_H
