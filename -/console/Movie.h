#pragma once
#ifndef MOVIE_H
#define MOVIE_H

#include <string>

class Movie {
private:
    int id;
    std::string title;
    std::string genre;
    int durationMinutes;
    std::string rating;

public:
    Movie(int id, const std::string& title, const std::string& genre,
        int durationMinutes, const std::string& rating);

    int getId() const;

    std::string getTitle() const;

    std::string getGenre() const;

    int getDuration() const;

    std::string getRating() const;

    void print() const;
};

#endif // MOVIE_H
