#pragma once
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

class Customer {
private:
    int id;
    std::string name;
    std::string email;

public:
    Customer(int id = 0, const std::string& name = "", const std::string& email = "");

    int getId() const;

    std::string getName() const;

    std::string getEmail() const;
};

#endif // CUSTOMER_H
