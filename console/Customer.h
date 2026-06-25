#pragma once
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>

// Класът Customer представя клиент на системата за резервации
class Customer {
private:
    int id;               // уникален идентификатор на клиента
    std::string name;     // име на клиента
    std::string email;    // имейл на клиента (за изпращане на потвърждение)

public:
    // Конструктор - инициализира клиента с ID, име и имейл
    Customer(int id = 0, const std::string& name = "", const std::string& email = "");

    // Връща ID на клиента
    int getId() const;

    // Връща името на клиента
    std::string getName() const;

    // Връща имейла на клиента
    std::string getEmail() const;
};

#endif // CUSTOMER_H