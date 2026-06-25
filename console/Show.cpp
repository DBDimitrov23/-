#include "Show.h"
#include <iostream>
#include <iomanip>

// Конструктор - запазва данните за прожекцията и генерира мрежа от свободни места
Show::Show(int id, int movieId, const std::string& movieTitle,
    const std::string& cinemaName, const std::string& hallName,
    const std::string& dateTime, double price,
    int rows, int seatsPerRow) {
    this->id = id;                   // запазваме ID на прожекцията
    this->movieId = movieId;         // запазваме ID на филма
    this->movieTitle = movieTitle;   // запазваме заглавието
    this->cinemaName = cinemaName;   // запазваме името на киното
    this->hallName = hallName;       // запазваме името на салона
    this->dateTime = dateTime;       // запазваме датата/часа
    this->price = price;             // запазваме цената
    this->rows = rows;               // запазваме броя редове
    this->seatsPerRow = seatsPerRow; // запазваме броя места на ред

    // Генерираме двумерната мрежа от места - всички места стартират свободни
    for (int r = 0; r < rows; r++) {                  // за всеки ред
        std::vector<Seat> rowOfSeats;                  // създаваме празен ред
        for (int s = 0; s < seatsPerRow; s++) {         // за всяко място в реда
            rowOfSeats.push_back(Seat(r, s));            // създаваме ново свободно място
        }
        seats.push_back(rowOfSeats);                    // добавяме готовия ред в мрежата
    }
}

// Геттър - ID на прожекцията
int Show::getId() const {
    return id;
}

// Геттър - ID на филма
int Show::getMovieId() const {
    return movieId;
}

// Геттър - заглавие на филма
std::string Show::getMovieTitle() const {
    return movieTitle;
}

// Геттър - име на киното
std::string Show::getCinemaName() const {
    return cinemaName;
}

// Геттър - име на салона
std::string Show::getHallName() const {
    return hallName;
}

// Геттър - дата и час
std::string Show::getDateTime() const {
    return dateTime;
}

// Геттър - цена на билет
double Show::getPrice() const {
    return price;
}

// Извежда визуална схема на местата - 'X' за заето, номер за свободно
void Show::displaySeatLayout() const {
    std::cout << "\n--- Схема на местата за \"" << movieTitle << "\" ---\n";
    std::cout << "    "; // отстъп преди номерата на колоните
    for (int s = 0; s < seatsPerRow; s++) {           // печатаме заглавен ред с номерата на местата
        std::cout << std::setw(4) << (s + 1);           // подравняваме всяко число на 4 символа
    }
    std::cout << std::endl;

    for (int r = 0; r < rows; r++) {                   // за всеки ред от мрежата
        char rowLetter = 'A' + r;                       // буквата на реда (A, B, C...)
        std::cout << " " << rowLetter << "  ";           // изписваме буквата на реда отпред
        for (int s = 0; s < seatsPerRow; s++) {           // за всяко място в реда
            if (seats[r][s].isBooked()) {                  // ако мястото е заето
                std::cout << std::setw(4) << "X";            // показваме "X"
            }
            else {
                std::cout << std::setw(4) << (s + 1);         // иначе показваме номера му (свободно)
            }
        }
        std::cout << std::endl; // нов ред след всеки ред с места
    }
    std::cout << "(X = заето място, число = свободно място с този номер)\n";
}

// Проверява дали посоченото място съществува и е свободно
bool Show::isSeatAvailable(int row, int number) const {
    if (row < 0 || row >= rows || number < 0 || number >= seatsPerRow) {
        return false; // координатите са извън границите на салона - невалидно място
    }
    return !seats[row][number].isBooked(); // връщаме обратното на "заето", т.е. дали е свободно
}

// Опитва да резервира списък от места наведно (всички или нищо)
bool Show::bookSeats(const std::vector<std::pair<int, int>>& seatList) {
    // Първо проверяваме дали ВСИЧКИ места от списъка са свободни
    for (const std::pair<int, int>& pos : seatList) {     // обхождаме всяка двойка (ред, номер)
        if (!isSeatAvailable(pos.first, pos.second)) {     // ако дори едно е заето или невалидно
            return false;                                    // отказваме цялата резервация
        }
    }
    // Ако всички места са били свободни, едвам сега ги маркираме като заети
    for (const std::pair<int, int>& pos : seatList) {
        seats[pos.first][pos.second].book(); // маркираме конкретното място като заето
    }
    return true; // резервацията е успешна
}

// Освобождава вече заети места (например при отказ от плащане)
void Show::releaseSeats(const std::vector<std::pair<int, int>>& seatList) {
    for (const std::pair<int, int>& pos : seatList) {            // за всяка двойка (ред, номер)
        if (pos.first >= 0 && pos.first < rows &&                 // проверка за валидни граници
            pos.second >= 0 && pos.second < seatsPerRow) {
            seats[pos.first][pos.second].cancel();                  // освобождаваме мястото
        }
    }
}

// Изчислява крайна цена като умножава цената на билет по броя места
double Show::calculateTotalPrice(int numberOfSeats) const {
    return price * numberOfSeats; // прост модел на цена - линейно умножение
}