#include <iostream>
#include <bcrypt.h>
std::string hashpassword(const std::string& password) {
    return bcrypt::generateHash(password);
}


int main() {
    std::string password;
    std::cout<<"Enter password: ";
    std::cin>>password;
    std::string hashedPassword = hashpassword(password);
    std::cout<<"The password is: "<<hashedPassword<<std::endl;
    return 0;
}


