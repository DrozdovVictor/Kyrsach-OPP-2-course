#pragma once
#include<iostream>
#include<string>

#include"Emploee.h"

namespace kyrsach {

    class HRSpecialist : public Employee {
    public:
        HRSpecialist(int id, const std::string& fullName,
            const Date& birthDay, const ContactInfo& contacts,
            int personnelNumber, const Date& hireDate)
            : Employee(id, fullName, birthDay, contacts,
                personnelNumber, hireDate) {}

        std::string getDuties() const override {
            return "Найм сотрудников";
        }
        std::string getRole() const override {
            return "HR-специалист";
        }

        void print(std::ostream& os) const override {
            os << "[HR-специалист] " << getFullName();
        }
    };
}