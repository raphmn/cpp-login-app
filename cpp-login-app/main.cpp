#include <iostream>
#include <fstream>
#include <unordered_map>
#include  <string>
using namespace std;
unordered_map<string, string> loadUsers() {
    unordered_map<string, string> users;
    ifstream usersFile("users.txt");
    string username,password;
    while (usersFile >> username >> password) {
        users[username] = password;
    }
    return users;
}

bool validateUser(const unordered_map<string, string>& users,const string& username,const string& password) {
    return users.count(username) && users.at(username) == password;
}