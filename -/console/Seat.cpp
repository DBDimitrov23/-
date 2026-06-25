#include "Seat.h"

Seat::Seat(int row, int number) {
    this->row = row;
    this->number = number;
    this->booked = false;
}

int Seat::getRow() const {
    return row;
}

int Seat::getNumber() const {
    return number;
}

bool Seat::isBooked() const {
    return booked;
}

void Seat::book() {
    booked = true;
}

void Seat::cancel() {
    booked = false;
}

std::string Seat::getLabel() const {
    char rowLetter = 'A' + row;
    std::string label = "";
    label += rowLetter;
    label += std::to_string(number + 1);
    return label;
}
