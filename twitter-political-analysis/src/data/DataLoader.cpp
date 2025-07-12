#include "DataLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

// Constructor para inicializar las rutas de los archivos
// userFile: archivo que contiene los datos de los usuarios
// connectionFile: archivo que contiene los seguidores y seguidos
// userFilePath: ruta del archivo de usuarios
// connectionFilePath: ruta del archivo de conexiones
DataLoader::DataLoader(const std::string& userFile, const std::string& connectionFile)
    : userFilePath(userFile), connectionFilePath(connectionFile) {}

// Carga los datos de los usuarios desde el archivo especificado
// userFilePath: ruta del archivo de usuarios
// Devuelve un vector de estructuras User con los datos de los usuarios
std::vector<User> DataLoader::loadUserData() {
    std::vector<User> users;    
    std::ifstream file(userFilePath);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Failed to open user data file: " << userFilePath << std::endl;
        return users;
    }

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        User user;
        std::getline(ss, user.user_id, ';');
        std::getline(ss, user.user_name, ';');
        std::getline(ss, user.number_tweets, ';');
        std::getline(ss, user.friends_count, ';');
        std::getline(ss, user.followers_count, ';');
        std::getline(ss, user.created_at);
        users.push_back(user);
    }

    file.close();
    return users;
}

// Carga los datos de las conexiones desde el archivo especificado
// connectionFilePath: ruta del archivo de conexiones
// Devuelve un vector de estructuras Connection con los datos de las conexiones
std::vector<Connection> DataLoader::loadConnectionData() {
    std::vector<Connection> connections;
    std::ifstream file(connectionFilePath);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Failed to open connection data file: " << connectionFilePath << std::endl;
        return connections;
    }

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        Connection connection;
        std::getline(ss, connection.followee, ';');
        std::getline(ss, connection.follower);
        connections.push_back(connection);
    }

    file.close();
    return connections;
}