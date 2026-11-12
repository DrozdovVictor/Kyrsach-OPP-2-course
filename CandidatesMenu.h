#include<iostream>

#include"Classes.h"
#include"Utilities.h"

using namespace kyrsach;

inline void printCandidatesMenu() {
    std::cout << "\n--- КАНДИДАТЫ ---\n"
        << "  1. Показать всех\n"
        << "  2. Найти по id\n"
        << "  3. Создать\n"
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
    (void)positions;

    bool running = true;
    while (running) {
        printCandidatesMenu();
        int choice = readInt("Выбор: ", 0, 3);

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
        case 0:
            running = false;
            break;
        }
    }
}