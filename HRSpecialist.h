#pragma once
#include<iostream>
#include<string>

#include"Emploee.h"

namespace kyrsach {

    class HRSpecialist : public Employee {
        int hiredThisYear = 0;

    public:
        HRSpecialist(int id, const std::string& fullName,
            const Date& birthDay, const ContactInfo& contacts,
            int personnelNumber, const Date& hireDate)
            : Employee(id, fullName, birthDay, contacts,
                personnelNumber, hireDate),
            hiredThisYear(0) {
        }

        void incrementHired() {
            ++hiredThisYear;
        }

        std::string getDuties() const override {
            return "Найм, адаптация и учёт персонала";
        }
        std::string getRole() const override {
            return "HR-специалист";
        }
        int getHiredThisYear() const { 
            return hiredThisYear; 
        }

        void print(std::ostream& os) const override {
            os << "[HR-специалист] " << getFullName()
                << " | нанято: " << hiredThisYear << "\n";
        }
    };
}