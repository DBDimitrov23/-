#include "Show.h"
#include <iostream>
#include <iomanip>

Show::Show(int id, int movieId, const std::string& movieTitle,
    const std::string& cinemaName, const std::string& hallName,
    const std::string& dateTime, double price,
    int rows, int seatsPerRow) {
    this->id = id;
    this->movieId = movieId;
    this->movieTitle = movieTitle;
    this->cinemaName = cinemaName;
    this->hallName = hallName;
    this->dateTime = dateTime;
    this->price = price;
    this->rows = rows;
    this->seatsPerRow = seatsPerRow;

    for (int r = 0; r < rows; r++) {
        std::vector<Seat> rowOfSeats;
        for (int s = 0; s < seatsPerRow; s++) {
            rowOfSeats.push_back(Seat(r, s));
        }
        seats.push_back(rowOfSeats);
    }
}

int Show::getId() const {
    return id;
}

int Show::getMovieId() const {
    return movieId;
}

std::string Show::getMovieTitle() const {
    return movieTitle;
}

std::string Show::getCinemaName() const {
    return cinemaName;
}

std::string Show::getHallName() const {
    return hallName;
}

std::string Show::getDateTime() const {
    return dateTime;
}

double Show::getPrice() const {
    return price;
}

void Show::displaySeatLayout() const {
    std::cout << "\n--- Seat Layout for \"" << movieTitle << "\" ---\n";
    std::cout << "    ";
    for (int s = 0; s < seatsPerRow; s++) {
        std::cout << std::setw(4) << (s + 1);
    }
    std::cout << std::endl;

    for (int r = 0; r < rows; r++) {
        char rowLetter = 'A' + r;
        std::cout << " " << rowLetter << "  ";
        for (int s = 0; s < seatsPerRow; s++) {
            if (seats[r][s].isBooked()) {
                std::cout << std::setw(4) << "X";
            }
            else {
                std::cout << std::setw(4) << (s + 1);
            }
        }
        std::cout << std::endl;
    }
    std::cout << "(X = occupied seat, number = available seat with that number)\n";
}

bool Show::isSeatAvailable(int row, int number) const {
    if (row < 0 || row >= rows || number < 0 || number >= seatsPerRow) {
        return false;
    }
    return !seats[row][number].isBooked();
}

bool Show::bookSeats(const std::vector<std::pair<int, int>>& seatList) {
    for (const std::pair<int, int>& pos : seatList) {
        if (!isSeatAvailable(pos.first, pos.second)) {
            return false;
        }
    }
    for (const std::pair<int, int>& pos : seatList) {
        seats[pos.first][pos.second].book();
    }
    return true;
}

void Show::releaseSeats(const std::vector<std::pair<int, int>>& seatList) {
    for (const std::pair<int, int>& pos : seatList) {
        if (pos.first >= 0 && pos.first < rows &&
            pos.second >= 0 && pos.second < seatsPerRow) {
            seats[pos.first][pos.second].cancel();
        }
    }
}

double Show::calculateTotalPrice(int numberOfSeats) const {
    return price * numberOfSeats;
}
