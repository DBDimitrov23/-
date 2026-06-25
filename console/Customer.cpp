#include "Customer.h"

// Конструктор - запазва ID, име и имейл на клиента
Customer::Customer(int id, const std::string& name, const std::string& email) {
    this->id = id;       // запазваме ID-то
    this->name = name;   // запазваме името
    this->email = email; // запазваме имейла
}

// Геттър - връща ID
int Customer::getId() const {
    return id;
}

// Геттър - връща името
std::string Customer::getName() const {
    return name;
}

// Геттър - връща имейла
std::string Customer::getEmail() const {
    return email;
}