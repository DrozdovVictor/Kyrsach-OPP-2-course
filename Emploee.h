#pragma once
#include <string>
#include<vector>

#include"Person.h"

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
        : title(title), grade(grade), baseSalary(baseSalary) {}

    const std::string& getTitle() const { 
        return title; 
    }
    int getGrade() const { 
        return grade; 
    }
    double getBaseSalary() const { 
        return baseSalary; 
    }
};

class UserAccount {
    std::string login;
    std::string passwordHash;
    int role = ROLE_ADMIN;
public:
    UserAccount() = default;
    UserAccount(const std::string& login, const std::string& hash, int role)
        : login(login), passwordHash(hash), role(role) {}

    const std::string& getLogin() const { 
        return login; 
    }
    int getRole() const { 
        return role; 
    }
};

class Employee : public Person {
protected:
    int personnelNumber = 0; // id только чисто дл€ работников, а не дл€ всех
    Date hireDate;
    double baseSalary = 0.0; // базовый оклад (то, что сотрудник получает до всех надбавок, бонусов и т.д.)
    int status = 0;

    Position* position = nullptr;   // ассоциаци€, не владеет
    UserAccount* account = nullptr; // композици€, владеет
    std::vector<Skill> skills;      // композици€, по значению

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

    ~Employee() override {
        delete account;   // владеем Ч об€заны удалить
    }

    virtual double calculateSalary() const = 0;
    virtual std::string getDuties() const = 0;
    virtual bool canManage() const { return false; }

    void setPosition(Position* p) { 
        position = p; 
    }
    void setAccount(UserAccount* a) {
        if (account != a) {
            delete account;
            account = a;
        }
    }
    void setStatus(int s) { 
        status = s;
    }

    void addSkill(const Skill& s) { 
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