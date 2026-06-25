#include "Movie.h"
#include <iostream>

Movie::Movie(int id, const std::string& title, const std::string& genre,
    int durationMinutes, const std::string& rating) {
    this->id = id;
    this->title = title;
    this->genre = genre;
    this->durationMinutes = durationMinutes;
    this->rating = rating;
}

int Movie::getId() const {
    return id;
}

std::string Movie::getTitle() const {
    return title;
}

std::string Movie::getGenre() const {
    return genre;
}

int Movie::getDuration() const {
    return durationMinutes;
}

std::string Movie::getRating() const {
    return rating;
}

void Movie::print() const {
    std::cout << "[" << id << "] " << title
        << " | Genre: " << genre
        << " | Duration: " << durationMinutes << " min"
        << " | Rating: " << rating << std::endl;
}
