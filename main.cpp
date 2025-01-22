#include <iostream>
#include <bcrypt.h>
std::string hashpassword(const std::string& password) {
    char salt[BCRYPT_HASHSIZE];
    char hash [BCRYPT_HASHSIZE];
    bcrypt_gensalt(12,salt);
    bcrypt_hashpw(password.c_str(),salt,hash);
    return std::string(hash);

int main() {
    std::string password;
    std::cout<<"Enter password: ";
    std::cin>>password;
    std::string hashedPassword = hashpassword(password);
    std::cout<<"The password is: "<<hashedPassword<<std::endl;
    return 0;
}
