#include<iostream>

#include"Classes.h"
#include"Repository.h"
#include"Input.h"

using namespace kyrsach;

inline void printEmployeesMenu() {
    std::cout << "\n--- СОТРУДНИКИ ---\n"
        << "  1. Показать всех\n"
        << "  2. Найти по id\n"
        << "  0. Назад\n"
        << "------------------\n";
}

inline void menuEmployees(Repository<Employee>& employees,
    Repository<Position>& positions) {
    (void)positions;   // пока не используется

    bool running = true;
    while (running) {
        printEmployeesMenu();
        int choice = readInt("Выбор: ", 0, 2);

        switch (choice) {
        case 1: {
            std::cout << "\n=== Список сотрудников ===\n";
            printAll(employees);
            break;
        }
        case 2: {
            int id = readInt("Введите id сотрудника: ");
            try {
                Employee* e = employees.findById(id);
                std::cout << "\nНайден:\n  " << *e;
            }
            catch (const NotFoundException& ex) {
                std::cout << "Ошибка: " << ex.what() << "\n";
            }
            break;
        }
        case 0:
            running = false;
            break;
        }
    }
}