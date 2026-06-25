#pragma once
#ifndef SEAT_H
#define SEAT_H

#include <string>

// Класът Seat представя едно конкретно място в киносалона
class Seat {
private:
    int row;        // ред, в който се намира мястото (започва от 0)
    int number;      // номер на мястото в реда (започва от 0)
    bool booked;     // флаг - true ако мястото е заето/резервирано

public:
    // Конструктор - по подразбиране създава свободно място на позиция (0,0)
    Seat(int row = 0, int number = 0);

    // Връща реда на мястото (само за четене - const)
    int getRow() const;

    // Връща номера на мястото в реда
    int getNumber() const;

    // Връща true, ако мястото вече е заето
    bool isBooked() const;

    // Маркира мястото като заето (извиква се при резервация)
    void book();

    // Освобождава мястото - премахва резервацията (при отказ/грешка)
    void cancel();

    // Връща текстов етикет на мястото, напр. "A3" (буква=ред, число=номер)
    std::string getLabel() const;
};

#endif // SEAT_H