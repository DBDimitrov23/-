#pragma once
#ifndef SHOW_H
#define SHOW_H

#include <string>
#include <vector>
#include <utility>
#include "Seat.h"

// Класът Show представя конкретна прожекция:
// определен филм, показван в определено кино и салон, в определен час.
// Всяка прожекция има СВОЯ собствена мрежа от места (seats),
// защото заетостта е различна за всяка прожекция, дори да е същия салон.
class Show {
private:
    int id;                              // уникален идентификатор на прожекцията
    int movieId;                         // ID на филма, който се прожектира
    std::string movieTitle;              // заглавие на филма (за бързо показване)
    std::string cinemaName;              // име на киното
    std::string hallName;                // име на салона
    std::string dateTime;                // дата и час на прожекцията, напр. "2026-06-25 19:30"
    double price;                        // цена на билет за тази прожекция
    int rows;                            // брой редове места
    int seatsPerRow;                     // брой места на ред
    std::vector<std::vector<Seat>> seats; // двумерна мрежа от места (ред x място)

public:
    // Конструктор - създава прожекция и автоматично генерира мрежата от свободни места
    Show(int id, int movieId, const std::string& movieTitle,
        const std::string& cinemaName, const std::string& hallName,
        const std::string& dateTime, double price,
        int rows, int seatsPerRow);

    // Връща ID на прожекцията
    int getId() const;

    // Връща ID на филма
    int getMovieId() const;

    // Връща заглавието на филма
    std::string getMovieTitle() const;

    // Връща името на киното
    std::string getCinemaName() const;

    // Връща името на салона
    std::string getHallName() const;

    // Връща датата и часа на прожекцията
    std::string getDateTime() const;

    // Връща цената на билет
    double getPrice() const;

    // Извежда в конзолата визуална схема на местата (заети/свободни)
    void displaySeatLayout() const;

    // Проверява дали дадено място (ред, номер) съществува и е свободно
    bool isSeatAvailable(int row, int number) const;

    // Опитва да резервира списък от места; връща true при успех, false при провал
    // (например ако дори едно от местата вече е заето или не съществува)
    bool bookSeats(const std::vector<std::pair<int, int>>& seatList);

    // Освобождава вече резервирани места (полезно при отказ от плащане)
    void releaseSeats(const std::vector<std::pair<int, int>>& seatList);

    // Изчислява обща цена за зададен брой места
    double calculateTotalPrice(int numberOfSeats) const;
};

#endif // SHOW_H