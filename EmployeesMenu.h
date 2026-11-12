#include<iostream>

#include"Classes.h"
#include"Utilities.h"

using namespace kyrsach;

inline void printCreateEmployeeMenu() {
    std::cout << "\n--- СОЗДАТЬ СОТРУДНИКА ---\n"
        << "  1. Разработчик\n"
        << "  2. Менеджер\n"
        << "  3. HR-специалист\n"
        << "  0. Назад\n"
        << "--------------------------\n";
}
inline Developer* createDeveloperInteractive() {
    std::cout << "\n--- Создание разработчика ---\n";

    std::string name;
    do {
        name = readLine("ФИО: ");
        if (name.empty())
            std::cout << "ФИО не может быть пустым.\n";
    } while (name.empty());

    Date birth = readDate("Дата рождения");
    ContactInfo contacts = readContactInfo("Контакты");
    Date hire = readDate("Дата найма");
    double salary = readDouble("Базовый оклад: ", 0.0);
    int grade = readInt(
        "Грейд (0-джуниор, 1-мидл, 2-сеньор, 3-лид): ",
        GRADE_JUNIOR, GRADE_LEAD);

    Developer* dev = EmployeeFactory::createDeveloper(
        name, birth, contacts, hire, salary, grade);
    return dev;
}
inline Manager* createManagerInteractive() {
    std::cout << "\n--- Создание менеджера ---\n";

    std::string name;
    do {
        name = readLine("ФИО: ");
        if (name.empty())
            std::cout << "ФИО не может быть пустым.\n";
    } while (name.empty());

    Date birth = readDate("Дата рождения");
    ContactInfo contacts = readContactInfo("Контакты");
    Date hire = readDate("Дата найма");
    double salary = readDouble("Базовый оклад: ", 0.0);
    double bonus = readDouble("Бонус: ", 0.0);

    Manager* m = EmployeeFactory::createManager(
        name, birth, contacts, hire, salary);
    m->setBonus(bonus);
    return m;
}
inline HRSpecialist* createHRInteractive() {
    std::cout << "\n--- Создание HR-специалиста ---\n";

    std::string name;
    do {
        name = readLine("ФИО: ");
        if (name.empty())
            std::cout << "ФИО не может быть пустым.\n";
    } while (name.empty());

    Date birth = readDate("Дата рождения");
    ContactInfo contacts = readContactInfo("Контакты");
    Date hire = readDate("Дата найма");
    double salary = readDouble("Базовый оклад: ", 0.0);

    return EmployeeFactory::createHR(name, birth, contacts, hire, salary);
}
inline void createEmployeeMenu(Repository<Employee>& employees) {
    bool running = true;
    while (running) {
        printCreateEmployeeMenu();
        int choice = readInt("Выбор: ", 0, 3);

        switch (choice) {
        case 1: {
            try {
                Developer* d = createDeveloperInteractive();
                std::cout << "\nСоздан:\n  " << *d;
                employees.add(d);
                std::cout << "  Сотрудник добавлен в систему.\n";
            }
            catch (const ValidationException& ex) {
                std::cout << "Ошибка: " << ex.what() << "\n";
            }
            running = false;
            break;
        }
        case 2: {
            try {
                Manager* m = createManagerInteractive();
                std::cout << "\nСоздан:\n  " << *m;
                employees.add(m);
                std::cout << "  Сотрудник добавлен в систему.\n";
            }
            catch (const ValidationException& ex) {
                std::cout << "Ошибка: " << ex.what() << "\n";
            }
            running = false;
            break;
        }
        case 3: {
            try {
                HRSpecialist* h = createHRInteractive();
                std::cout << "\nСоздан:\n  " << *h;
                employees.add(h);
                std::cout << "  Сотрудник добавлен в систему.\n";
            }
            catch (const ValidationException& ex) {
                std::cout << "Ошибка: " << ex.what() << "\n";
            }
            running = false;
            break;
        }
        case 0:
            running = false;
            break;
        }
    }
}

inline void printEmployeesMenu() {
    std::cout << "\n--- СОТРУДНИКИ ---\n"
        << "  1. Показать всех\n"
        << "  2. Найти по id\n"
        << "  3. Создать\n"
        << "  0. Назад\n"
        << "------------------\n";
}
inline void employeesMenu(Repository<Employee>& employees,
    Repository<Position>& positions) {
    (void)positions;

    bool running = true;
    while (running) {
        printEmployeesMenu();
        int choice = readInt("Выбор: ", 0, 3);

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
        case 3:
            createEmployeeMenu(employees);
            break;
        case 0:
            running = false;
            break;
        }
    }
}