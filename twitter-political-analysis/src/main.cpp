#include <iostream>
#include "DataLoader.h"
#include "PoliticalAnalyzer.h"
#include "UserGraph.h"

int main() {
    // Initialize file paths for user and connection data
    std::string userFilePath = "data/twitter_users.csv";
    std::string connectionFilePath = "data/connections.csv";
    // Initialize the data loader
    DataLoader dataLoader(userFilePath, connectionFilePath);
    
    // Load user and connection data
    std::vector<User> users = dataLoader.loadUserData();
    std::vector<Connection> connection = dataLoader.loadConnectionData();
    
    std::cout << "Loaded " << users.size() << " users and " 
              << connections.size() << " connections." << std::endl;
    // Initialize the political analyzer
    //PoliticalAnalyzer politicalAnalyzer(userGraph);
    
    // Analyze political tendencies
    //politicalAnalyzer.assignPoliticalTendency();
    
    // Report influential users
    //politicalAnalyzer.reportInfluentialUsers();
    
    std::cout << "Analysis complete." << std::endl;
    return 0;
}