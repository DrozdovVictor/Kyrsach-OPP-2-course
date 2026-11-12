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

inline void printEmployeeDetails(Employee* e) {
    std::cout << "\n--- Карточка сотрудника ---\n";
    std::cout << *e;   // краткая строка через operator<<
    std::cout << "  оклад      : " << e->getBaseSalary() << "\n"
        << "  зарплата   : " << e->calculateSalary() << "\n"
        << "  статус     : " << e->getStatus() << "\n"
        << "  навыков    : " << e->getSkillsCount() << "\n"
        << "  обязанности: " << e->getDuties() << "\n";
}
inline void printOperationsMenu() {
    std::cout << "\n--- ОПЕРАЦИИ С СОТРУДНИКОМ ---\n"
        << "  1. Сменить статус\n"
        << "  2. Назначить должность\n"
        << "  3. Создать учётку\n"
        << "  4. Добавить навык\n"
        << "  5. Показать подробную информацию\n"
        << "  6. Добавить технологию [Developer]\n"
        << "  7. Задать бонус [Manager]\n"
        << "  8. Добавить подчинённого [Manager]\n"
        << "  9. Отметить найм [HRSpecialist]\n"
        << "  0. Назад\n"
        << "------------------------------\n";
}
inline void changeStatus(Employee* e) {
    int how = readInt("Ввод: 1-числом (0-2), 2-словом, 0-отмена: ", 0, 2);
    if (how == 0) return;

    try {
        if (how == 1) {
            int s = readInt("Статус (0-активный, 1-отпуск, 2-уволен): ",
                STATUS_ACTIVE, STATUS_FIRED);
            e->setStatus(s);                         // перегрузка int
        }
        else {
            std::string s = readLine("Статус (активный/отпуск/уволен): ");
            e->setStatus(s);                         // перегрузка string
        }
        std::cout << "Статус изменён.\n";
    }
    catch (const ValidationException& ex) {
        std::cout << "Ошибка: " << ex.what() << "\n";
    }
}
inline void assignPosition(Employee* e, Repository<Position>& positions) {
    if (positions.empty()) {
        std::cout << "Нет должностей. Сначала создайте их в разделе «Должности».\n";
        return;
    }

    std::vector<Position*> list = positions.getAll();
    std::cout << "\nДоступные должности:\n";
    for (int i = 0; i < static_cast<int>(list.size()); ++i) {
        std::cout << "  " << (i + 1) << ". " << list[i]->getTitle()
            << " | грейд: " << list[i]->getGrade()
            << " | оклад: " << list[i]->getBaseSalary() << "\n";
    }
    int idx = readInt("Выберите номер (0-отмена): ", 0, static_cast<int>(list.size()));
    if (idx == 0) return;

    e->setPosition(list[idx - 1]);
    std::cout << "Должность назначена.\n";
}
inline void createAccount(Employee* e) {
    std::string login = readLine("Логин: ");
    if (login.empty()) {
        std::cout << "Логин не может быть пустым.\n";
        return;
    }
    std::string hash = readLine("Хэш пароля: ");
    int role = readInt("Роль (0-админ, 1-HR, 2-менеджер, 3-сотрудник): ",
        ROLE_ADMIN, ROLE_EMPLOYEE);

    e->setAccount(std::make_unique<UserAccount>(login, hash, role));
    std::cout << "Учётка создана (логин: " << login << ").\n";
}
inline void addSkill(Employee* e) {
    std::string name = readLine("Название навыка: ");
    if (name.empty()) {
        std::cout << "Название не может быть пустым.\n";
        return;
    }
    int level = readInt("Уровень (1-5): ", 1, 5);
    try {
        e->addSkill(Skill{ name, level });
        std::cout << "Навык добавлен (всего навыков: "
            << e->getSkillsCount() << ").\n";
    }
    catch (const ValidationException& ex) {
        std::cout << "Ошибка: " << ex.what() << "\n";
    }
}

// Developer: добавить технологию
inline void addTechnology(Employee* e) {
    Developer* dev = dynamic_cast<Developer*>(e);
    if (dev == nullptr) {
        std::cout << "Операция только для разработчика.\n";
        return;
    }
    std::string tech = readLine("Название технологии: ");
    if (tech.empty()) {
        std::cout << "Название не может быть пустым.\n";
        return;
    }
    dev->addTechnology(tech);
    std::cout << "Технология добавлена (всего: "
        << dev->getTechCount() << ").\n";
}
// Manager: задать бонус
inline void setBonus(Employee* e) {
    Manager* mgr = dynamic_cast<Manager*>(e);
    if (mgr == nullptr) {
        std::cout << "Операция только для менеджера.\n";
        return;
    }
    double bonus = readDouble("Бонус: ", 0.0);
    try {
        mgr->setBonus(bonus);
        std::cout << "Бонус установлен.\n";
    }
    catch (const ValidationException& ex) {
        std::cout << "Ошибка: " << ex.what() << "\n";
    }
}
// Manager: добавить подчинённого
// Здесь ДВЕ проверки:
//   1) canManage() — полиморфный запрос «умеет ли управлять»
//   2) dynamic_cast — доступ к методу addSubordinate
inline void addSubordinate(Employee* e, Repository<Employee>& employees) {
    // 1) Полиморфная проверка права
    if (!e->canManage()) {
        std::cout << "Этот сотрудник не может управлять подчинёнными.\n";
        return;
    }

    // 2) Приведение к Manager — теперь точно безопасно,
    //    потому что canManage() == true только у Manager
    Manager* mgr = dynamic_cast<Manager*>(e);
    if (mgr == nullptr) {
        // сюда попасть невозможно, пока canManage override только в Manager
        std::cout << "Внутренняя ошибка: canManage()==true, но тип не Manager.\n";
        return;
    }

    int id = readInt("id подчинённого (0-отмена): ");
    if (id == 0) return;

    Employee* sub = nullptr;
    try {
        sub = employees.findById(id);
    }
    catch (const NotFoundException& ex) {
        std::cout << "Ошибка: " << ex.what() << "\n";
        return;
    }
    if (sub == e) {
        std::cout << "Нельзя быть подчинённым у себя.\n";
        return;
    }

    mgr->addSubordinate(sub);
    std::cout << "Подчинённый добавлен (всего: "
        << mgr->getSubordinatesCount() << ").\n";
}
// HRSpecialist: отметить найм
inline void incrementHired(Employee* e) {
    HRSpecialist* hr = dynamic_cast<HRSpecialist*>(e);
    if (hr == nullptr) {
        std::cout << "Операция только для HR-специалиста.\n";
        return;
    }
    hr->incrementHired();
    std::cout << "Найм отмечен (всего за год: "
        << hr->getHiredThisYear() << ").\n";
}

inline void employeeOperationsMenu(Repository<Employee>& employees,
    Repository<Position>& positions) {
    int id = readInt("Введите id сотрудника (0-отмена): ");
    if (id == 0) return;

    Employee* e = nullptr;
    try {
        e = employees.findById(id);
    }
    catch (const NotFoundException& ex) {
        std::cout << "Ошибка: " << ex.what() << "\n";
        return;
    }

    std::cout << "\nВыбран сотрудник:\n  " << *e;

    bool running = true;
    while (running) {
        printOperationsMenu();
        int choice = readInt("Выбор: ", 0, 9);

        switch (choice) {
        case 1: changeStatus(e); break;
        case 2: assignPosition(e, positions); break;
        case 3: createAccount(e); break;
        case 4: addSkill(e); break;
        case 5: printEmployeeDetails(e); break;
        case 6: addTechnology(e); break;
        case 7: setBonus(e); break;
        case 8: addSubordinate(e, employees); break;
        case 9: incrementHired(e); break;
        case 0: running = false; break;
        }
    }
}

inline void printEmployeesMenu() {
    std::cout << "\n--- СОТРУДНИКИ ---\n"
        << "  1. Показать всех\n"
        << "  2. Найти по id\n"
        << "  3. Создать\n"
        << "  4. Операции с сотрудником (по id)\n"
        << "  0. Назад\n"
        << "------------------\n";
}
inline void employeesMenu(Repository<Employee>& employees,
    Repository<Position>& positions) {
    bool running = true;
    while (running) {
        printEmployeesMenu();
        int choice = readInt("Выбор: ", 0, 4);

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
        case 4:
            employeeOperationsMenu(employees, positions);
            break;
        case 0:
            running = false;
            break;
        }
    }
}

void employeeOperationsMenu(Repository<Employee>& employees,
    Repository<Position>& positions);