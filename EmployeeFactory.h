#pragma once
#include <string>

#include"Classes.h"

namespace kyrsach {

    // Паттерн «Фабричный метод» (Factory Method).
    // Только статические методы — экземпляр создать нельзя.
    class EmployeeFactory {
        inline static int nextPersonnelNumber = 101;

    public:
        EmployeeFactory() = delete;
        friend class Storage; // ← доступ к nextPersonnelNumber

        static Developer* createDeveloper(
            const std::string& fullName,
            const Date& birthDay,
            const ContactInfo& contacts,
            const Date& hireDate,
            int grade)
        {
            return new Developer(
                Person::generateId(),
                fullName, birthDay, contacts,
                nextPersonnelNumber++,
                hireDate, grade);
        }

        static Manager* createManager(
            const std::string& fullName,
            const Date& birthDay,
            const ContactInfo& contacts,
            const Date& hireDate)
        {
            return new Manager(
                Person::generateId(),
                fullName, birthDay, contacts,
                nextPersonnelNumber++,
                hireDate);
        }

        static HRSpecialist* createHR(
            const std::string& fullName,
            const Date& birthDay,
            const ContactInfo& contacts,
            const Date& hireDate)
        {
            return new HRSpecialist(
                Person::generateId(),
                fullName, birthDay, contacts,
                nextPersonnelNumber++,
                hireDate);
        }

        static Candidate* createCandidate(
            const std::string& fullName,
            const Date& birthDay,
            const ContactInfo& contacts)
        {
            return new Candidate(
                Person::generateId(),
                fullName, birthDay, contacts);
        }
    };

}