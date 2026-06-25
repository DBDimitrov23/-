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

class BookingSystem {
private:
    std::vector<Movie> movies;
    std::vector<Cinema> cinemas;
    std::vector<Show> shows;
    std::vector<Customer> customers;
    std::vector<Booking> bookings;

    int nextMovieId;
    int nextCinemaId;
    int nextShowId;
    int nextCustomerId;
    int nextBookingId;

    int findShowIndexById(int showId) const;

    void seedDemoData();

public:
    BookingSystem();

    int addMovie(const std::string& title, const std::string& genre,
        int duration, const std::string& rating);

    int addCinema(const std::string& name, const std::string& city);

    void addHallToCinema(int cinemaId, const std::string& hallName, int rows, int seatsPerRow);

    int addShow(int movieId, int cinemaId, const std::string& hallName,
        const std::string& dateTime, double price);

    int registerCustomer(const std::string& name, const std::string& email);

    void listAllMovies() const;

    void listAllCinemas() const;

    void listShowsForMovie(int movieId) const;

    void showSeatLayout(int showId) const;

    int createBooking(int customerId, int showId, const std::vector<std::pair<int, int>>& seats);

    bool payForBooking(int bookingId);

    std::vector<int> searchMoviesByTitle(const std::string& keyword) const;

    void run();
};

#endif // BOOKING_SYSTEM_H
