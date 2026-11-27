#pragma once
#include <string>
#include<vector>

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

    class Position {
        std::string title;
        int grade = GRADE_JUNIOR;
        //int roleType = 1; // 1-Dev, 2-Mgr, 3-HR
    public:
        Position() = default;
        Position(const std::string& title, int grade)
            : title(title), grade(grade) {
        }

        const std::string& getTitle() const {
            return title;
        }
        int getGrade() const {
            return grade;
        }
        //int getRoleType() const { 
        //    return roleType; 
        //}

        bool operator==(const Position& other) const {
            return title == other.title && grade == other.grade;
        }
    };

    class Employee : public Person {
    protected:
        int personnelNumber = 0; // id только чисто для работников, а не для всех
        Date hireDate;
        int status = 0;

        Position* position = nullptr;   // ассоциация, не владеет

        inline static int nextId = 1;
        friend class Storage; // Чтобы Storage мог обновлять nextId при загрузке

    public:
        Employee(int id, const std::string& fullName,
            const Date& birthDay, const ContactInfo& contacts,
            int personnelNumber, const Date& hireDate)
            : Person(id, fullName, birthDay, contacts),
            personnelNumber(personnelNumber),
            hireDate(hireDate),
            status(STATUS_ACTIVE),
            position(nullptr)
        {}

        ~Employee() override = default;

        virtual std::string getDuties() const = 0;
        int getStatus() const {
            return status;
        }
        int getPersonnelNumber() const {
            return personnelNumber;
        }
        const Date& getHireDate() const {
            return hireDate;
        }
        Position* getPosition() const {
            return position;
        }

        void setPosition(Position* p) {
            position = p;
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
        void setPersonnelNumber(int pn) { 
            personnelNumber = pn; 
        }
        void setHireDate(const Date& date) { 
            hireDate = date; 
        }

        static int generateId() {
            return nextId++;
        }
        virtual bool canManage() const {
            return false;
        }
    };
}