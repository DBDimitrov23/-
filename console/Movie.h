#pragma once
#ifndef MOVIE_H
#define MOVIE_H

#include <string>

// Класът Movie съхранява информация за един филм в системата
class Movie {
private:
    int id;                  // уникален идентификатор на филма
    std::string title;       // заглавие на филма
    std::string genre;       // жанр (например "Action", "Comedy")
    int durationMinutes;     // продължителност на филма в минути
    std::string rating;       // възрастов рейтинг, напр. "PG-13"

public:
    // Конструктор - инициализира всички данни на филма
    Movie(int id, const std::string& title, const std::string& genre,
        int durationMinutes, const std::string& rating);

    // Връща идентификатора на филма
    int getId() const;

    // Връща заглавието на филма
    std::string getTitle() const;

    // Връща жанра на филма
    std::string getGenre() const;

    // Връща продължителността в минути
    int getDuration() const;

    // Връща възрастовия рейтинг
    std::string getRating() const;

    // Извежда информация за филма в конзолата (за удобство при показване)
    void print() const;
};

#endif // MOVIE_H