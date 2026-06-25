#include "Hall.h"

Hall::Hall(int id, const std::string& name, int rows, int seatsPerRow) {
    this->id = id;
    this->name = name;
    this->rows = rows;
    this->seatsPerRow = seatsPerRow;
}

int Hall::getId() const {
    return id;
}

std::string Hall::getName() const {
    return name;
}

int Hall::getRows() const {
    return rows;
}

int Hall::getSeatsPerRow() const {
    return seatsPerRow;
}

int Hall::getCapacity() const {
    return rows * seatsPerRow;
}
