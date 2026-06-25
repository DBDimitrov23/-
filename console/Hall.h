#pragma once
#ifndef HALL_H
#define HALL_H

#include <string>

// Класът Hall представя един салон в дадено кино
// (самите места не се пазят тук, а във всяка конкретна прожекция - Show,
// защото различните прожекции в един и същ салон имат различна заетост)
class Hall {
private:
    int id;              // уникален идентификатор на салона
    std::string name;    // име на салона, напр. "Зала 1"
    int rows;             // брой редове с места
    int seatsPerRow;      // брой места на ред

public:
    // Конструктор - инициализира салона с име, брой редове и места на ред
    Hall(int id, const std::string& name, int rows, int seatsPerRow);

    // Връща ID на салона
    int getId() const;

    // Връща името на салона
    std::string getName() const;

    // Връща броя редове
    int getRows() const;

    // Връща броя места на ред
    int getSeatsPerRow() const;

    // Връща общия капацитет на салона (редове * места на ред)
    int getCapacity() const;
};

#endif // HALL_H