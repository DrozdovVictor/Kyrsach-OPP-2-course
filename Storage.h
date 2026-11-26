#pragma once
#include<iostream>
#include<fstream>
#include"string.h"

#include"Utilities.h"

namespace kyrsach {
    class Storage {
    // Вспомогательная функция: разбивает строку по символу
    static std::vector<std::string> split(const std::string& s, char delim) {
        std::vector<std::string> elems;
        std::string item;
        for (char c : s) {
            if (c == delim) {
                elems.push_back(item);
                item.clear();
            } else {
                item += c;
            }
        }
        elems.push_back(item);
        return elems;
    }

    public:
        // Сохранение
        static void savePositions(const std::string& filename, const Repository<Position>& positions) {
            std::ofstream out(filename);
            if (!out) throw std::runtime_error("Не удалось открыть файл на запись: " + filename);
            out << "# title|grade\n";
            for (Position* p : positions.getAll()) {
                out << p->getTitle() << "|" << p->getGrade() << "\n";
            }
        }

        static void saveEmployees(const std::string& filename,
            const Repository<Employee>& employees,
            const Repository<Position>& positions) {
            std::ofstream out(filename);
            if (!out) throw std::runtime_error("Не удалось открыть файл на запись: " + filename);

            out << "# type|id|fullName|bd_day|bd_mon|bd_year|phone|email|personnel_num|hire_day|hire_mon|hire_year|status|pos_idx|extra\n";
            for (Employee* e : employees.getAll()) {
                std::string type, extra;

                if (auto d = dynamic_cast<Developer*>(e)) {
                    type = "D";
                    extra = std::to_string(d->getGrade()) + ",";
                    const auto& skills = d->getSkills();
                    for (size_t i = 0; i < skills.size(); ++i) {
                        extra += skills[i].name + ":" + std::to_string(skills[i].level);
                        if (i + 1 < skills.size()) extra += ";";
                    }
                }
                else if (auto m = dynamic_cast<Manager*>(e)) {
                    type = "M";
                    const auto& subs = m->getSubordinates();
                    for (size_t i = 0; i < subs.size(); ++i) {
                        extra += std::to_string(subs[i]->getId()) + (i + 1 < subs.size() ? "," : "");
                    }
                }
                else if (auto h = dynamic_cast<HRSpecialist*>(e)) {
                    type = "H";
                    extra = "";
                }

                int posIdx = -1;
                if (e->getPosition()) {
                    const auto& allPos = positions.getAll();
                    for (size_t i = 0; i < allPos.size(); ++i) {
                        if (allPos[i] == e->getPosition()) { posIdx = static_cast<int>(i); break; }
                    }
                }

                Date bd = e->getBirthDay();
                Date hd = e->getHireDate();
                ContactInfo ci = e->getContacts();

                out << type << "|" << e->getId() << "|" << e->getFullName() << "|"
                    << bd.day << "|" << bd.month << "|" << bd.year << "|"
                    << ci.phone << "|" << ci.email << "|"
                    << e->getPersonnelNumber() << "|"
                    << hd.day << "|" << hd.month << "|" << hd.year << "|"
                    << e->getStatus() << "|" << posIdx << "|" << extra << "\n";
            }
        }

        static void saveCandidates(const std::string& filename,
            const Repository<Candidate>& candidates,
            const Repository<Position>& positions) {
            std::ofstream out(filename);
            if (!out) throw std::runtime_error("Не удалось открыть файл на запись: " + filename);

            out << "# id|fullName|bd_day|bd_mon|bd_year|phone|email|resume|status|desired_pos_idx\n";
            for (Candidate* c : candidates.getAll()) {
                int posIdx = -1;
                if (c->getDesiredPosition()) {
                    const auto& allPos = positions.getAll();
                    for (size_t i = 0; i < allPos.size(); ++i) {
                        if (allPos[i] == c->getDesiredPosition()) { posIdx = static_cast<int>(i); break; }
                    }
                }

                Date bd = c->getBirthDay();
                ContactInfo ci = c->getContacts();

                out << c->getId() << "|" << c->getFullName() << "|"
                    << bd.day << "|" << bd.month << "|" << bd.year << "|"
                    << ci.phone << "|" << ci.email << "|"
                    << c->getResume() << "|" << c->getStatus() << "|" << posIdx << "\n";
            }
        }

        // Загрузка
        static void loadPositions(const std::string& filename, Repository<Position>& positions) {
            std::ifstream in(filename);
            if (!in) return; // Файла нет — это нормально для первого запуска

            std::string line;
            while (std::getline(in, line)) {
                if (line.empty() || line[0] == '#') continue;
                auto parts = split(line, '|');
                if (parts.size() < 2) continue;
                positions.add(new Position(parts[0], std::stoi(parts[1])));
            }
        }
        static void loadEmployees(const std::string& filename,
            Repository<Employee>& employees,
            const Repository<Position>& positions) {
            std::ifstream in(filename);
            if (!in) return;

            std::string line;
            std::vector<std::pair<int, std::string>> tempSubs; // Для второго прохода (ID менеджера, строка с ID подчиненных)
            int maxId = 0;
            int maxPersonnel = 100;

            // ПЕРВЫЙ ПРОХОД: создаем всех сотрудников
            while (std::getline(in, line)) {
                if (line.empty() || line[0] == '#') continue;
                auto parts = split(line, '|');
                if (parts.size() < 14) continue;

                std::string type = parts[0];
                int id = std::stoi(parts[1]);
                std::string name = parts[2];
                Date bd{ std::stoi(parts[3]), std::stoi(parts[4]), std::stoi(parts[5]) };
                ContactInfo ci{ parts[6], parts[7] };
                int pn = std::stoi(parts[8]);
                Date hd{ std::stoi(parts[9]), std::stoi(parts[10]), std::stoi(parts[11]) };
                int status = std::stoi(parts[12]);
                int posIdx = std::stoi(parts[13]);
                std::string extra = (parts.size() > 14) ? parts[14] : "";

                if (id > maxId) maxId = id;
                if (pn > maxPersonnel) maxPersonnel = pn;

                Employee* emp = nullptr;

                if (type == "D") {
                    auto ext = split(extra, ',');
                    int grade = (!ext.empty() && !ext[0].empty()) ? std::stoi(ext[0]) : 0;
                    auto dev = new Developer(id, name, bd, ci, pn, hd, grade);

                    if (ext.size() > 1 && !ext[1].empty()) {
                        auto skillsStr = split(ext[1], ';');
                        for (const auto& sStr : skillsStr) {
                            auto sParts = split(sStr, ':');
                            if (sParts.size() == 2) {
                                dev->addSkill(Skill{ sParts[0], std::stoi(sParts[1]) });
                            }
                        }
                    }
                    emp = dev;
                }
                else if (type == "M") {
                    auto mgr = new Manager(id, name, bd, ci, pn, hd);
                    if (!extra.empty()) tempSubs.push_back({ id, extra });
                    emp = mgr;
                }
                else if (type == "H") {
                    emp = new HRSpecialist(id, name, bd, ci, pn, hd);
                }

                if (emp) {
                    emp->setStatus(status);
                    if (posIdx >= 0 && posIdx < positions.size()) {
                        emp->setPosition(positions.getAll()[posIdx]);
                    }
                    employees.add(emp);
                }
            }

            // ВТОРОЙ ПРОХОД: связываем менеджеров с подчиненными
            for (const auto& pair : tempSubs) {
                try {
                    Employee* mEmp = employees.findById(pair.first);
                    Manager* mgr = dynamic_cast<Manager*>(mEmp);
                    if (!mgr) continue;

                    auto subIds = split(pair.second, ',');
                    for (const auto& sidStr : subIds) {
                        if (sidStr.empty()) continue;
                        try {
                            Employee* sub = employees.findById(std::stoi(sidStr));
                            mgr->addSubordinate(sub);
                        }
                        catch (...) { /* Игнорируем битые ссылки */ }
                    }
                }
                catch (...) { /* Игнорируем битые ссылки */ }
            }

            Employee::nextId = maxId + 1;
            EmployeeFactory::nextPersonnelNumber = maxPersonnel + 1;
        }
        static void loadCandidates(const std::string& filename,
            Repository<Candidate>& candidates,
            const Repository<Position>& positions) {
            std::ifstream in(filename);
            if (!in) return;

            std::string line;
            int maxId = Candidate::nextId - 1; // Учитываем тех, кто уже загрузился (сотрудники)

            while (std::getline(in, line)) {
                if (line.empty() || line[0] == '#') continue;
                auto parts = split(line, '|');
                if (parts.size() < 10) continue;

                int id = std::stoi(parts[0]);
                std::string name = parts[1];
                Date bd{ std::stoi(parts[2]), std::stoi(parts[3]), std::stoi(parts[4]) };
                ContactInfo ci{ parts[5], parts[6] };
                std::string resume = parts[7];
                int status = std::stoi(parts[8]);
                int desiredIdx = std::stoi(parts[9]);

                if (id > maxId) maxId = id;

                auto cand = new Candidate(id, name, bd, ci);
                cand->setResume(resume);
                cand->setStatus(status);

                if (desiredIdx >= 0 && desiredIdx < positions.size()) {
                    cand->setDesiredPosition(positions.getAll()[desiredIdx]);
                }
                candidates.add(cand);
            }

            Candidate::nextId = maxId + 1;
        }

        // Обёртки (Вызов всех файлов сразу)
        static void saveAll(const std::string& prefix,
            const Repository<Position>& positions,
            const Repository<Employee>& employees,
            const Repository<Candidate>& candidates) {
            savePositions(prefix + "positions.txt", positions);
            saveEmployees(prefix + "employees.txt", employees, positions);
            saveCandidates(prefix + "candidates.txt", candidates, positions);
        }

        static void loadAll(const std::string& prefix,
            Repository<Position>& positions,
            Repository<Employee>& employees,
            Repository<Candidate>& candidates) {
            // Очищаем всё перед загрузкой. Порядок важен (как при удалении).
            candidates.clear();
            employees.clear();
            positions.clear();

            loadPositions(prefix + "positions.txt", positions);
            loadEmployees(prefix + "employees.txt", employees, positions);
            loadCandidates(prefix + "candidates.txt", candidates, positions);
        }
    };
}