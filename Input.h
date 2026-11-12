#pragma once
#include <iostream>
#include <string>

#include "Person.h"

namespace kyrsach {

    const int INT_MIN = 0;
    const int INT_MAX = 100;

    inline void clearInput() {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
    }

    inline int readInt(const std::string& prompt,
        int min = INT_MIN, int max = INT_MAX) {
        while (true) {
            std::cout << prompt;
            int x;
            std::cin >> x;
            if (std::cin.fail()) {
                clearInput();
                std::cout << "Ошибка: введите целое число.\n";
                continue;
            }
            clearInput();
            if (x < min || x > max) {
                std::cout << "Ошибка: число должно быть в [" << min << ", " << max << "].\n";
                continue;
            }
            return x;
        }
    }

    inline double readDouble(const std::string& prompt, double min = 0.0) {
        while (true) {
            std::cout << prompt;
            double x;
            std::cin >> x;
            if (std::cin.fail()) {
                clearInput();
                std::cout << "Ошибка: введите число.\n";
                continue;
            }
            clearInput();
            if (x < min) {
                std::cout << "Ошибка: число должно быть >= " << min << ".\n";
                continue;
            }
            return x;
        }
    }

    inline std::string readLine(const std::string& prompt) {
        std::cout << prompt;
        std::string s;
        std::getline(std::cin, s);
        return s;
    }

    inline Date readDate(const std::string& prompt) {
        while (true) {
            std::cout << prompt << " (дд мм гггг): ";
            Date d;
            std::cin >> d.day >> d.month >> d.year;
            if (std::cin.fail()) {
                clearInput();
                std::cout << "Ошибка: введите три целых числа.\n";
                continue;
            }
            clearInput();
            if (d.day < 1 || d.day > 31 || d.month < 1 || d.month > 12 || d.year < 1900) {
                std::cout << "Ошибка: некорректная дата.\n";
                continue;
            }
            return d;
        }
    }

    inline ContactInfo readContactInfo(const std::string& prompt) {
        std::cout << "--- " << prompt << " ---\n";
        ContactInfo c;
        c.phone = readLine("Телефон: ");
        c.email = readLine("Email:   ");
        c.address = readLine("Адрес:   ");
        return c;
    }

}