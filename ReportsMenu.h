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
    std::cout << "\n--- Распределение по ролям ---\n"
        << "  Разработчики    : " << devCount << "\n"
        << "  Менеджеры       : " << mgrCount << "\n"
        << "  HR-специалисты  : " << hrCount << "\n"
        << "  Всего           : " << (devCount + mgrCount + hrCount) << "\n";
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
    std::cout << "\n--- Кандидаты по статусам ---\n"
        << "  Новый          : " << newC << "\n"
        << "  Собеседование  : " << intC << "\n"
        << "  Оффер          : " << offC << "\n"
        << "  Отказ          : " << rejC << "\n"
        << "  Всего          : " << (newC + intC + offC + rejC) << "\n";
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