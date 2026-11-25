#pragma once
#include<iostream>
#include<string>
#include<vector>

#include"Emploee.h"

namespace kyrsach {

    class Manager : public Employee {
        std::vector<Employee*> subordinates; // агрегация, не владеет (подчинённые)

    public:
        Manager(int id, const std::string& fullName,
            const Date& birthDay, const ContactInfo& contacts,
            int personnelNumber, const Date& hireDate)
            : Employee(id, fullName, birthDay, contacts,
                personnelNumber, hireDate) {}

        void addSubordinate(Employee* e) {
            subordinates.push_back(e);
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