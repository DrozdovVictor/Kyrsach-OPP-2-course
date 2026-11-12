#pragma once
#include<iostream>
#include<string>

#include"Person.h"
#include"Emploee.h"

namespace kyrsach {

    const int CAND_NEW = 0; // новый
    const int CAND_INTERVIEW = 1; // на собеседовании
    const int CAND_OFFERED = 2; // получил оффер
    const int CAND_REJECTED = 3; // отказ

    class Candidate : public Person {
        std::string resume;
        Position* desiredPosition = nullptr;   // ассоциация, не владеет
        int status = 0;                        // CAND_NEW = 0

    public:
        Candidate(int id, const std::string& fullName,
            const Date& birthDay, const ContactInfo& contacts)
            : Person(id, fullName, birthDay, contacts),
            desiredPosition(nullptr),
            status(0) {
        }

        void setResume(const std::string& r) {
            resume = r;
        }
        void setDesiredPosition(Position* p) {
            desiredPosition = p;
        }
        void setStatus(int s) {
            if (s < CAND_NEW || s > CAND_REJECTED)
                throw ValidationException("Неверный статус кандидата: " + std::to_string(s));
            status = s;
        }

        std::string getRole() const override {
            return "Кандидат";
        }

        void print(std::ostream& os) const override {
            os << "[Кандидат] " << getFullName()
                << " | статус: " << status;
            if (desiredPosition != nullptr) {
                os << " | желаемая должность: " << desiredPosition->getTitle();
            }
            os << "\n";
        }

        const std::string& getResume() const {
            return resume;
        }
        Position* getDesiredPosition() const {
            return desiredPosition;
        }
        int getStatus() const {
            return status;
        }
    };
}