#include "auth.h"
#include "bcrypt.h"
#include <fstream>
#include <iostream>


std::unordered_map<std::string, std::string> LoadUsers() {
    std::unordered_map<std::string, std::string> users;
    std::ifstream file("users.txt");

    std::string username, hashedPassword;
    while (file >> username >> hashedPassword) {
        users[username] = hashedPassword;
    }

    return users;
}

bool AuthenticateUser(const std::string& username, const std::string& password) {
    static auto users = LoadUsers();

    auto it = users.find(username);
    if (it == users.end()) return false;

    return bcrypt::validatePassword(password, it->second);
}
