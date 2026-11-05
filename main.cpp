#include<iostream>
#include"Classes.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    Date birthDev{ 1, 1, 1998 };
    Date birthMgr{ 2, 2, 1990 };
    Date birthHR{ 3, 3, 1995 };
    Date birthCand{ 4, 4, 2000 };

    Date hireDev{ 1, 9, 2023 };
    Date hireMgr{ 1, 3, 2020 };
    Date hireHR{ 5, 5, 2021 };

    ContactInfo contactDev{ "+375 29 111-11-11", "dev@it.by",  "Minsk" };
    ContactInfo contactMgr{ "+375 29 222-22-22", "mgr@it.by",  "Minsk" };
    ContactInfo contactHR{ "+375 29 333-33-33", "hr@it.by",   "Minsk" };
    ContactInfo contactCand{ "+375 29 444-44-44", "cand@mail.by","Gomel" };

    // ---------- Внешние сущности ----------
    Position posCpp("C++ Developer", GRADE_MIDDLE, 1500.0);
    Position posQA("QA Engineer", GRADE_JUNIOR, 900.0);

    // ---------- Developer ----------
    Developer dev(1, "Иванов И.И.", birthDev, contactDev,
        101, hireDev, 1500.0, GRADE_MIDDLE);
    dev.addTechnology("C++");
    dev.addTechnology("Qt");
    dev.addTechnology("CMake");
    dev.addSkill(Skill{ "C++", 4 });
    dev.addSkill(Skill{ "Qt",  3 });
    dev.setPosition(&posCpp);
    dev.setAccount(new UserAccount("ivanov", "hash1", ROLE_EMPLOYEE));

    // ---------- Manager ----------
    Manager mgr(2, "Петров П.П.", birthMgr, contactMgr,
        102, hireMgr, 2500.0);
    mgr.setBonus(500.0);
    mgr.addSubordinate(&dev);
    mgr.setAccount(new UserAccount("petrov", "hash2", ROLE_MANAGER));

    // ---------- HRSpecialist ----------
    HRSpecialist hr(3, "Сидорова А.А.", birthHR, contactHR,
        103, hireHR, 1200.0);
    hr.incrementHired();
    hr.incrementHired();
    hr.incrementHired();
    hr.setAccount(new UserAccount("sidorova", "hash3", ROLE_HR));

    // ---------- Candidate ----------
    Candidate cand(10, "Смирнов С.С.", birthCand, contactCand);
    cand.setResume("3 года C++, Qt, CMake");
    cand.setDesiredPosition(&posCpp);
    cand.setStatus(CAND_INTERVIEW);

    // Прямые вызовы — видно индивидуальное поведение
    cout << "=== Прямые вызовы ===\n\n";

    dev.print(cout);
    cout << "  role      : " << dev.getRole() << "\n"
        << "  grade     : " << dev.getGrade() << "\n"
        << "  techs     : " << dev.getTechCount() << "\n"
        << "  skills    : " << dev.getSkillsCount() << "\n"
        << "  salary    : " << dev.calculateSalary() << "\n"
        << "  canManage : " << dev.canManage() << "\n\n";

    mgr.print(cout);
    cout << "  role      : " << mgr.getRole() << "\n"
        << "  subs      : " << mgr.getSubordinatesCount() << "\n"
        << "  salary    : " << mgr.calculateSalary() << "\n"
        << "  canManage : " << mgr.canManage() << "\n\n";

    hr.print(cout);
    cout << "  role      : " << hr.getRole() << "\n"
        << "  hired     : " << hr.getHiredThisYear() << "\n"
        << "  salary    : " << hr.calculateSalary() << "\n"
        << "  canManage : " << hr.canManage() << "\n\n";

    cand.print(cout);
    cout << "  role      : " << cand.getRole() << "\n"
        << "  status    : " << cand.getStatus() << "\n"
        << "  resume    : " << cand.getResume() << "\n"
        << "  desiredPos: "
        << (cand.getDesiredPosition()
            ? cand.getDesiredPosition()->getTitle()
            : "—")
        << "\n\n";

    // Полиморфизм через Employee* — только сотрудники
    cout << "=== Полиморфизм через Employee* ===\n\n";

    Employee* staff[3] = { &dev, &mgr, &hr };
    for (int i = 0; i < 3; ++i) {
        staff[i]->print(cout);
        cout << "  role      : " << staff[i]->getRole() << "\n"
            << "  duties    : " << staff[i]->getDuties() << "\n"
            << "  salary    : " << staff[i]->calculateSalary() << "\n"
            << "  canManage : " << staff[i]->canManage() << "\n\n";
    }

    // Полиморфизм через Person* — все люди в системе
    cout << "=== Полиморфизм через Person* ===\n\n";

    Person* everyone[4] = { &dev, &mgr, &hr, &cand };
    for (int i = 0; i < 4; ++i) {
        everyone[i]->print(cout);
        cout << "  role      : " << everyone[i]->getRole() << "\n\n";
    }

    // Демонстрация владения : account удалится в ~Employee
    cout << "=== Деструкторы ===\n";
    cout << "dev, mgr, hr, cand — на стеке.\n"
        << "При выходе из main ~Employee() удалит account.\n";
    return 0;
}