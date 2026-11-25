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
            int personnelNumber, const Date& hireDate, int grade)
            : Employee(id, fullName, birthDay, contacts,
                personnelNumber, hireDate),
            grade(grade) {
            if (grade < GRADE_JUNIOR || grade > GRADE_LEAD)
                throw ValidationException("Неверный грейд: " + std::to_string(grade));
        }

        void addTechnology(const std::string& t) {
            techStack.push_back(t);
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
        const std::vector<std::string>& getTechStack() const { 
            return techStack; 
        }

        void print(std::ostream& os) const override {
            os << "[Разработчик] " << getFullName()
                << " | технологий: " << techStack.size() << "\n";
        }
    };
}