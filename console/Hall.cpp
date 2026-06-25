#include "Hall.h"

// Конструктор - запазва данните за салона
Hall::Hall(int id, const std::string& name, int rows, int seatsPerRow) {
    this->id = id;                  // запазваме ID на салона
    this->name = name;              // запазваме името
    this->rows = rows;              // запазваме броя редове
    this->seatsPerRow = seatsPerRow; // запазваме броя места на ред
}

// Геттър - връща ID
int Hall::getId() const {
    return id;
}

// Геттър - връща името на салона
std::string Hall::getName() const {
    return name;
}

// Геттър - връща броя редове
int Hall::getRows() const {
    return rows;
}

// Геттър - връща броя места на ред
int Hall::getSeatsPerRow() const {
    return seatsPerRow;
}

// Изчислява и връща общия капацитет на салона
int Hall::getCapacity() const {
    return rows * seatsPerRow; // умножаваме редовете по местата на ред
}