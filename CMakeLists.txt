cmake_minimum_required(VERSION 3.10) # Version minimum de CMake
project(project)

# Utilisation de C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Configuration de bcrypt
add_subdirectory(./Bcrypt.cpp-master)

# Configuration d'OpenCV
set(OpenCV_DIR "C:/opencv/") # Chemin vers OpenCV
find_package(OpenCV REQUIRED)
file(GLOB OPENCV_DLL_FILES "C:/opencv/x64/mingw/bin/*.dll")
file(COPY ${OPENCV_DLL_FILES} DESTINATION ${CMAKE_BINARY_DIR})

# Ajouter qrcodegen (les fichiers qrcodegen.c et qrcodegen.h doivent être dans libqrcodegen/)
add_library(qrcodegen STATIC libqrcodegen/qrcodegen.c)
target_include_directories(qrcodegen PUBLIC libqrcodegen)

# Inclure les répertoires
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(./Bcrypt.cpp-master)
include_directories(libqrcodegen)

# Création de l'exécutable
add_executable(project main2.cpp)

# Lier les bibliothèques
target_link_libraries(project bcrypt ${OpenCV_LIBS} qrcodegen)
