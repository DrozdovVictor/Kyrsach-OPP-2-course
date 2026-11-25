#pragma once
#include<iostream>

#include"Classes.h"
#include"Utilities.h"

using namespace kyrsach;

inline void printPositionsMenu() {
    std::cout << "\n--- ДОЛЖНОСТИ ---\n"
        << "  1. Показать все\n"
        << "  2. Создать\n"
        << "  0. Назад\n"
        << "-----------------\n";
}
inline Position* createPositionInteractive() {
    std::cout << "\n--- Создание должности ---\n";
    std::string title;
    do {
        title = readLine("Название: ");
        if (title.empty())
            std::cout << "Название не может быть пустым.\n";
    } while (title.empty());

    int grade = readInt(
        "Грейд (0-юниор, 1-мидл, 2-сеньор, 3-лид): ",
        GRADE_JUNIOR, GRADE_LEAD);

    return new Position(title, grade);
}
inline void positionsMenu(Repository<Position>& positions) {
    bool running = true;
    while (running) {
        printPositionsMenu();
        int choice = readInt("Выбор: ", 0, 2);

        switch (choice) {
        case 1: {
            std::cout << "\n=== Список должностей ===\n";
            if (positions.empty()) {
                std::cout << "  (пусто)\n";
            }
            else {
                printPositionsTable(positions);
            }
            break;
        }
        case 2: {
            try {
                Position* p = createPositionInteractive();
                std::cout << "  Должность добавлена: " << p->getTitle() << "\n";
                positions.add(p);
            }
            catch (const ValidationException& ex) {
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