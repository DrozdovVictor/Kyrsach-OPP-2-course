#pragma once
#include <string>

namespace kyrsach {

	struct Date {
		int day = 1;
		int month = 1;
		int year = 2000;
	};

	// Перегрузка оператора ВВОДА для Date.
    // Не friend: поля Date публичные (struct).
	inline std::istream& operator>>(std::istream& is, Date& d) {
		is >> d.day >> d.month >> d.year;
		return is;
	}

	struct ContactInfo {
		std::string phone;
		std::string email;
	};

	class Person {
	protected:
		int id = 0;
		std::string fullName;
		Date birthDay;
		ContactInfo contacts;

	public:
		Person() = default;
		Person(int id, const std::string& fullName, const Date& birthDay, const ContactInfo& contacts)
			: id(id), fullName(fullName), birthDay(birthDay), contacts(contacts) {
		}
		friend class Storage; // ← доступ к nextId

		int getId() const {
			return id;
		}
		const std::string& getFullName() const {
			return fullName;
		}

		virtual std::string getRole() const = 0;
		virtual void print(std::ostream& os) const = 0;
		const Date& getBirthDay() const { 
			return birthDay;
		}
		const ContactInfo& getContacts() const { 
			return contacts; 
		}

		Person(const Person&) = delete; // запрет копирования
		Person& operator=(const Person&) = delete; // запрет присваивания

		friend std::ostream& operator<<(std::ostream& os, const Person& p) {
			os << "#" << p.id << " ";
			p.print(os);
			return os;
		}

		virtual ~Person() = default;
	};
}