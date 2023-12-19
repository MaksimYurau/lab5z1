#pragma once

#include <exception>
#include <string>

class CustomException : public std::exception {
public:
    CustomException(const std::string& message, double errorValue, int errorCode)
        : errorMessage(message), errorValue(errorValue), errorCode(errorCode) {}

    const char* what() const noexcept override {
        return errorMessage.c_str();
    }

    double getErrorValue() const {
        return errorValue;
    }

    int getErrorCode() const {
        return errorCode;
    }

private:
    std::string errorMessage;
    double errorValue;
    int errorCode;
};
