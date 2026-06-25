#pragma once
#ifndef CINEMA_H
#define CINEMA_H

#include <string>
#include <vector>
#include "Hall.h"

class Cinema {
private:
    int id;
    std::string name;
    std::string city;
    std::vector<Hall> halls;

public:
    Cinema(int id, const std::string& name, const std::string& city);

    void addHall(const Hall& hall);

    int getId() const;

    std::string getName() const;

    std::string getCity() const;

    const std::vector<Hall>& getHalls() const;

    const Hall* findHallById(int hallId) const;
};

#endif // CINEMA_H
