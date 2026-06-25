#include "Cinema.h"

Cinema::Cinema(int id, const std::string& name, const std::string& city) {
    this->id = id;
    this->name = name;
    this->city = city;
}

void Cinema::addHall(const Hall& hall) {
    halls.push_back(hall);
}

int Cinema::getId() const {
    return id;
}

std::string Cinema::getName() const {
    return name;
}

std::string Cinema::getCity() const {
    return city;
}

const std::vector<Hall>& Cinema::getHalls() const {
    return halls;
}

const Hall* Cinema::findHallById(int hallId) const {
    for (const Hall& h : halls) {
        if (h.getId() == hallId) {
            return &h;
        }
    }
    return nullptr;
}
