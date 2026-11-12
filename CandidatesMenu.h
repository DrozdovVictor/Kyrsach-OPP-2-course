#include<iostream>

#include"Classes.h"
#include"Utilities.h"

using namespace kyrsach;

inline void printCandidateOperationsMenu() {
    std::cout << "\n--- ОПЕРАЦИИ С КАНДИДАТОМ ---\n"
        << "  1. Сменить статус\n"
        << "  2. Изменить резюме\n"
        << "  3. Назначить желаемую должность\n"
        << "  4. Показать подробную информацию\n"
        << "  0. Назад\n"
        << "------------------------------\n";
}
inline void candChangeStatus(Candidate* c) {
    int status = readInt(
        "Статус (0-новый, 1-собеседование, 2-оффер, 3-отказ): ",
        CAND_NEW, CAND_REJECTED);
    try {
        c->setStatus(status);
        std::cout << "Статус изменён.\n";
    }
    catch (const ValidationException& ex) {
        std::cout << "Ошибка: " << ex.what() << "\n";
    }
}
inline void candChangeResume(Candidate* c) {
    std::string r = readLine("Новое резюме: ");
    if (r.empty()) {
        std::cout << "Резюме не может быть пустым.\n";
        return;
    }
    c->setResume(r);
    std::cout << "Резюме обновлено.\n";
}
inline void candAssignPosition(Candidate* c, Repository<Position>& positions) {
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

    c->setDesiredPosition(list[idx - 1]);
    std::cout << "Желаемая должность назначена: "
        << list[idx - 1]->getTitle() << "\n";
}
inline void candPrintDetails(Candidate* c) {
    std::cout << "\n--- Карточка кандидата ---\n";
    std::cout << *c;
    std::cout << "  резюме   : " << c->getResume() << "\n";
    std::cout << "  статус   : " << c->getStatus() << "\n";
    Position* p = c->getDesiredPosition();
    std::cout << "  желаемая : " << (p ? p->getTitle() : "—") << "\n";
}
inline void menuCandidateOperations(Repository<Candidate>& candidates,
    Repository<Position>& positions) {
    int id = readInt("Введите id кандидата (0-отмена): ");
    if (id == 0) return;

    Candidate* c = nullptr;
    try {
        c = candidates.findById(id);
    }
    catch (const NotFoundException& ex) {
        std::cout << "Ошибка: " << ex.what() << "\n";
        return;
    }

    std::cout << "\nВыбран кандидат:\n  " << *c;

    bool running = true;
    while (running) {
        printCandidateOperationsMenu();
        int choice = readInt("Выбор: ", 0, 4);

        switch (choice) {
        case 1: candChangeStatus(c); break;
        case 2: candChangeResume(c); break;
        case 3: candAssignPosition(c, positions); break;
        case 4: candPrintDetails(c); break;
        case 0: running = false; break;
        }
    }
}

inline void printCandidatesMenu() {
    std::cout << "\n--- КАНДИДАТЫ ---\n"
        << "  1. Показать всех\n"
        << "  2. Найти по id\n"
        << "  3. Создать\n"
        << "  4. Операции с кандидатом (по id)\n"
        << "  0. Назад\n"
        << "-----------------\n";
}
inline Candidate* createCandidateInteractive() {
    std::cout << "\n--- Создание кандидата ---\n";

    std::string name;
    do {
        name = readLine("ФИО: ");
        if (name.empty())
            std::cout << "ФИО не может быть пустым.\n";
    } while (name.empty());

    Date birth = readDate("Дата рождения");
    ContactInfo contacts = readContactInfo("Контакты");

    std::string resume;
    do {
        resume = readLine("Резюме (кратко): ");
        if (resume.empty())
            std::cout << "Резюме не может быть пустым.\n";
    } while (resume.empty());

    int status = readInt(
        "Статус (0-новый, 1-собеседование, 2-оффер, 3-отказ): ",
        CAND_NEW, CAND_REJECTED);

    Candidate* c = EmployeeFactory::createCandidate(name, birth, contacts);
    c->setResume(resume);
    c->setStatus(status);
    return c;
}
inline void candidatesMenu(Repository<Candidate>& candidates,
    Repository<Position>& positions) {
    bool running = true;
    while (running) {
        printCandidatesMenu();
        int choice = readInt("Выбор: ", 0, 4);

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
        case 3: {
            try {
                Candidate* c = createCandidateInteractive();
                std::cout << "\nСоздан:\n  " << *c;
                candidates.add(c);
                std::cout << "  Кандидат добавлен в систему.\n";
            }
            catch (const ValidationException& ex) {
                std::cout << "Ошибка: " << ex.what() << "\n";
            }
            running = false;
            break;
        }
        case 4:
            menuCandidateOperations(candidates, positions);
            break;
        case 0:
            running = false;
            break;
        }
    }
}

void menuCandidateOperations(Repository<Candidate>& candidates,
    Repository<Position>& positions);