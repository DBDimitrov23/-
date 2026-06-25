#pragma once
#ifndef CINEMA_H
#define CINEMA_H

#include <string>
#include <vector>
#include "Hall.h"

// Класът Cinema представя едно кино в определен град,
// което съдържа списък от салони (Hall)
class Cinema {
private:
    int id;                    // уникален идентификатор на киното
    std::string name;          // име на киното, напр. "Cinema City"
    std::string city;          // град, в който се намира киното
    std::vector<Hall> halls;   // списък със всички салони на това кино

public:
    // Конструктор - инициализира киното с ID, име и град (без салони - те се добавят после)
    Cinema(int id, const std::string& name, const std::string& city);

    // Добавя нов салон към киното
    void addHall(const Hall& hall);

    // Връща ID на киното
    int getId() const;

    // Връща името на киното
    std::string getName() const;

    // Връща града на киното
    std::string getCity() const;

    // Връща константна референция към всички салони (само за четене)
    const std::vector<Hall>& getHalls() const;

    // Търси салон по ID; връща указател към него или nullptr, ако не е намерен
    const Hall* findHallById(int hallId) const;
};

#endif // CINEMA_H
