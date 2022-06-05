#include "password.h"
bool ValidatePassword(const std::string& password) {
    if (password.size() < 8) {
        return false;
    }
    if (password.size() > 14) {
        return false;
    }

    for (size_t i = 0; i < password.size(); i++) {
        if (password[i] < 33) {
            return false;
        }
        if (password[i] > 126) {
            return false;
        }
    }

    int type_count[4] = {0, 0, 0, 0};
    for (size_t i = 0; i < password.size(); i++) {
        if ('0' <= password[i] && password[i] <= '9') {
            type_count[0] = 1;
            continue;
        }
        if ('A' <= password[i] && password[i] <= 'Z') {
            type_count[1] = 1;
            continue;
        }
        if ('a' <= password[i] && password[i] <= 'z') {
            type_count[2] = 1;
            continue;
        }
        type_count[3] = 1;
    }

    int sum = 0;
    for (size_t i = 0; i < 4; i++) {
        sum += type_count[i];
    }

    if (sum < 3) {
        return false;
    }

    return true;
}