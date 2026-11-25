#pragma once
#include<iostream>
#include<string>
#include<vector>

#include"Emploee.h"

namespace kyrsach {

    struct Skill {
        std::string name;
        int level = 1;  // 1..5
    };

    class Developer : public Employee {
        int grade = GRADE_JUNIOR;
        std::vector<Skill> skills;

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

        std::string getDuties() const override {
            return "Разработка и поддержка ПО";
        }
        std::string getRole() const override {
            return "Разработчик";
        }
        int getGrade() const {
            return grade;
        }

        void addSkill(const Skill& s) {
            if (s.level < 1 || s.level > 5)
                throw ValidationException("Уровень навыка должен быть 1..5");
            skills.push_back(s);
        }
        const std::vector<Skill>& getSkills() const { 
            return skills;
        }
        int getSkillsCount() const { 
            return static_cast<int>(skills.size()); 
        }

        void print(std::ostream& os) const override {
            os << "[Разработчик] " << getFullName();
        }
    };
}