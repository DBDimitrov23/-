#pragma once
#ifndef SHOW_H
#define SHOW_H

#include <string>
#include <vector>
#include <utility>
#include "Seat.h"

class Show {
private:
    int id;
    int movieId;
    std::string movieTitle;
    std::string cinemaName;
    std::string hallName;
    std::string dateTime;
    double price;
    int rows;
    int seatsPerRow;
    std::vector<std::vector<Seat>> seats;

public:
    Show(int id, int movieId, const std::string& movieTitle,
        const std::string& cinemaName, const std::string& hallName,
        const std::string& dateTime, double price,
        int rows, int seatsPerRow);

    int getId() const;

    int getMovieId() const;

    std::string getMovieTitle() const;

    std::string getCinemaName() const;

    std::string getHallName() const;

    std::string getDateTime() const;

    double getPrice() const;

    void displaySeatLayout() const;

    bool isSeatAvailable(int row, int number) const;

    bool bookSeats(const std::vector<std::pair<int, int>>& seatList);

    void releaseSeats(const std::vector<std::pair<int, int>>& seatList);

    double calculateTotalPrice(int numberOfSeats) const;
};

#endif // SHOW_H
