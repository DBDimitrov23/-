#include "Customer.h"

Customer::Customer(int id, const std::string& name, const std::string& email) {
    this->id = id;
    this->name = name;
    this->email = email;
}

int Customer::getId() const {
    return id;
}

std::string Customer::getName() const {
    return name;
}

std::string Customer::getEmail() const {
    return email;
}
