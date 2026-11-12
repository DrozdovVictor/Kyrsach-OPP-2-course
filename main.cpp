#include <iostream>

#include"Classes.h"
#include "Repository.h"
#include "EmployeeFactory.h"
#include "Input.h"

using namespace kyrsach;

// Прямые объявления подменю.
// Реализации — ниже, пока заглушки.
void menuEmployees(Repository<Employee>& employees,
    Repository<Position>& positions);

void menuCandidates(Repository<Candidate>& candidates,
    Repository<Position>& positions);

void menuPositions(Repository<Position>& positions);

// Главное меню
void printMainMenu();
void printMainMenu() {
    std::cout << "\n========== СИСТЕМА УПРАВЛЕНИЯ ПЕРСОНАЛОМ ==========\n"
        << "  1. Сотрудники\n"
        << "  2. Кандидаты\n"
        << "  3. Должности\n"
        << "  0. Выход\n"
        << "====================================================\n";
}

int main() {
    setlocale(LC_ALL, "rus");
    // Порядок объявления важен:
    // positions — первым → удалится последним.
    // employees/candidates — позже → удалятся раньше.
    // (Они держат невладеемые указатели на Position.)
    Repository<Position> positions;
    Repository<Employee> employees;
    Repository<Candidate> candidates;

    bool running = true;
    while (running) {
        printMainMenu();
        int choice = readInt("Выбор: ", 0, 3);

        switch (choice) {
        case 1: menuEmployees(employees, positions); break;
        case 2: menuCandidates(candidates, positions); break;
        case 3: menuPositions(positions); break;
        case 0:
            running = false;
            std::cout << "Выход. До свидания.\n";
            break;
        }
    }
    return 0;
}

// Заглушки подменю (M1)
void menuEmployees(Repository<Employee>& employees,
    Repository<Position>& positions) {
    (void)employees;
    (void)positions;
    std::cout << "\n[Раздел «Сотрудники» — в разработке]\n";
}

void menuCandidates(Repository<Candidate>& candidates,
    Repository<Position>& positions) {
    (void)candidates;
    (void)positions;
    std::cout << "\n[Раздел «Кандидаты» — в разработке]\n";
}

void menuPositions(Repository<Position>& positions) {
    (void)positions;
    std::cout << "\n[Раздел «Должности» — в разработке]\n";
}