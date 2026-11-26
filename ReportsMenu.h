#pragma once
#include<iostream>

#include"Classes.h"
#include"Repository.h"
#include"Input.h"

using namespace kyrsach;

// Все, кроме уволенных
inline bool isInStaff(Employee* e) {
    return e->getStatus() != STATUS_FIRED;
}

inline void reportByRoles(Repository<Employee>& employees) {
    int devCount = 0, mgrCount = 0, hrCount = 0;
    for (Employee* e : employees.getAll()) {
        if (!isInStaff(e)) continue;
        if (dynamic_cast<Developer*>(e) != nullptr) ++devCount;
        else if (dynamic_cast<Manager*>(e) != nullptr) ++mgrCount;
        else if (dynamic_cast<HRSpecialist*>(e) != nullptr) ++hrCount;
    }

    Table t({ "Роль", "Количество" });
    t.addRow({ "Разработчики", std::to_string(devCount) });
    t.addRow({ "Менеджеры", std::to_string(mgrCount) });
    t.addRow({ "HR-специалисты", std::to_string(hrCount) });
    t.addRow({ "Всего", std::to_string(devCount + mgrCount + hrCount) });
    t.print();
}

inline void reportCandidatesByStatus(Repository<Candidate>& candidates) {
    int newC = 0, intC = 0, offC = 0, rejC = 0;
    for (Candidate* c : candidates.getAll()) {
        int s = c->getStatus();
        if (s == CAND_NEW)       ++newC;
        else if (s == CAND_INTERVIEW) ++intC;
        else if (s == CAND_OFFERED)   ++offC;
        else if (s == CAND_REJECTED)  ++rejC;
    }

    Table t({ "Статус", "Количество" });
    t.addRow({ "Новый", std::to_string(newC) });
    t.addRow({ "Собеседование", std::to_string(intC) });
    t.addRow({ "Оффер", std::to_string(offC) });
    t.addRow({ "Отказ", std::to_string(rejC) });
    t.addRow({ "Всего", std::to_string(newC + intC + offC + rejC) });
    t.print();
}

inline void printReportsMenu() {
    std::cout << "\n--- ОТЧЁТЫ ---\n"
        << "  1. Распределение по ролям\n"
        << "  2. Кандидаты по статусам\n"
        << "  0. Назад\n"
        << "--------------\n";
}

inline void reportsMenu(Repository<Employee>& employees,
    Repository<Candidate>& candidates) {
    bool running = true;
    while (running) {
        printReportsMenu();
        int choice = readInt("Выбор: ", 0, 2);

        switch (choice) {
        case 1: reportByRoles(employees); break;
        case 2: reportCandidatesByStatus(candidates); break;
        case 0: running = false; break;
        }
    }
}