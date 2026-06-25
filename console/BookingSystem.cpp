#include "BookingSystem.h"
#include "EmailService.h"
#include <iostream>
#include <algorithm>
#include <limits>

// Конструктор - инициализираме всички брояч-и от 1 и зареждаме демонстрационни данни
BookingSystem::BookingSystem() {
    nextMovieId = 1;     // ID-тата на филмите ще започват от 1
    nextCinemaId = 1;    // ID-тата на кината ще започват от 1
    nextShowId = 1;      // ID-тата на прожекциите ще започват от 1
    nextCustomerId = 1;  // ID-тата на клиентите ще започват от 1
    nextBookingId = 1;   // ID-тата на резервациите ще започват от 1
    seedDemoData();      // зареждаме примерни филми/кина/прожекции, за да има с какво да се тества системата
}

// Добавя нов филм в системата
int BookingSystem::addMovie(const std::string& title, const std::string& genre,
    int duration, const std::string& rating) {
    Movie m(nextMovieId, title, genre, duration, rating); // създаваме обект Movie с текущото свободно ID
    movies.push_back(m);                                   // добавяме филма във вектора с филми
    return nextMovieId++;                                  // връщаме ID-то и след това го увеличаваме за следващия филм
}

// Добавя ново кино (без салони засега)
int BookingSystem::addCinema(const std::string& name, const std::string& city) {
    Cinema c(nextCinemaId, name, city); // създаваме ново кино
    cinemas.push_back(c);                // добавяме го във вектора с кина
    return nextCinemaId++;               // връщаме и увеличаваме ID-то
}

// Добавя салон към кино с дадено cinemaId
void BookingSystem::addHallToCinema(int cinemaId, const std::string& hallName, int rows, int seatsPerRow) {
    for (Cinema& c : cinemas) {              // обхождаме всички кина
        if (c.getId() == cinemaId) {           // намираме киното с подаденото ID
            int hallId = (int)c.getHalls().size() + 1; // генерираме просто ID на салона (поред в киното)
            Hall h(hallId, hallName, rows, seatsPerRow); // създаваме новия салон
            c.addHall(h);                                   // добавяме салона към киното
            return;                                          // приключваме - намерили сме киното
        }
    }
    std::cout << "Грешка: няма кино с ID " << cinemaId << std::endl; // ако не намерим кино с такъв ID
}

// Добавя прожекция - свързва филм, кино и конкретен салон в определени дата/час и цена
int BookingSystem::addShow(int movieId, int cinemaId, const std::string& hallName,
    const std::string& dateTime, double price) {
    // Първо намираме филма по ID, за да вземем заглавието му
    std::string movieTitle = "";
    bool movieFound = false;
    for (const Movie& m : movies) {            // обхождаме всички филми
        if (m.getId() == movieId) {              // проверяваме за съвпадение по ID
            movieTitle = m.getTitle();             // запазваме заглавието
            movieFound = true;                     // отбелязваме, че сме го намерили
            break;                                  // прекъсваме търсенето
        }
    }
    if (!movieFound) {
        std::cout << "Грешка: няма филм с ID " << movieId << std::endl;
        return -1; // връщаме -1 при неуспех
    }

    // После намираме киното и конкретния салон в него по име
    for (const Cinema& c : cinemas) {                 // обхождаме всички кина
        if (c.getId() == cinemaId) {                    // намираме желаното кино
            for (const Hall& h : c.getHalls()) {           // обхождаме салоните на това кино
                if (h.getName() == hallName) {                // намираме салона по име
                    // създаваме новата прожекция със всички нужни данни
                    Show s(nextShowId, movieId, movieTitle, c.getName(), h.getName(),
                        dateTime, price, h.getRows(), h.getSeatsPerRow());
                    shows.push_back(s);            // добавяме прожекцията в общия списък
                    return nextShowId++;            // връщаме и увеличаваме ID-то
                }
            }
            std::cout << "Грешка: киното няма салон с име \"" << hallName << "\"\n";
            return -1;
        }
    }
    std::cout << "Грешка: няма кино с ID " << cinemaId << std::endl;
    return -1;
}

// Регистрира нов клиент в системата
int BookingSystem::registerCustomer(const std::string& name, const std::string& email) {
    Customer c(nextCustomerId, name, email); // създаваме нов клиент
    customers.push_back(c);                    // добавяме го във вектора с клиенти
    return nextCustomerId++;                   // връщаме и увеличаваме ID-то
}

// Извежда списък с всички налични филми
void BookingSystem::listAllMovies() const {
    std::cout << "\n=== Списък с филми ===\n";
    for (const Movie& m : movies) { // обхождаме всеки филм
        m.print();                    // използваме метода print() на класа Movie
    }
}

// Извежда списък с всички кина, градовете им и салоните им
void BookingSystem::listAllCinemas() const {
    std::cout << "\n=== Списък с кина ===\n";
    for (const Cinema& c : cinemas) {                                  // за всяко кино
        std::cout << "[" << c.getId() << "] " << c.getName()             // показваме ID и име
            << " - гр. " << c.getCity() << std::endl;                // показваме града
        for (const Hall& h : c.getHalls()) {                                // за всеки салон в киното
            std::cout << "    Салон: " << h.getName()                       // показваме името на салона
                << " (капацитет: " << h.getCapacity() << " места)\n";    // и капацитета му
        }
    }
}

// Извежда всички прожекции на филм с дадено movieId
void BookingSystem::listShowsForMovie(int movieId) const {
    std::cout << "\n=== Прожекции ===\n";
    bool found = false;
    for (const Show& s : shows) {                  // обхождаме всички прожекции
        if (s.getMovieId() == movieId) {              // филтрираме само тези за желания филм
            found = true;
            std::cout << "[Прожекция №" << s.getId() << "] " << s.getCinemaName()  // ID и кино
                << " - " << s.getHallName()                                      // салон
                << " | " << s.getDateTime()                                       // дата/час
                << " | Цена: " << s.getPrice() << " лв.\n";                          // цена
        }
    }
    if (!found) {
        std::cout << "Няма намерени прожекции за този филм.\n";
    }
}

// Помощен метод - намира индекс на прожекция във вектора по нейното ID
int BookingSystem::findShowIndexById(int showId) const {
    for (size_t i = 0; i < shows.size(); i++) {  // обхождаме всички прожекции по индекс
        if (shows[i].getId() == showId) {          // проверяваме за съвпадение по ID
            return (int)i;                            // връщаме намерения индекс
        }
    }
    return -1; // ако не намерим, връщаме -1
}

// Показва схемата на местата за конкретна прожекция
void BookingSystem::showSeatLayout(int showId) const {
    int idx = findShowIndexById(showId); // търсим индекса на прожекцията
    if (idx == -1) {
        std::cout << "Грешка: няма прожекция с ID " << showId << std::endl;
        return;
    }
    shows[idx].displaySeatLayout(); // делегираме на метода на класа Show
}

// Създава резервация - проверява и резервира местата в прожекцията
int BookingSystem::createBooking(int customerId, int showId, const std::vector<std::pair<int, int>>& seats) {
    int showIdx = findShowIndexById(showId); // намираме индекса на прожекцията
    if (showIdx == -1) {
        std::cout << "Грешка: невалидна прожекция.\n";
        return -1;
    }

    // Търсим клиента по подаденото customerId
    Customer* foundCustomer = nullptr;
    for (Customer& c : customers) {       // обхождаме всички клиенти
        if (c.getId() == customerId) {      // проверяваме за съвпадение
            foundCustomer = &c;                // запазваме адреса на намерения клиент
            break;
        }
    }
    if (foundCustomer == nullptr) {
        std::cout << "Грешка: невалиден клиент.\n";
        return -1;
    }

    // Опитваме да резервираме местата в самата прожекция (атомарно - всички или нищо)
    bool success = shows[showIdx].bookSeats(seats);
    if (!success) {
        std::cout << "Грешка: едно или повече от избраните места вече са заети или не съществуват.\n";
        return -1;
    }

    // Изчисляваме обща цена според броя избрани места
    double totalPrice = shows[showIdx].calculateTotalPrice((int)seats.size());

    // Създаваме нов обект Booking, който пази информация за резервацията
    Booking newBooking(nextBookingId, *foundCustomer, shows[showIdx], seats, totalPrice);
    bookings.push_back(newBooking); // добавяме резервацията в историята

    std::cout << "Местата са успешно резервирани (временно, до плащане)!\n";
    return nextBookingId++; // връщаме ID на новата резервация и увеличаваме брояча
}

// Обработва плащане по съществуваща резервация
bool BookingSystem::payForBooking(int bookingId) {
    for (Booking& b : bookings) {           // обхождаме всички резервации
        if (b.getId() == bookingId) {         // намираме резервацията по ID
            if (b.isPaymentCompleted()) {       // проверка - ако вече е платена
                std::cout << "Тази резервация вече е платена.\n";
                return false;
            }
            b.confirmPayment();                  // маркираме плащането като завършено
            b.printTicket();                       // отпечатваме готовия билет
            EmailService::sendBookingConfirmation(b.getCustomer(), b); // изпращаме (симулирано) имейл
            return true;
        }
    }
    std::cout << "Грешка: няма резервация с ID " << bookingId << std::endl;
    return false;
}

// Търси филми по заглавие - проверява дали ключовата дума се съдържа в заглавието
std::vector<int> BookingSystem::searchMoviesByTitle(const std::string& keyword) const {
    std::vector<int> result;                        // тук ще съберем ID-тата на намерените филми

    // Превръщаме ключовата дума в малки букви за търсене без значение от регистъра
    std::string lowerKeyword = keyword;
    std::transform(lowerKeyword.begin(), lowerKeyword.end(), lowerKeyword.begin(), ::tolower);

    for (const Movie& m : movies) {                 // обхождаме всички филми
        std::string lowerTitle = m.getTitle();         // вземаме заглавието
        std::transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower); // в малки букви

        if (lowerTitle.find(lowerKeyword) != std::string::npos) { // ако ключовата дума се среща в заглавието
            result.push_back(m.getId());                            // добавяме ID-то на филма в резултата
        }
    }
    return result; // връщаме списъка с намерени ID-та (може да е празен)
}

// Зарежда примерни данни, за да може системата да се тества веднага след стартиране
void BookingSystem::seedDemoData() {
    // Добавяме няколко примерни филма
    int m1 = addMovie("Интерстелар", "Sci-Fi", 169, "PG-13");
    int m2 = addMovie("Тъмният рицар", "Action", 152, "PG-13");
    int m3 = addMovie("Зеленият път", "Drama", 189, "R");

    // Добавяме примерно кино с два салона
    int c1 = addCinema("Cinema City", "София");
    addHallToCinema(c1, "Зала 1", 5, 8);   // 5 реда х 8 места = 40 места
    addHallToCinema(c1, "Зала 2", 4, 6);   // 4 реда х 6 места = 24 места

    // Добавяме второ кино с един салон в друг град
    int c2 = addCinema("Arena Mall Cinema", "Пловдив");
    addHallToCinema(c2, "VIP Зала", 3, 5); // 3 реда х 5 места = 15 места

    // Добавяме няколко прожекции, използвайки вече създадените филми и салони
    addShow(m1, c1, "Зала 1", "2026-06-25 19:00", 12.50);
    addShow(m1, c2, "VIP Зала", "2026-06-26 21:00", 18.00);
    addShow(m2, c1, "Зала 2", "2026-06-25 20:30", 11.00);
    addShow(m3, c1, "Зала 1", "2026-06-27 18:00", 12.50);
}

// Главното интерактивно меню на приложението - работи в безкраен цикъл, докато потребителят не избере "Изход"
void BookingSystem::run() {
    int choice = 0; // ще пазим избора на потребителя от менюто

    // Първо регистрираме "текущ" клиент за демонстрационни цели
    std::cout << "=== Добре дошли в системата за резервация на билети за кино ===\n";
    std::string name, email;
    std::cout << "Въведете Вашето име: ";
    std::getline(std::cin, name);                 // четем цял ред (за да хванем име с интервал)
    std::cout << "Въведете Вашия имейл: ";
    std::getline(std::cin, email);                 // четем имейла на потребителя
    int customerId = registerCustomer(name, email); // регистрираме клиента и пазим ID-то му

    while (true) { // безкраен цикъл - менюто се показва, докато потребителят не избере изход
        std::cout << "\n========= МЕНЮ =========\n";
        std::cout << "1. Покажи всички филми\n";
        std::cout << "2. Покажи всички кина\n";
        std::cout << "3. Търси филм по заглавие\n";
        std::cout << "4. Покажи прожекции за филм (по ID)\n";
        std::cout << "5. Покажи схема на местата за прожекция (по ID)\n";
        std::cout << "6. Резервирай билети\n";
        std::cout << "7. Плати за резервация (по ID на резервация)\n";
        std::cout << "0. Изход\n";
        std::cout << "Изберете опция: ";
        std::cin >> choice; // четем избора (число)

        if (std::cin.fail()) { // защита при невалиден (нечислов) вход
            std::cin.clear();    // изчистваме грешния флаг на потока
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // изхвърляме остатъка от реда
            std::cout << "Невалиден вход. Опитайте отново.\n";
            continue; // връщаме се в началото на цикъла
        }

        if (choice == 0) {
            std::cout << "Благодарим Ви, че използвахте системата! Довиждане!\n";
            break; // излизаме от цикъла (и от метода run)
        }
        else if (choice == 1) {
            listAllMovies(); // показваме всички филми
        }
        else if (choice == 2) {
            listAllCinemas(); // показваме всички кина
        }
        else if (choice == 3) {
            std::cin.ignore();                          // изчистваме остатъчния символ за нов ред в буфера
            std::string keyword;
            std::cout << "Въведете ключова дума за търсене: ";
            std::getline(std::cin, keyword);              // четем търсения текст
            std::vector<int> found = searchMoviesByTitle(keyword); // извикваме търсенето
            if (found.empty()) {
                std::cout << "Няма намерени филми.\n";
            }
            else {
                std::cout << "Намерени филми:\n";
                for (int id : found) {                       // обхождаме намерените ID-та
                    for (const Movie& m : movies) {             // намираме самия филм по ID
                        if (m.getId() == id) {
                            m.print(); // показваме информацията му
                        }
                    }
                }
            }
        }
        else if (choice == 4) {
            int movieId;
            std::cout << "Въведете ID на филма: ";
            std::cin >> movieId;
            listShowsForMovie(movieId); // показваме прожекциите за този филм
        }
        else if (choice == 5) {
            int showId;
            std::cout << "Въведете ID на прожекцията: ";
            std::cin >> showId;
            showSeatLayout(showId); // показваме схемата на местата
        }
        else if (choice == 6) {
            int showId, numSeats;
            std::cout << "Въведете ID на прожекцията: ";
            std::cin >> showId;

            showSeatLayout(showId); // първо показваме схемата, за да избере клиентът свободни места

            std::cout << "Колко места искате да резервирате? ";
            std::cin >> numSeats;

            std::vector<std::pair<int, int>> chosenSeats; // тук ще съберем избраните места
            for (int i = 0; i < numSeats; i++) {            // за всяко място, което клиентът иска
                int rowNum, seatNum;
                char rowLetter;
                std::cout << "Място #" << (i + 1) << " - въведете ред (буква, напр. A): ";
                std::cin >> rowLetter;
                std::cout << "Място #" << (i + 1) << " - въведете номер на мястото: ";
                std::cin >> seatNum;
                rowNum = (int)(toupper(rowLetter) - 'A');     // превръщаме буквата на реда в число (A->0, B->1...)
                chosenSeats.push_back(std::make_pair(rowNum, seatNum - 1)); // запазваме (ред, номер-1, защото вътрешно е от 0)
            }

            int bookingId = createBooking(customerId, showId, chosenSeats); // опитваме резервацията
            if (bookingId != -1) {
                std::cout << "Резервацията е успешна! Вашето ID на резервация е: " << bookingId << std::endl;
                std::cout << "Моля, изберете опция 7 от менюто, за да платите и потвърдите резервацията.\n";
            }
        }
        else if (choice == 7) {
            int bookingId;
            std::cout << "Въведете ID на резервацията за плащане: ";
            std::cin >> bookingId;
            payForBooking(bookingId); // обработваме плащането
        }
        else {
            std::cout << "Невалидна опция. Опитайте отново.\n";
        }
    }
}