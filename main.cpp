#include <iostream>
#include <windows.h>

#include"Classes.h"
#include"Utilities.h"
#include"Menus.h"

using namespace kyrsach;

// Прямые объявления подменю.
void employeesMenu(Repository<Employee>& employees,
    Repository<Position>& positions);

void candidatesMenu(Repository<Candidate>& candidates,
    Repository<Position>& positions);

void positionsMenu(Repository<Position>& positions);

void createEmployeeMenu(Repository<Employee>& employees);

void menuEmployeeOperations(Repository<Employee>& employees,
    Repository<Position>& positions);

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
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
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
        case 1: employeesMenu(employees, positions); break;
        case 2: candidatesMenu(candidates, positions); break;
        case 3: positionsMenu(positions); break;
        case 0:
            running = false;
            std::cout << "Выход. До свидания.\n";
            break;
        }
    }
    return 0;
}