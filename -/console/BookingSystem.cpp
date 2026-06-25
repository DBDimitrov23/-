#include "BookingSystem.h"
#include "EmailService.h"
#include <iostream>
#include <algorithm>
#include <limits>

BookingSystem::BookingSystem() {
    nextMovieId = 1;
    nextCinemaId = 1;
    nextShowId = 1;
    nextCustomerId = 1;
    nextBookingId = 1;
    seedDemoData();
}

int BookingSystem::addMovie(const std::string& title, const std::string& genre,
    int duration, const std::string& rating) {
    Movie m(nextMovieId, title, genre, duration, rating);
    movies.push_back(m);
    return nextMovieId++;
}

int BookingSystem::addCinema(const std::string& name, const std::string& city) {
    Cinema c(nextCinemaId, name, city);
    cinemas.push_back(c);
    return nextCinemaId++;
}

void BookingSystem::addHallToCinema(int cinemaId, const std::string& hallName, int rows, int seatsPerRow) {
    for (Cinema& c : cinemas) {
        if (c.getId() == cinemaId) {
            int hallId = (int)c.getHalls().size() + 1;
            Hall h(hallId, hallName, rows, seatsPerRow);
            c.addHall(h);
            return;
        }
    }
    std::cout << "Error: No cinema found with ID " << cinemaId << std::endl;
}

int BookingSystem::addShow(int movieId, int cinemaId, const std::string& hallName,
    const std::string& dateTime, double price) {
    std::string movieTitle = "";
    bool movieFound = false;
    for (const Movie& m : movies) {
        if (m.getId() == movieId) {
            movieTitle = m.getTitle();
            movieFound = true;
            break;
        }
    }
    if (!movieFound) {
        std::cout << "Error: No movie found with ID " << movieId << std::endl;
        return -1;
    }

    for (const Cinema& c : cinemas) {
        if (c.getId() == cinemaId) {
            for (const Hall& h : c.getHalls()) {
                if (h.getName() == hallName) {
                    Show s(nextShowId, movieId, movieTitle, c.getName(), h.getName(),
                        dateTime, price, h.getRows(), h.getSeatsPerRow());
                    shows.push_back(s);
                    return nextShowId++;
                }
            }
            std::cout << "Error: No hall found with name \"" << hallName << "\"\n";
            return -1;
        }
    }
    std::cout << "Error: No cinema found with ID " << cinemaId << std::endl;
    return -1;
}

int BookingSystem::registerCustomer(const std::string& name, const std::string& email) {
    Customer c(nextCustomerId, name, email);
    customers.push_back(c);
    return nextCustomerId++;
}

void BookingSystem::listAllMovies() const {
    std::cout << "\n=== All Movies ===\n";
    for (const Movie& m : movies) {
        m.print();
    }
}

void BookingSystem::listAllCinemas() const {
    std::cout << "\n=== All Cinemas ===\n";
    for (const Cinema& c : cinemas) {
        std::cout << "[" << c.getId() << "] " << c.getName()
            << " - " << c.getCity() << std::endl;
        for (const Hall& h : c.getHalls()) {
            std::cout << "    Hall: " << h.getName()
                << " (Capacity: " << h.getCapacity() << " seats)\n";
        }
    }
}

void BookingSystem::listShowsForMovie(int movieId) const {
    std::cout << "\n=== Screenings ===\n";
    bool found = false;
    for (const Show& s : shows) {
        if (s.getMovieId() == movieId) {
            found = true;
            std::cout << "[Screening #" << s.getId() << "] " << s.getCinemaName()
                << " - " << s.getHallName()
                << " | " << s.getDateTime()
                << " | Price: $" << s.getPrice() << std::endl;
        }
    }
    if (!found) {
        std::cout << "No screenings found for this movie.\n";
    }
}

int BookingSystem::findShowIndexById(int showId) const {
    for (size_t i = 0; i < shows.size(); i++) {
        if (shows[i].getId() == showId) {
            return (int)i;
        }
    }
    return -1;
}

void BookingSystem::showSeatLayout(int showId) const {
    int idx = findShowIndexById(showId);
    if (idx == -1) {
        std::cout << "Error: No screening found with ID " << showId << std::endl;
        return;
    }
    shows[idx].displaySeatLayout();
}

int BookingSystem::createBooking(int customerId, int showId, const std::vector<std::pair<int, int>>& seats) {
    int showIdx = findShowIndexById(showId);
    if (showIdx == -1) {
        std::cout << "Error: Screening not found.\n";
        return -1;
    }

    Customer* foundCustomer = nullptr;
    for (Customer& c : customers) {
        if (c.getId() == customerId) {
            foundCustomer = &c;
            break;
        }
    }
    if (foundCustomer == nullptr) {
        std::cout << "Error: Customer not found.\n";
        return -1;
    }

    bool success = shows[showIdx].bookSeats(seats);
    if (!success) {
        std::cout << "Error: Could not book seats. One or more seats may already be taken or invalid.\n";
        return -1;
    }

    double totalPrice = shows[showIdx].calculateTotalPrice((int)seats.size());

    Booking newBooking(nextBookingId, *foundCustomer, shows[showIdx], seats, totalPrice);
    bookings.push_back(newBooking);

    std::cout << "Booking created successfully (pending payment)!\n";
    return nextBookingId++;
}

bool BookingSystem::payForBooking(int bookingId) {
    for (Booking& b : bookings) {
        if (b.getId() == bookingId) {
            if (b.isPaymentCompleted()) {
                std::cout << "This booking has already been paid.\n";
                return false;
            }
            b.confirmPayment();
            b.printTicket();
            EmailService::sendBookingConfirmation(b.getCustomer(), b);
            return true;
        }
    }
    std::cout << "Error: No booking found with ID " << bookingId << std::endl;
    return false;
}

std::vector<int> BookingSystem::searchMoviesByTitle(const std::string& keyword) const {
    std::vector<int> result;

    std::string lowerKeyword = keyword;
    std::transform(lowerKeyword.begin(), lowerKeyword.end(), lowerKeyword.begin(), ::tolower);

    for (const Movie& m : movies) {
        std::string lowerTitle = m.getTitle();
        std::transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower);

        if (lowerTitle.find(lowerKeyword) != std::string::npos) {
            result.push_back(m.getId());
        }
    }
    return result;
}

void BookingSystem::seedDemoData() {
    int m1 = addMovie("Interstellar", "Sci-Fi", 169, "PG-13");
    int m2 = addMovie("The Avengers", "Action", 152, "PG-13");
    int m3 = addMovie("Life of Pi", "Drama", 189, "R");

    int c1 = addCinema("Cinema City", "Sofia");
    addHallToCinema(c1, "Hall 1", 5, 8);
    addHallToCinema(c1, "Hall 2", 4, 6);

    int c2 = addCinema("Arena Mall Cinema", "Varna");
    addHallToCinema(c2, "VIP Hall", 3, 5);

    addShow(m1, c1, "Hall 1", "2026-06-25 19:00", 12.50);
    addShow(m1, c2, "VIP Hall", "2026-06-26 21:00", 18.00);
    addShow(m2, c1, "Hall 2", "2026-06-25 20:30", 11.00);
    addShow(m3, c1, "Hall 1", "2026-06-27 18:00", 12.50);
}

void BookingSystem::run() {
    int choice = 0;

    std::cout << "=== Welcome to the Ticket Booking System ===\n";
    std::string name, email;
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);
    std::cout << "Enter your email: ";
    std::getline(std::cin, email);
    int customerId = registerCustomer(name, email);

    while (true) {
        std::cout << "\n========= MENU =========\n";
        std::cout << "1. View all movies\n";
        std::cout << "2. View all cinemas\n";
        std::cout << "3. Search movie by title\n";
        std::cout << "4. View screenings for a movie (by ID)\n";
        std::cout << "5. View seats for a specific screening (by ID)\n";
        std::cout << "6. Make a new booking\n";
        std::cout << "7. Pay for a booking (by booking ID)\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose an option: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please try again.\n";
            continue;
        }

        if (choice == 0) {
            std::cout << "Thank you for using the system! Goodbye!\n";
            break;
        }
        else if (choice == 1) {
            listAllMovies();
        }
        else if (choice == 2) {
            listAllCinemas();
        }
        else if (choice == 3) {
            std::cin.ignore();
            std::string keyword;
            std::cout << "Enter movie title to search: ";
            std::getline(std::cin, keyword);
            std::vector<int> found = searchMoviesByTitle(keyword);
            if (found.empty()) {
                std::cout << "No movies found.\n";
            }
            else {
                std::cout << "Found movies:\n";
                for (int id : found) {
                    for (const Movie& m : movies) {
                        if (m.getId() == id) {
                            m.print();
                        }
                    }
                }
            }
        }
        else if (choice == 4) {
            int movieId;
            std::cout << "Enter movie ID: ";
            std::cin >> movieId;
            listShowsForMovie(movieId);
        }
        else if (choice == 5) {
            int showId;
            std::cout << "Enter screening ID: ";
            std::cin >> showId;
            showSeatLayout(showId);
        }
        else if (choice == 6) {
            int showId, numSeats;
            std::cout << "Enter screening ID: ";
            std::cin >> showId;

            showSeatLayout(showId);

            std::cout << "How many seats do you want to book? ";
            std::cin >> numSeats;

            std::vector<std::pair<int, int>> chosenSeats;
            for (int i = 0; i < numSeats; i++) {
                int rowNum, seatNum;
                char rowLetter;
                std::cout << "Seat #" << (i + 1) << " - Enter row letter (e.g., A): ";
                std::cin >> rowLetter;
                std::cout << "Seat #" << (i + 1) << " - Enter seat number: ";
                std::cin >> seatNum;
                rowNum = (int)(toupper(rowLetter) - 'A');
                chosenSeats.push_back(std::make_pair(rowNum, seatNum - 1));
            }

            int bookingId = createBooking(customerId, showId, chosenSeats);
            if (bookingId != -1) {
                std::cout << "Booking successful! Your booking ID is: " << bookingId << std::endl;
                std::cout << "Please use option 7 from the menu to pay and confirm your booking.\n";
            }
        }
        else if (choice == 7) {
            int bookingId;
            std::cout << "Enter the booking ID to pay: ";
            std::cin >> bookingId;
            payForBooking(bookingId);
        }
        else {
            std::cout << "Invalid option. Please try again.\n";
        }
    }
}
