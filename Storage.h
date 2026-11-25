#pragma once
#include<iostream>
#include"string.h"

#include"Utilities.h"

namespace kyrsach {
    class Storage {
    public:
        // Сохранение
        static void savePositions(const std::string& filename, const Repository<Position>& positions);
        static void saveEmployees(const std::string& filename, const Repository<Employee>& employees, const Repository<Position>& positions);
        static void saveCandidates(const std::string& filename, const Repository<Candidate>& candidates, const Repository<Position>& positions);

        // Загрузка
        static void loadPositions(const std::string& filename, Repository<Position>& positions);
        static void loadEmployees(const std::string& filename, Repository<Employee>& employees, const Repository<Position>& positions);
        static void loadCandidates(const std::string& filename, Repository<Candidate>& candidates, const Repository<Position>& positions);
    };
}