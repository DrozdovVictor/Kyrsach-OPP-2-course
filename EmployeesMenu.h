#include<iostream>

#include"Classes.h"
#include"Utilities.h"

using namespace kyrsach;

inline std::string gradeToStr(int g) {
    if (g == GRADE_JUNIOR) return "Junior";
    if (g == GRADE_MIDDLE) return "Middle";
    if (g == GRADE_SENIOR) return "Senior";
    if (g == GRADE_LEAD)   return "Lead";
    return "Неизвестно";
}

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
    int grade = readInt(
        "Грейд (0-джуниор, 1-мидл, 2-сеньор, 3-лид): ",
        GRADE_JUNIOR, GRADE_LEAD);

    Developer* dev = EmployeeFactory::createDeveloper(
        name, birth, contacts, hire, grade);
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

    Manager* m = EmployeeFactory::createManager(
        name, birth, contacts, hire);
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

    return EmployeeFactory::createHR(name, birth, contacts, hire);
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
    Table t({ "Параметр", "Значение" });
    t.addRow({ "ID", std::to_string(e->getId()) });
    t.addRow({ "ФИО", e->getFullName() });
    t.addRow({ "Роль", e->getRole() });

    std::string statusStr = (e->getStatus() == STATUS_ACTIVE) ? "Работает" :
        (e->getStatus() == STATUS_VACATION) ? "Отпуск" : "Уволен";
    t.addRow({ "Статус", statusStr });

    Position* p = e->getPosition();
    t.addRow({ "Должность", p ? p->getTitle() : "пусто" });

    t.addRow({ "Обязанности", e->getDuties() });

    // Специфичные поля через dynamic_cast
    if (auto dev = dynamic_cast<Developer*>(e)) {
        t.addRow({ "Грейд", gradeToStr(dev->getGrade()) });
        t.addRow({ "Навыков", std::to_string(dev->getSkillsCount()) }); // <--- Перенесли сюда
    }
    else if (auto mgr = dynamic_cast<Manager*>(e)) {
        t.addRow({ "Подчинённых", std::to_string(mgr->getSubordinatesCount()) });
    }
    // Блок else if (auto hr = dynamic_cast<HRSpecialist*>(e)) удалён, 
    // так как у HR больше нет специфичных полей для вывода

    std::cout << "\n--- Карточка сотрудника ---\n";
    t.print();
}
inline void changeStatus(Employee* e) {
    int s = readInt("Ввод: 0-работает, 1-отпуск, 2-уволен, -1-отмена: ", -1, 2);
    if (s == -1) return;

    try {
        e->setStatus(s); // Вызывается перегрузка int
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

    Table t({ "#", "Название", "Грейд" });
    for (int i = 0; i < static_cast<int>(list.size()); ++i) {
        t.addRow({ std::to_string(i + 1), list[i]->getTitle(), gradeToStr(list[i]->getGrade()) });
    }
    t.print();

    int idx = readInt("Выберите номер (0-отмена): ", 0, static_cast<int>(list.size()));
    if (idx == 0) return;

    e->setPosition(list[idx - 1]);
    std::cout << "Должность назначена.\n";
}

// Developer: навыки
inline void showSkills(Employee* e) {
    Developer* d = dynamic_cast<Developer*>(e);
    if (d == nullptr) {
        std::cout << "Навыки могут быть только у разработчика.\n";
        return;
    }

    const auto& skills = d->getSkills();
    if (skills.empty()) {
        std::cout << "  У сотрудника пока нет навыков.\n";
        return;
    }
    Table t({ "Навык", "Уровень" });
    for (const auto& s : skills) {
        t.addRow({ s.name, std::to_string(s.level) });
    }
    t.print();
}
inline void addSkill(Employee* e) {
    Developer* d = dynamic_cast<Developer*>(e);
    if (d == nullptr) {
        std::cout << "Навыки могут быть только у разработчика.\n";
        return;
    }

    std::string name = readLine("Название навыка: ");
    if (name.empty()) {
        std::cout << "Название не может быть пустым.\n";
        return;
    }
    int level = readInt("Уровень (1-5): ", 1, 5);
    try {
        d->addSkill(Skill{ name, level });
        std::cout << "Навык добавлен (всего навыков: "
            << d->getSkillsCount() << ").\n";
    }
    catch (const ValidationException& ex) {
        std::cout << "Ошибка: " << ex.what() << "\n";
    }
}
inline void editSkill(Employee* e) {
    Developer* d = dynamic_cast<Developer*>(e);
    if (!d) return;
    auto& skills = const_cast<std::vector<Skill>&>(d->getSkills());
    if (skills.empty()) {
        std::cout << "Нет навыков для редактирования.\n";
        return;
    }
    for (int i = 0; i < (int)skills.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << skills[i].name << " (" << skills[i].level << ")\n";
    }
    int idx = readInt("Выберите номер навыка (0-отмена): ", 0, skills.size());
    if (idx == 0) return;

    skills[idx - 1].level = readInt("Новый уровень (1-5): ", 1, 5);
    std::cout << "Уровень навыка обновлён.\n";
}
inline void deleteSkill(Employee* e) {
    Developer* d = dynamic_cast<Developer*>(e);
    if (!d) return;
    auto& skills = const_cast<std::vector<Skill>&>(d->getSkills());
    if (skills.empty()) return;
    for (int i = 0; i < (int)skills.size(); ++i) {
        std::cout << "  " << (i + 1) << ". " << skills[i].name << "\n";
    }
    int idx = readInt("Выберите номер навыка для удаления (0-отмена): ", 0, skills.size());
    if (idx == 0) return;

    skills.erase(skills.begin() + (idx - 1));
    std::cout << "Навык удалён.\n";
}

// Manager: добавить подчинённого
// Здесь ДВЕ проверки:
//   1) canManage() — полиморфный запрос «умеет ли управлять»
//   2) dynamic_cast — доступ к методу addSubordinate
inline void showSubordinates(Employee* e) {
    Manager* m = dynamic_cast<Manager*>(e);
    if (!m) return;
    const auto& subs = m->getSubordinates();
    if (subs.empty()) {
        std::cout << "Нет подчинённых.\n";
        return;
    }
    Table t({ "ID", "ФИО", "Роль", "Должность", "Статус" });
    for (Employee* sub : subs) {
        std::string st = (sub->getStatus() == STATUS_ACTIVE) ? "Работает" :
            (sub->getStatus() == STATUS_VACATION) ? "Отпуск" : "Уволен";
        Position* p = sub->getPosition();
        t.addRow({ std::to_string(sub->getId()), sub->getFullName(), sub->getRole(), p ? p->getTitle() : "—", st });
    }
    t.print();
}
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
inline void removeSubordinate(Employee* e) {
    Manager* m = dynamic_cast<Manager*>(e);
    if (!m) return;
    if (m->getSubordinates().empty()) return;

    int id = readInt("Введите id подчинённого для удаления (0-отмена): ");
    if (id == 0) return;
    m->removeSubordinate(id);
    std::cout << "Подчинённый удалён (если он был в списке).\n";
}

// HR: превратить кандидата в сотрудника
inline void hireCandidate(Repository<Employee>& employees, Repository<Candidate>& candidates, Repository<Position>& positions) {
    if (candidates.empty()) {
        std::cout << "В базе нет кандидатов.\n";
        return;
    }

    Table t({ "ID", "ФИО", "Желаемая должность", "Статус" });
    for (Candidate* c : candidates.getAll()) {
        std::string st = (c->getStatus() == CAND_NEW) ? "Новый" :
            (c->getStatus() == CAND_INTERVIEW) ? "Собеседование" :
            (c->getStatus() == CAND_OFFERED) ? "Оффер" : "Отказ";
        Position* p = c->getDesiredPosition();
        t.addRow({ std::to_string(c->getId()), c->getFullName(), p ? p->getTitle() : "—", st });
    }
    t.print();

    int id = readInt("Введите id кандидата для найма (0-отмена): ");
    if (id == 0) return;

    Candidate* c = nullptr;
    try { c = candidates.findById(id); }
    catch (const NotFoundException& ex) { std::cout << ex.what() << "\n"; return; }

    if (c->getStatus() == CAND_OFFERED) {
        std::cout << "Этот кандидат уже принят на работу (статус 'Оффер').\n";
        return;
    }

    std::cout << "Кем будет работать " << c->getFullName() << "?\n"
        << "  1. Разработчик\n  2. Менеджер\n  3. HR-специалист\n";
    int role = readInt("Выбор: ", 1, 3);

    Date today = { 1, 1, 2024 }; // Для простоты берем фиксированную дату или можно спросить
    Employee* newEmp = nullptr;

    if (role == 1) {
        int grade = readInt("Грейд (0-юниор, 1-мидл, 2-сеньор, 3-лид): ", GRADE_JUNIOR, GRADE_LEAD);
        newEmp = EmployeeFactory::createDeveloper(c->getFullName(), c->getBirthDay(), c->getContacts(), today, grade);
    }
    else if (role == 2) {
        newEmp = EmployeeFactory::createManager(c->getFullName(), c->getBirthDay(), c->getContacts(), today);
    }
    else {
        newEmp = EmployeeFactory::createHR(c->getFullName(), c->getBirthDay(), c->getContacts(), today);
    }

    // Если у кандидата была желаемая должность, назначаем её сотруднику
    if (c->getDesiredPosition()) newEmp->setPosition(c->getDesiredPosition());

    employees.add(newEmp);
    c->setStatus(CAND_OFFERED); // Меняем статус кандидата
    std::cout << "Кандидат успешно принят на работу! Создан сотрудник #" << newEmp->getId() << "\n";
}

inline void employeeOperationsMenu(Repository<Employee>& employees,
    Repository<Position>& positions, Repository<Candidate>& candidates) {
    int id = readInt("Введите id сотрудника (0-отмена): ");
    if (id == 0) return;

    Employee* e = nullptr;
    try { e = employees.findById(id); }
    catch (const NotFoundException& ex) { std::cout << "Ошибка: " << ex.what() << "\n"; return; }

    std::cout << "\nВыбран сотрудник:\n  " << *e;

    Developer* dev = dynamic_cast<Developer*>(e);
    Manager* mgr = dynamic_cast<Manager*>(e);
    HRSpecialist* hr = dynamic_cast<HRSpecialist*>(e);

    bool running = true;
    while (running) {
        std::cout << "\n--- ОПЕРАЦИИ С СОТРУДНИКОМ ---\n";
        std::cout << "  1. Сменить статус\n";
        std::cout << "  2. Назначить должность\n";
        std::cout << "  3. Показать подробную информацию\n";

        int next = 4;
        int optAddSkill = -1, optEditSkill = -1, optDelSkill = -1, optShowSkill = -1;
        int optAddSub = -1, optShowSub = -1, optDelSub = -1;
        int optHire = -1;

        if (dev) {
            std::cout << "  " << next << ". Добавить навык\n"; optAddSkill = next++;
            std::cout << "  " << next << ". Редактировать навык\n"; optEditSkill = next++;
            std::cout << "  " << next << ". Удалить навык\n"; optDelSkill = next++;
            std::cout << "  " << next << ". Показать навыки\n"; optShowSkill = next++;
        }
        if (mgr) {
            std::cout << "  " << next << ". Добавить подчинённого\n"; optAddSub = next++;
            std::cout << "  " << next << ". Показать подчинённых\n"; optShowSub = next++;
            std::cout << "  " << next << ". Удалить подчинённого\n"; optDelSub = next++;
        }
        if (hr) {
            std::cout << "  " << next << ". Нанять кандидата\n"; optHire = next++;
        }

        std::cout << "  0. Назад\n------------------------------\n";
        int choice = readInt("Выбор: ", 0, next - 1);

        if (choice == 1) changeStatus(e);
        else if (choice == 2) assignPosition(e, positions);
        else if (choice == 3) printEmployeeDetails(e);
        else if (choice == optAddSkill) addSkill(e);
        else if (choice == optEditSkill) editSkill(e);
        else if (choice == optDelSkill) deleteSkill(e);
        else if (choice == optShowSkill) showSkills(e);
        else if (choice == optAddSub) addSubordinate(e, employees);
        else if (choice == optShowSub) showSubordinates(e);
        else if (choice == optDelSub) removeSubordinate(e);
        else if (choice == optHire) hireCandidate(employees, candidates, positions);
        else if (choice == 0) running = false;
    }
}

inline void printEmployeesMenu() {
    std::cout << "\n--- СОТРУДНИКИ ---\n"
        << "  1. Показать всех\n"
        << "  2. Найти по id\n"
        << "  3. Создать\n"
        << "  4. Операции с сотрудником\n"
        << "  0. Назад\n"
        << "------------------\n";
}
inline void employeesMenu(Repository<Employee>& employees,
    Repository<Position>& positions, Repository<Candidate>& candidates) {
    bool running = true;
    while (running) {
        printEmployeesMenu();
        int choice = readInt("Выбор: ", 0, 4);

        switch (choice) {
        case 1: {
            std::cout << "\n=== Список сотрудников ===\n";
            printEmployeesTable(employees);
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
            employeeOperationsMenu(employees, positions, candidates);
            break;
        case 0:
            running = false;
            break;
        }
    }
}