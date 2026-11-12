#pragma once
#include <stdexcept>
#include <string>

namespace system {

    class HrException : public std::runtime_error {
    public:
        explicit HrException(const std::string& msg) : std::runtime_error(msg) {}
    };

    class ValidationException : public HrException {
    public:
        explicit ValidationException(const std::string& msg) : HrException(msg) {}
    };

    class NotFoundException : public HrException {
    public:
        explicit NotFoundException(const std::string& msg) : HrException(msg) {}
    };

}