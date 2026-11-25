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
        << "  4. Отчёты\n"
        << "  5. Сохранить в файл\n"
        << "  6. Загрузить из файла\n"
        << "  0. Выход\n"
        << "====================================================\n";
}

int main() {
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    if (!login()) return 0;

    // Порядок объявления важен:
    // positions — первым → удалится последним.
    // employees/candidates — позже → удалятся раньше.
    // (Они держат невладеемые указатели на Position.)
    Repository<Position> positions;
    Repository<Employee> employees;
    Repository<Candidate> candidates;

    const std::string dataPrefix = "data_";

    bool running = true;
    while (running) {
        printMainMenu();
        int choice = readInt("Выбор: ", 0, 6);

        switch (choice) {
        case 1: employeesMenu(employees, positions); break;
        case 2: candidatesMenu(candidates, positions); break;
        case 3: positionsMenu(positions); break;
        case 4: reportsMenu(employees, candidates); break;
        case 5: {
            try {
                Storage::saveAll(dataPrefix, positions, employees, candidates);
                std::cout << "Данные сохранены ("
                    << dataPrefix << "positions.txt, "
                    << dataPrefix << "employees.txt, "
                    << dataPrefix << "candidates.txt).\n";
            }
            catch (const std::exception& ex) {
                std::cout << "Ошибка сохранения: " << ex.what() << "\n";
            }
            break;
        }
        case 6: {
            try {
                Storage::loadAll(dataPrefix, positions, employees, candidates);
                std::cout << "Данные загружены.\n"
                    << "  Должностей:  " << positions.size() << "\n"
                    << "  Сотрудников: " << employees.size() << "\n"
                    << "  Кандидатов:  " << candidates.size() << "\n";
            }
            catch (const std::exception& ex) {
                std::cout << "Ошибка загрузки: " << ex.what() << "\n";
            }
            break;
        }
        case 0:
            running = false;
            std::cout << "Выход. До свидания.\n";
            break;
        }
    }
    return 0;
}