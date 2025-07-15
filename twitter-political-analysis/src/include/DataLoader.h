#ifndef DATALOADER_H
#define DATALOADER_H

#include <string>
#include <vector>
#include "UserandConnections.h"

class DataLoader {
public:
    DataLoader(const std::string& userFile, const std::string& connectionFile);
    std::vector<User> loadUserData();
    std::vector<Connection> loadConnectionData();

private:
    std::string userFilePath;
    std::string connectionFilePath;
};

#endif // DATALOADER_H