#pragma once
#include <string>

#include"Classes.h"

namespace kyrsach {

    // ѕаттерн Ђ‘абричный методї (Factory Method).
    // “олько статические методы Ч экземпл€р создать нельз€.
    class EmployeeFactory {
        inline static int nextPersonnelNumber = 101;

    public:
        EmployeeFactory() = delete;
        friend class Storage;

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