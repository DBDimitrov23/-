#include "Seat.h"

// Конструктор - инициализира реда, номера и задава мястото като свободно
Seat::Seat(int row, int number) {
    this->row = row;          // запазваме подадения ред
    this->number = number;    // запазваме подадения номер
    this->booked = false;     // ново място винаги е свободно
}

// Геттър за реда
int Seat::getRow() const {
    return row; // просто връщаме стойността на полето row
}

// Геттър за номера на мястото
int Seat::getNumber() const {
    return number; // връщаме стойността на полето number
}

// Проверка дали мястото е заето
bool Seat::isBooked() const {
    return booked; // връщаме текущия статус на резервацията
}

// Маркиране на мястото като заето
void Seat::book() {
    booked = true; // сменяме статуса на "заето"
}

// Освобождаване на мястото
void Seat::cancel() {
    booked = false; // сменяме статуса обратно на "свободно"
}

// Генерира четим етикет на мястото, напр. ред 0 -> 'A', номер 0 -> "1"
std::string Seat::getLabel() const {
    char rowLetter = 'A' + row;                 // превръщаме числото на реда в буква (0->A, 1->B,...)
    std::string label = "";                      // подготвяме празен низ за резултата
    label += rowLetter;                           // добавяме буквата на реда
    label += std::to_string(number + 1);          // добавяме номера на мястото (показваме от 1, не от 0)
    return label;                                  // връщаме готовия етикет, напр. "A3"
}