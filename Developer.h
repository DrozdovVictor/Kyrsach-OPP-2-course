#pragma once
#include<iostream>
#include<string>
#include<vector>

#include"Emploee.h"

namespace kyrsach {

    class Developer : public Employee {
        int grade = GRADE_JUNIOR;
        std::vector<std::string> techStack;   // композиция

    public:
        Developer(int id, const std::string& fullName,
            const Date& birthDay, const ContactInfo& contacts,
            int personnelNumber, const Date& hireDate,
            double baseSalary, int grade)
            : Employee(id, fullName, birthDay, contacts,
                personnelNumber, hireDate, baseSalary),
            grade(grade) {
            if (grade < GRADE_JUNIOR || grade > GRADE_LEAD)
                throw ValidationException("Неверный грейд: " + std::to_string(grade));
        }

        void addTechnology(const std::string& t) {
            techStack.push_back(t);
        }

        double calculateSalary() const override {
            double k = 1.0;
            if (grade == GRADE_JUNIOR) k = 1.0;
            else if (grade == GRADE_MIDDLE) k = 1.5;
            else if (grade == GRADE_SENIOR) k = 2.2;
            else if (grade == GRADE_LEAD)   k = 3.0;
            return getBaseSalary() * k;
        }

        std::string getDuties() const override {
            return "Разработка и поддержка ПО";
        }
        std::string getRole() const override {
            return "Разработчик";
        }
        int getGrade() const {
            return grade;
        }
        int getTechCount() const {
            return static_cast<int>(techStack.size());
        }

        void print(std::ostream& os) const override {
            os << "[Разработчик] " << getFullName()
                << " | технологий: " << techStack.size() << "\n";
        }
    };
}