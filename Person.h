#pragma once
#include <string>

namespace kyrsach {

	struct Date {
		int day = 1;
		int month = 1;
		int year = 2000;
	};

	struct ContactInfo {
		std::string phone;
		std::string email;
		std::string address;
	};

	class Person {
	protected:
		int id = 0;
		std::string fullName;
		Date birthDay;
		ContactInfo contacts;

		static inline int nextId = 1;

	public:
		Person() = default;
		Person(int id, const std::string& fullName, const Date& birthDay, const ContactInfo& contacts)
			: id(id), fullName(fullName), birthDay(birthDay), contacts(contacts) {
		}

		int getId() const {
			return id;
		}
		const std::string& getFullName() const {
			return fullName;
		}

		virtual std::string getRole() const = 0;
		virtual void print(std::ostream& os) const = 0;

		static int generateId() {
			return nextId++;
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