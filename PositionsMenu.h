#pragma once
#include<iostream>

#include"Classes.h"
#include"Repository.h"
#include"Input.h"

using namespace kyrsach;

inline void printPositionsMenu() {
    std::cout << "\n--- ДОЛЖНОСТИ ---\n"
        << "  1. Показать все\n"
        << "  0. Назад\n"
        << "-----------------\n";
}

inline void menuPositions(Repository<Position>& positions) {
    bool running = true;
    while (running) {
        printPositionsMenu();
        int choice = readInt("Выбор: ", 0, 1);

        switch (choice) {
        case 1: {
            std::cout << "\n=== Список должностей ===\n";
            if (positions.empty()) {
                std::cout << "  (пусто)\n";
            }
            else {
                for (Position* p : positions.getAll()) {
                    std::cout << "  " << p->getTitle()
                        << " | грейд: " << p->getGrade()
                        << " | оклад: " << p->getBaseSalary()
                        << "\n";
                }
            }
            break;
        }
        case 0:
            running = false;
            break;
        }
    }
}