#pragma once
#include <iostream>
#include <string>
#include <vector>

namespace kyrsach {

    // Вспомогательная функция: считает количество символов в UTF-8,
    // а не байт (кириллица занимает 2 байта, но 1 знакоместо).
    inline size_t utf8_length(const std::string& str) {
        size_t len = 0;
        for (char c : str) {
            if (c == '\r') continue; // Игнорируем возврат каретки Windows
            // Пропускаем байты-продолжения (10xxxxxx)
            if ((c & 0xC0) != 0x80) ++len;
        }
        return len;
    }

    class Table {
        std::vector<std::string> headers;
        std::vector<std::vector<std::string>> rows;
    public:
        Table(std::vector<std::string> h) : headers(h) {}

        void addRow(const std::vector<std::string>& r) {
            rows.push_back(r);
        }

        void print() const {
            if (headers.empty()) return;
            std::vector<size_t> widths(headers.size(), 0);

            for (size_t i = 0; i < headers.size(); ++i) {
                widths[i] = utf8_length(headers[i]);
            }
            for (const auto& row : rows) {
                for (size_t i = 0; i < row.size() && i < widths.size(); ++i) {
                    size_t len = utf8_length(row[i]);
                    if (len > widths[i]) widths[i] = len;
                }
            }

            auto print_sep = [&]() {
                std::cout << "+";
                for (size_t w : widths) std::cout << std::string(w + 2, '-') << "+";
                std::cout << "\n";
                };

            print_sep();
            // Заголовки
            std::cout << "|";
            for (size_t i = 0; i < headers.size(); ++i) {
                std::cout << " " << headers[i] << std::string(widths[i] - utf8_length(headers[i]), ' ') << " |";
            }
            std::cout << "\n";
            print_sep();

            // Данные
            for (const auto& row : rows) {
                std::cout << "|";
                for (size_t i = 0; i < headers.size(); ++i) {
                    std::string val = (i < row.size()) ? row[i] : "";
                    std::cout << " " << val << std::string(widths[i] - utf8_length(val), ' ') << " |";
                }
                std::cout << "\n";
            }
            print_sep();
            //std::cout << rows.size() << " строк(и) в наборе\n";
        }
    };

    inline void printEmployeesTable(Repository<Employee>& employees) {
        if (employees.empty()) {
            std::cout << "  (пусто)\n";
            return;
        }
        Table t({ "ID", "ФИО", "Роль", "Должность", "Статус" });
        for (Employee* e : employees.getAll()) {
            std::string statusStr = (e->getStatus() == STATUS_ACTIVE) ? "Работает" :
                (e->getStatus() == STATUS_VACATION) ? "Отпуск" : "Уволен";

            Position* p = e->getPosition();
            std::string posStr = p ? p->getTitle() : "—"; // Если должности нет, ставим прочерк

            t.addRow({
                std::to_string(e->getId()),
                e->getFullName(),
                e->getRole(),
                posStr,
                statusStr
                });
        }
        t.print();
    }
    inline void printCandidatesTable(Repository<Candidate>& candidates) {
        if (candidates.empty()) {
            std::cout << "  (пусто)\n";
            return;
        }
        Table t({ "ID", "ФИО", "Статус", "Желаемая должность" });
        for (Candidate* c : candidates.getAll()) {
            std::string statusStr = (c->getStatus() == CAND_NEW) ? "Новый" :
                (c->getStatus() == CAND_INTERVIEW) ? "Собеседование" :
                (c->getStatus() == CAND_OFFERED) ? "Оффер" : "Отказ";
            Position* p = c->getDesiredPosition();
            std::string pos = p ? p->getTitle() : "—";
            t.addRow({
                std::to_string(c->getId()),
                c->getFullName(),
                statusStr,
                pos
                });
        }
        t.print();
    }
    inline void printPositionsTable(Repository<Position>& positions) {
        if (positions.empty()) {
            std::cout << "  (пусто)\n";
            return;
        }
        Table t({ "Название", "Грейд" });
        for (Position* p : positions.getAll()) {
            std::string gradeStr = (p->getGrade() == GRADE_JUNIOR) ? "Junior" :
                (p->getGrade() == GRADE_MIDDLE) ? "Middle" :
                (p->getGrade() == GRADE_SENIOR) ? "Senior" : "Lead";
            t.addRow({ p->getTitle(), gradeStr });
        }
        t.print();
    }

}
