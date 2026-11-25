#pragma once
#include <vector>
#include <iostream>
#include <string>

#include <memory>

#include "Exceptions.h"

namespace kyrsach {

    // Ўаблонный класс Ч обЄртка над vector<unique_ptr<T>> с владением
    template<typename T>
    class Repository {
        std::vector<std::unique_ptr<T>> items;

    public:
        Repository() = default;
        ~Repository() = default;

        Repository(const Repository&) = delete;
        Repository& operator=(const Repository&) = delete;

        void add(T* item) {
            if (item == nullptr)
                throw ValidationException("Ќельз€ добавить пустой указатель в репозиторий");
            items.push_back(std::unique_ptr<T>(item));
        }

        // findById Ч есть у T метод getId() (Person и наследники).
        // ƒл€ типов без getId метод не инстанцируетс€, пока его не вызовут.
        T* findById(int id) const {
            for (const auto& item : items) {
                if (item->getId() == id) return item.get();
            }
            throw NotFoundException("ќбъект с id=" + std::to_string(id) + " не найден");
        }

        // Ўаблонный метод: поиск по предикату
        template<typename Predicate>
        T* findFirst(Predicate pred) const {
            for (const auto& item : items) {
                if (pred(item.get())) return item.get();
            }
            throw NotFoundException("ќбъект не найден по заданному критерию");
        }

        // Ўаблонный метод: найти всех по предикату
        template<typename Predicate>
        std::vector<T*> findAll(Predicate pred) const {
            std::vector<T*> result;
            for (const auto& item : items) {
                if (pred(item.get())) result.push_back(item.get());
            }
            return result;
        }

        void removeById(int id) {
            for (auto it = items.begin(); it != items.end(); ++it) {
                if ((*it)->getId() == id) {
                    items.erase(it);
                    return;
                }
            }
            throw NotFoundException("ќбъект с id=" + std::to_string(id) + " не найден");
        }

        std::vector<T*> getAll() const {
            std::vector<T*> result;
            result.reserve(items.size());
            for (const auto& item : items) {
                result.push_back(item.get());
            }
            return result;
        }

        int  size()  const { return static_cast<int>(items.size()); }
        bool empty() const { return items.empty(); }

        void clear() {
            items.clear();
        }
    };
}
