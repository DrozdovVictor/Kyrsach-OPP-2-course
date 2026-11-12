#pragma once
#include <vector>
#include <iostream>
#include <string>

#include "Exceptions.h"

namespace kyrsach {

    // Ўаблонный класс Ч обЄртка над vector<T*> с владением
    template<typename T>
    class Repository {
        std::vector<T*> items;

    public:
        Repository() = default;
        ~Repository() { clear(); }

        Repository(const Repository&) = delete;
        Repository& operator=(const Repository&) = delete;

        void add(T* item) {
            if (item == nullptr)
                throw ValidationException("Ќельз€ добавить пустой указатель в репозиторий");
            items.push_back(item);
        }

        // findById Ч есть у T метод getId() (Person и наследники).
        // ƒл€ типов без getId метод не инстанцируетс€, пока его не вызовут.
        T* findById(int id) const {
            for (T* item : items) {
                if (item->getId() == id) return item;
            }
            throw NotFoundException("ќбъект с id=" + std::to_string(id) + " не найден");
        }

        // Ўаблонный метод: поиск по предикату
        template<typename Predicate>
        T* findFirst(Predicate pred) const {
            for (T* item : items) {
                if (pred(item)) return item;
            }
            throw NotFoundException("ќбъект не найден по заданному критерию");
        }

        // Ўаблонный метод: найти всех по предикату
        template<typename Predicate>
        std::vector<T*> findAll(Predicate pred) const {
            std::vector<T*> result;
            for (T* item : items) {
                if (pred(item)) result.push_back(item);
            }
            return result;
        }

        void removeById(int id) {
            for (auto it = items.begin(); it != items.end(); ++it) {
                if ((*it)->getId() == id) {
                    delete* it;
                    items.erase(it);
                    return;
                }
            }
            throw NotFoundException("ќбъект с id=" + std::to_string(id) + " не найден");
        }

        const std::vector<T*>& getAll() const { return items; }
        int  size()  const { return static_cast<int>(items.size()); }
        bool empty() const { return items.empty(); }

        void clear() {
            for (T* item : items) delete item;
            items.clear();
        }
    };

    // Ўаблонна€ функци€ Ч печатает всЄ, что поддерживает operator<<
    template<typename T>
    void printAll(const Repository<T>& repo) {
        if (repo.empty()) {
            std::cout << "  (пусто)\n";
            return;
        }
        for (T* item : repo.getAll()) {
            std::cout << "  " << *item;
        }
    }

}  // namespace kyrsach
