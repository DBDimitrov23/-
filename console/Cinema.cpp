#include "Cinema.h"

// Конструктор - запазва ID, име и град на киното
Cinema::Cinema(int id, const std::string& name, const std::string& city) {
    this->id = id;       // запазваме ID
    this->name = name;   // запазваме името
    this->city = city;   // запазваме града
    // векторът halls остава празен и се запълва чрез addHall()
}

// Добавя салон към вектора със салони на киното
void Cinema::addHall(const Hall& hall) {
    halls.push_back(hall); // добавяме копие на подадения салон в края на вектора
}

// Геттър - връща ID на киното
int Cinema::getId() const {
    return id;
}

// Геттър - връща името на киното
std::string Cinema::getName() const {
    return name;
}

// Геттър - връща града на киното
std::string Cinema::getCity() const {
    return city;
}

// Връща всички салони (като константна референция - не позволява промяна отвън)
const std::vector<Hall>& Cinema::getHalls() const {
    return halls;
}

// Търси салон по ID чрез обхождане на вектора
const Hall* Cinema::findHallById(int hallId) const {
    for (const Hall& h : halls) {     // обхождаме всеки салон в киното
        if (h.getId() == hallId) {    // проверяваме дали ID-то съвпада
            return &h;                 // ако намерим - връщаме адреса му
        }
    }
    return nullptr; // ако не намерим салон с такова ID, връщаме nullptr
}