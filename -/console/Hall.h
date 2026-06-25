#pragma once
#ifndef HALL_H
#define HALL_H

#include <string>

class Hall {
private:
    int id;
    std::string name;
    int rows;
    int seatsPerRow;

public:
    Hall(int id, const std::string& name, int rows, int seatsPerRow);

    int getId() const;

    std::string getName() const;

    int getRows() const;

    int getSeatsPerRow() const;

    int getCapacity() const;
};

#endif // HALL_H
