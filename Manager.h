#pragma once
#include<iostream>
#include<string>
#include<vector>

#include"Emploee.h"

class Manager : public Employee {
    std::vector<Employee*> subordinates; // агрегаци€, не владеет (подчинЄнные)
    double bonus = 0.0; // преми€

public:
    Manager(int id, const std::string& fullName,
        const Date& birthDay, const ContactInfo& contacts,
        int personnelNumber, const Date& hireDate, double baseSalary)
        : Employee(id, fullName, birthDay, contacts,
            personnelNumber, hireDate, baseSalary),
        bonus(0.0) {}

    void addSubordinate(Employee* e) { 
        subordinates.push_back(e); 
    }
    void setBonus(double b) { 
        bonus = b; 
    }

    double calculateSalary() const override {
        return getBaseSalary() + bonus
            + 100.0 * static_cast<int>(subordinates.size());
    }

    std::string getDuties() const override {
        return "”правление командой и планирование";
    }

    bool canManage() const override { 
        return true; 
    }

    std::string getRole() const override { 
        return "Manager"; 
    }

    void print(std::ostream& os) const override {
        os << "[Manager] " << getFullName()
            << " | subordinates: " << subordinates.size() << "\n";
    }

    int getSubordinatesCount() const {
        return static_cast<int>(subordinates.size());
    }
};