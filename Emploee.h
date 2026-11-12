#pragma once
#include <string>
#include<vector>
#include <memory>      // для std::unique_ptr
#include <utility>     // для std::move

#include"Person.h"
#include "Exceptions.h"

namespace kyrsach {

    // grades
    const int GRADE_JUNIOR = 0;
    const int GRADE_MIDDLE = 1;
    const int GRADE_SENIOR = 2;
    const int GRADE_LEAD = 3;

    // roles
    const int ROLE_ADMIN = 0;
    const int ROLE_HR = 1;
    const int ROLE_MANAGER = 2;
    const int ROLE_EMPLOYEE = 3;

    // statuses
    const int STATUS_ACTIVE = 0;   // работает
    const int STATUS_VACATION = 1;   // в отпуске
    const int STATUS_FIRED = 2;   // уволен

    struct Skill {
        std::string name;
        int level = 1;  // 1..5
    };

    class Position {
        std::string title;
        int grade = GRADE_JUNIOR;
        double baseSalary = 0.0;

    public:
        Position() = default;
        Position(const std::string& title, int grade, double baseSalary)
            : title(title), grade(grade), baseSalary(baseSalary) {
        }

        const std::string& getTitle() const {
            return title;
        }
        int getGrade() const {
            return grade;
        }
        double getBaseSalary() const {
            return baseSalary;
        }

        bool operator==(const Position& other) const {
            return title == other.title && grade == other.grade;
        }
    };

    class UserAccount {
        std::string login;
        std::string passwordHash;
        int role = ROLE_ADMIN;
    public:
        UserAccount() = default;
        UserAccount(const std::string& login, const std::string& hash, int role)
            : login(login), passwordHash(hash), role(role) {
        }

        const std::string& getLogin() const {
            return login;
        }
        int getRole() const {
            return role;
        }
    };

    class Employee : public Person {
    protected:
        int personnelNumber = 0; // id только чисто для работников, а не для всех
        Date hireDate;
        double baseSalary = 0.0; // базовый оклад (то, что сотрудник получает до всех надбавок, бонусов и т.д.)
        int status = 0;

        Position* position = nullptr;   // ассоциация, не владеет
        std::unique_ptr<UserAccount> account;  // композиция (умный указатель)
        std::vector<Skill> skills;      // композиция, по значению

    public:
        Employee(int id, const std::string& fullName,
            const Date& birthDay, const ContactInfo& contacts,
            int personnelNumber, const Date& hireDate, double baseSalary)
            : Person(id, fullName, birthDay, contacts),
            personnelNumber(personnelNumber),
            hireDate(hireDate),
            baseSalary(baseSalary),
            status(STATUS_ACTIVE),
            position(nullptr),
            account(nullptr) {}

        ~Employee() override = default;

        virtual double calculateSalary() const = 0;
        virtual std::string getDuties() const = 0;
        virtual bool canManage() const {
            return false;
        }

        void setPosition(Position* p) {
            position = p;
        }
        void setAccount(std::unique_ptr<UserAccount> a) {
            account = std::move(a);   // старое автоматически удалится
        }

        void setStatus(int s) {
            if (s < STATUS_ACTIVE || s > STATUS_FIRED)
                throw ValidationException("Неверный статус: " + std::to_string(s));
            status = s;
        }
        void setStatus(const std::string& name) {
            if (name == "активный" || name == "active") setStatus(STATUS_ACTIVE);
            else if (name == "отпуск" || name == "vacation") setStatus(STATUS_VACATION);
            else if (name == "уволен" || name == "fired") setStatus(STATUS_FIRED);
            else throw ValidationException("Неизвестный статус: " + name);
        }
        void addSkill(const Skill& s) {
            if (s.level < 1 || s.level > 5)
                throw ValidationException("Уровень навыка должен быть 1..5");
            skills.push_back(s);
        }

        int getStatus() const {
            return status;
        }
        double getBaseSalary() const {
            return baseSalary;
        }
        int getSkillsCount() const {
            return static_cast<int>(skills.size());
        }
    };
}