#include<iostream>

#include"Classes.h"
#include"Repository.h"
#include"Input.h"

using namespace kyrsach;


inline void printCandidatesMenu() {
    std::cout << "\n--- КАНДИДАТЫ ---\n"
        << "  1. Показать всех\n"
        << "  2. Найти по id\n"
        << "  0. Назад\n"
        << "-----------------\n";
}

inline void menuCandidates(Repository<Candidate>& candidates,
    Repository<Position>& positions) {
    (void)positions;

    bool running = true;
    while (running) {
        printCandidatesMenu();
        int choice = readInt("Выбор: ", 0, 2);

        switch (choice) {
        case 1: {
            std::cout << "\n=== Список кандидатов ===\n";
            printAll(candidates);
            break;
        }
        case 2: {
            int id = readInt("Введите id кандидата: ");
            try {
                Candidate* c = candidates.findById(id);
                std::cout << "\nНайден:\n  " << *c;
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