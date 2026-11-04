#pragma once
#include<iostream>
#include<string>

#include"Person.h"
#include"Emploee.h"

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
        status(0) {}

    void setResume(const std::string& r) { 
        resume = r;
    }
    void setDesiredPosition(Position* p) { 
        desiredPosition = p; 
    }
    void setStatus(int s) { 
        status = s;
    }

    std::string getRole() const override { 
        return "Candidate";
    }

    void print(std::ostream& os) const override {
        os << "[Candidate] " << getFullName()
            << " | status: " << status << "\n";
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