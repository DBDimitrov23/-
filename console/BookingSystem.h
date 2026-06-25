#pragma once
#ifndef BOOKING_SYSTEM_H
#define BOOKING_SYSTEM_H

#include <vector>
#include <string>
#include "Movie.h"
#include "Cinema.h"
#include "Show.h"
#include "Customer.h"
#include "Booking.h"

// Класът BookingSystem е "сърцето" на цялото приложение.
// Той пази всички данни (филми, кина, прожекции, клиенти, резервации)
// и предоставя методи за търсене, резервиране и плащане,
// както и конзолно меню (run), с което потребителят взаимодейства.
class BookingSystem {
private:
    std::vector<Movie> movies;        // всички филми в системата
    std::vector<Cinema> cinemas;      // всички кина в системата
    std::vector<Show> shows;          // всички прожекции в системата
    std::vector<Customer> customers;  // всички регистрирани клиенти
    std::vector<Booking> bookings;    // история на всички резервации

    int nextMovieId;     // брояч за генериране на следващото ID за филм
    int nextCinemaId;    // брояч за следващо ID за кино
    int nextShowId;      // брояч за следващо ID за прожекция
    int nextCustomerId;  // брояч за следващо ID за клиент
    int nextBookingId;   // брояч за следващо ID за резервация

    // Помощен метод - намира индекс на прожекция по ID; връща -1 ако не е намерена
    int findShowIndexById(int showId) const;

    // Помощен метод - зарежда примерни (демонстрационни) данни в системата
    void seedDemoData();

public:
    // Конструктор - инициализира брояч-ите и зарежда примерни данни
    BookingSystem();

    // Добавя нов филм и връща неговото ново ID
    int addMovie(const std::string& title, const std::string& genre,
        int duration, const std::string& rating);

    // Добавя ново кино (без салони) и връща неговото ново ID
    int addCinema(const std::string& name, const std::string& city);

    // Добавя салон към вече съществуващо кино (по cinemaId)
    void addHallToCinema(int cinemaId, const std::string& hallName, int rows, int seatsPerRow);

    // Добавя нова прожекция за филм в определено кино/салон
    int addShow(int movieId, int cinemaId, const std::string& hallName,
        const std::string& dateTime, double price);

    // Регистрира нов клиент и връща неговото ID
    int registerCustomer(const std::string& name, const std::string& email);

    // Извежда списък с всички филми
    void listAllMovies() const;

    // Извежда списък с всички кина и техните салони
    void listAllCinemas() const;

    // Извежда всички прожекции на филм с дадено ID
    void listShowsForMovie(int movieId) const;

    // Извежда схемата на местата за конкретна прожекция (по showId)
    void showSeatLayout(int showId) const;

    // Прави резервация: проверява местата, резервира ги и създава Booking обект
    // Връща ID на новата резервация при успех, или -1 при неуспех
    int createBooking(int customerId, int showId, const std::vector<std::pair<int, int>>& seats);

    // Обработва плащане по резервация - маркира я като платена и изпраща имейл
    bool payForBooking(int bookingId);

    // Търси филм по заглавие (частично съвпадение, без значение от главни/малки букви)
    std::vector<int> searchMoviesByTitle(const std::string& keyword) const;

    // Стартира главното интерактивно конзолно меню на приложението
    void run();
};

#endif // BOOKING_SYSTEM_H