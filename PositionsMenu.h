#pragma once
#include<iostream>

#include"Classes.h"
#include"Utilities.h"

using namespace kyrsach;

inline std::string gradeToStr(int g);

inline void printPositionsMenu() {
    std::cout << "\n--- ДОЛЖНОСТИ ---\n"
        << "  1. Показать все\n"
        << "  2. Создать\n"
        << "  3. Удалить\n"
        << "  0. Назад\n"
        << "-----------------\n";
}
inline Position* createPositionInteractive() {
    std::cout << "\n--- Создание должности ---\n";
    std::string title;
    do {
        title = readLine("Название: ");
        if (title.empty())
            std::cout << "Название не может быть пустым.\n";
    } while (title.empty());

    int grade = readInt(
        "Грейд (0-юниор, 1-мидл, 2-сеньор, 3-лид): ",
        GRADE_JUNIOR, GRADE_LEAD);

    return new Position(title, grade);
}
inline void deletePositionInteractive(Repository<Position>& positions,
    Repository<Employee>& employees,
    Repository<Candidate>& candidates) {
    if (positions.empty()) {
        std::cout << "Нет должностей для удаления.\n";
        return;
    }

    std::vector<Position*> list = positions.getAll();
    Table t({ "#", "Название", "Грейд" });
    for (int i = 0; i < static_cast<int>(list.size()); ++i) {
        t.addRow({ std::to_string(i + 1), list[i]->getTitle(), gradeToStr(list[i]->getGrade()) });
    }
    t.print();

    int idx = readInt("Выберите номер для удаления (0-отмена): ", 0, static_cast<int>(list.size()));
    if (idx == 0) return;

    Position* target = list[idx - 1];

    // 1. Очищаем связи у сотрудников
    for (Employee* e : employees.getAll()) {
        if (e->getPosition() == target) {
            e->setPosition(nullptr);
        }
    }
    // 2. Очищаем связи у кандидатов
    for (Candidate* c : candidates.getAll()) {
        if (c->getDesiredPosition() == target) {
            c->setDesiredPosition(nullptr);
        }
    }

    // 3. Удаляем саму должность из репозитория
    positions.removeAt(idx - 1);
    std::cout << "Должность успешно удалена. Сотрудники и кандидаты, занимавшие её, остались без должности.\n";
}
inline void positionsMenu(Repository<Position>& positions, Repository<Employee>& employees,
    Repository<Candidate>& candidates) {
    bool running = true;
    while (running) {
        printPositionsMenu();
        int choice = readInt("Выбор: ", 0, 3);

        switch (choice) {
        case 1: {
            std::cout << "\n=== Список должностей ===\n";
            if (positions.empty()) {
                std::cout << "  (пусто)\n";
            }
            else {
                printPositionsTable(positions);
            }
            break;
        }
        case 2: {
            try {
                Position* p = createPositionInteractive();
                std::cout << "  Должность добавлена: " << p->getTitle() << "\n";
                positions.add(p);
            }
            catch (const ValidationException& ex) {
                std::cout << "Ошибка: " << ex.what() << "\n";
            }
            break;
        }
        case 3:
            deletePositionInteractive(positions, employees, candidates);
            break;
        case 0:
            running = false;
            break;
        }
    }
}