#pragma once
#include<iostream>
#include<string>
#include<vector>

#include"Emploee.h"

namespace kyrsach {

    class Manager : public Employee {
        std::vector<Employee*> subordinates; // агрегация, не владеет (подчинённые)
        double bonus = 0.0; // премия

    public:
        Manager(int id, const std::string& fullName,
            const Date& birthDay, const ContactInfo& contacts,
            int personnelNumber, const Date& hireDate, double baseSalary)
            : Employee(id, fullName, birthDay, contacts,
                personnelNumber, hireDate, baseSalary),
            bonus(0.0) {
        }

        void addSubordinate(Employee* e) {
            subordinates.push_back(e);
        }
        void setBonus(double b) {
            if (b < 0) throw ValidationException("Бонус не может быть отрицательным");
            bonus = b;
        }

        double calculateSalary() const override {
            return getBaseSalary() + bonus
                + 100.0 * static_cast<int>(subordinates.size());
        }

        std::string getDuties() const override {
            return "Управление командой и планирование";
        }

        bool canManage() const override {
            return true;
        }

        std::string getRole() const override {
            return "Менеджер";
        }

        void print(std::ostream& os) const override {
            os << "[Менеджер] " << getFullName()
                << " | подчинённых: " << subordinates.size() << "\n";
        }

        int getSubordinatesCount() const {
            return static_cast<int>(subordinates.size());
        }
    };
}