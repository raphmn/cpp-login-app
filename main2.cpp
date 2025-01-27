#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <opencv2/opencv.hpp>
#include "bcrypt.h"
#include "qrcodegen.h"
#include <opencv2/highgui.hpp> // Inclure pour cv::imshow
#include <opencv2/imgcodecs.hpp> // Inclure pour cv::imread

// Fonction pour hacher un mot de passe
std::string hashPassword(const std::string& password) {
    return bcrypt::generateHash(password);
}

// Fonction pour vérifier un mot de passe
bool verifyPassword(const std::string& password, const std::string& hashedPassword) {
    return bcrypt::validatePassword(password, hashedPassword);
}

// Fonction pour générer et afficher un QR code
void generateAndShowQRCode(const std::string& data, const std::string& filename) {
    uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];
    uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];

    // Générer le QR code avec les données fournies
    bool success = qrcodegen_encodeText(data.c_str(), tempBuffer, qrcode, qrcodegen_Ecc_LOW,
                                        qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);
    if (!success) {
        std::cerr << "Erreur : Impossible de générer le QR code.\n";
        return;
    }

    int size = qrcodegen_getSize(qrcode);
    int border = 4;

    // Créer une image OpenCV pour afficher le QR code
    int imageSize = (size + 2 * border) * 10;
    cv::Mat qrImage(imageSize, imageSize, CV_8UC1, cv::Scalar(255));

    for (int y = -border; y < size + border; y++) {
        for (int x = -border; x < size + border; x++) {
            bool module = (y >= 0 && y < size && x >= 0 && x < size) ? qrcodegen_getModule(qrcode, x, y) : false;
            cv::rectangle(qrImage, cv::Point((x + border) * 10, (y + border) * 10),
                          cv::Point((x + border + 1) * 10 - 1, (y + border + 1) * 10 - 1),
                          module ? cv::Scalar(0) : cv::Scalar(255), cv::FILLED);
        }
    }

    // Afficher et sauvegarder l'image
    cv::imshow("QR Code", qrImage);
    cv::imwrite(filename, qrImage);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

// Fonction pour sauvegarder les utilisateurs dans un fichier
void saveUsers(const std::unordered_map<std::string, std::string>& users, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier pour sauvegarder les utilisateurs.\n";
        return;
    }

    for (const auto& [username, hashedPassword] : users) {
        file << username << " " << hashedPassword << "\n";
    }
    file.close();
}

// Fonction pour charger les utilisateurs depuis un fichier
void loadUsers(std::unordered_map<std::string, std::string>& users, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Erreur : Impossible d'ouvrir le fichier pour charger les utilisateurs.\n";
        return;
    }

    std::string username, hashedPassword;
    while (file >> username >> hashedPassword) {
        users[username] = hashedPassword;
    }
    file.close();
}

// Fonction pour scanner et valider un QR code
bool scanQRCode(const std::string& expectedData) {
    cv::VideoCapture camera(0);
    if (!camera.isOpened()) {
        std::cerr << "Impossible d'ouvrir la caméra.\n";
        return false;
    }

    cv::Mat frame;
    cv::QRCodeDetector detector;
    while (true) {
        camera >> frame;
        std::string data = detector.detectAndDecode(frame);

        if (!data.empty()) {
            if (data == expectedData) {
                std::cout << "QR code validé : " << data << "\n";

                // Libération de la caméra avant d'afficher l'image
                camera.release();
                cv::destroyAllWindows();

                // Afficher l'image "pregnant.png"
                std::string filePath = "C:/Users/corth/CLionProjects/project/secret/pregnant.png";
                cv::Mat image = cv::imread(filePath);

                if (image.empty()) {
                    std::cerr << "Erreur : Impossible de charger l'image : " << filePath << "\n";
                    return false;
                } else {
                    cv::imshow("Succès - Image Secrète", image);
                    cv::waitKey(0); // Attente que l'utilisateur ferme la fenêtre
                    cv::destroyAllWindows();
                    return true;
                }
            } else {
                std::cerr << "QR code incorrect : " << data << "\n";
            }
        }

        cv::imshow("Scanner QR Code", frame);
        if (cv::waitKey(15) >= 0) break;
    }

    camera.release();
    cv::destroyAllWindows();
    return false;
}

// Fonction pour enregistrer un utilisateur
void registerUser(std::unordered_map<std::string, std::string>& users, const std::string& dbFilename) {
    std::string username, password;
    std::cout << "Entrez un nom d'utilisateur : ";
    std::cin >> username;

    if (users.find(username) != users.end()) {
        std::cout << "Nom d'utilisateur déjà existant. Essayez un autre.\n";
        return;
    }

    std::cout << "Entrez un mot de passe : ";
    std::cin >> password;

    std::string hashedPassword = hashPassword(password);
    users[username] = hashedPassword;

    // Chemin d'accès au QR code
    std::string qrCodeFilename = "C:/Users/corth/CLionProjects/project/qrcodeuser/" + username + "_qrcode.png";
    generateAndShowQRCode(username, qrCodeFilename);

    // Sauvegarder les utilisateurs dans le fichier
    saveUsers(users, dbFilename);

    std::cout << "Utilisateur enregistré avec succès ! QR code généré et sauvegardé.\n";
}

// Fonction pour se connecter
void loginUser(const std::unordered_map<std::string, std::string>& users) {
    std::string username, password;
    std::cout << "Entrez votre nom d'utilisateur : ";
    std::cin >> username;

    auto it = users.find(username);
    if (it == users.end()) {
        std::cout << "Nom d'utilisateur invalide.\n";
        return;
    }

    std::cout << "Entrez votre mot de passe : ";
    std::cin >> password;

    if (!verifyPassword(password, it->second)) {
        std::cout << "Mot de passe incorrect.\n";
        return;
    }

    std::cout << "Veuillez scanner votre QR code pour la double authentification...\n";
    if (!scanQRCode(username)) {
        std::cout << "Échec de l'authentification QR code.\n";
        return;
    }

    std::cout << "Connexion réussie !\n";
}

int main() {
    std::unordered_map<std::string, std::string> users;
    const std::string dbFilename = "C:/Users/corth/CLionProjects/project/users.txt";

    // Charger les utilisateurs depuis le fichier
    loadUsers(users, dbFilename);

    int choice;
    while (true) {
        std::cout << "1. Enregistrer\n2. Se connecter\n3. Quitter\nChoisissez une option : ";
        std::cin >> choice;

        if (choice == 1) {
            registerUser(users, dbFilename);
        } else if (choice == 2) {
            loginUser(users);
        } else if (choice == 3) {
            break;
        } else {
            std::cout << "Choix invalide. Réessayez.\n";
        }
    }

    return 0;
}
