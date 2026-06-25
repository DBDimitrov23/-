#include "Movie.h"
#include <iostream>

// Конструктор - запазва подадените стойности във вътрешните полета
Movie::Movie(int id, const std::string& title, const std::string& genre,
    int durationMinutes, const std::string& rating) {
    this->id = id;                         // запазваме ID-то на филма
    this->title = title;                   // запазваме заглавието
    this->genre = genre;                   // запазваме жанра
    this->durationMinutes = durationMinutes; // запазваме продължителността
    this->rating = rating;                 // запазваме рейтинга
}

// Геттър - връща ID
int Movie::getId() const {
    return id;
}

// Геттър - връща заглавието
std::string Movie::getTitle() const {
    return title;
}

// Геттър - връща жанра
std::string Movie::getGenre() const {
    return genre;
}

// Геттър - връща продължителността в минути
int Movie::getDuration() const {
    return durationMinutes;
}

// Геттър - връща рейтинга
std::string Movie::getRating() const {
    return rating;
}

// Извежда подредена информация за филма в конзолата
void Movie::print() const {
    std::cout << "[" << id << "] " << title                 // показваме ID и заглавие
        << " | Жанр: " << genre                         // показваме жанра
        << " | Времетраене: " << durationMinutes << " мин" // показваме времетраенето
        << " | Рейтинг: " << rating << std::endl;        // показваме рейтинга и слизаме на нов ред
}