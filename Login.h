#pragma once
#include <iostream>
#include <string>

#include"Input.h"

namespace kyrsach {
    inline bool login() {
        const std::string CORRECT_USER = "admin";
        const std::string CORRECT_PASS = "admin";
        const int MAX_ATTEMPTS = 3;

        for (int attempt = 1; attempt <= MAX_ATTEMPTS; ++attempt) {
            std::cout << "\n=== Вход в систему ===\n"
                << "Попытка " << attempt << " из " << MAX_ATTEMPTS << "\n";
            std::string user = readLine("Логин: ");
            std::string pass = readLine("Пароль: ");

            if (user == CORRECT_USER && pass == CORRECT_PASS) {
                std::cout << "Добро пожаловать, " << user << "!\n";
                return true;
            }
            std::cout << "Неверный логин или пароль.\n";
        }
        std::cout << "\nПревышено число попыток. Выход.\n";
        return false;
    }
}