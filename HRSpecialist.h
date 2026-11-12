#pragma once
#include<iostream>
#include<string>

#include"Emploee.h"

namespace system {

    class HRSpecialist : public Employee {
        int hiredThisYear = 0;

    public:
        HRSpecialist(int id, const std::string& fullName,
            const Date& birthDay, const ContactInfo& contacts,
            int personnelNumber, const Date& hireDate, double baseSalary)
            : Employee(id, fullName, birthDay, contacts,
                personnelNumber, hireDate, baseSalary),
            hiredThisYear(0) {
        }

        void incrementHired() {
            ++hiredThisYear;
        }

        double calculateSalary() const override {
            return getBaseSalary() + 50.0 * hiredThisYear;
        }

        std::string getDuties() const override {
            return "Найм, адаптация и учёт персонала";
        }

        std::string getRole() const override {
            return "HR-специалист";
        }

        void print(std::ostream& os) const override {
            os << "[HR-специалист] " << getFullName()
                << " | нанято: " << hiredThisYear << "\n";
        }

        int getHiredThisYear() const { return hiredThisYear; }
    };
}