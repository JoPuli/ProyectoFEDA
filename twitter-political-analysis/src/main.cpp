#include <iostream>
#include <sstream>
#include <unordered_set>
#include <string>
#include <vector>
#include "DataLoader.h"
#include "UserGraph.h"
#include "SCCFinder.h"
#include "Ranking.h"
//#include "PoliticalAnalyzer.h"





int main(int argc, char* argv[]) {
    // Default file paths
    std::string userFilePath = "../data/twitter_users.csv";
    std::string connectionFilePath = "../data/twitter_connections.csv";

    // Exclusion lists
    std::unordered_set<std::string> excludeFollowing = {};
    std::unordered_set<std::string> excludeFollower = {};

    // Option flags
    size_t N = 10;
    std::unordered_map<std::string, std::string> politicalTendency = {
        {"Cooperativa", "izquierda"},
        {"elmostrador", "libertario"},
        {"soyvaldiviacl", "derecha"},
        {"latercera", "centro"}
    };

    // Parse arguments using flags
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if ((arg == "--users-path" || arg == "-up") && i + 1 < argc) {
            userFilePath = argv[++i];
        } else if ((arg == "--connections-path" || arg == "-cp") && i + 1 < argc) {
            connectionFilePath = argv[++i];
        } else if ((arg == "--exclude-following" || arg == "-eg") && i + 1 < argc) {
            std::istringstream iss(argv[++i]);
            std::string name;
            while (std::getline(iss, name, ',')) {
                if (!name.empty()) excludeFollowing.insert(name);
            }
        } else if ((arg == "--exclude-follower" || arg == "-er") && i + 1 < argc) {
            std::istringstream iss(argv[++i]);
            std::string name;
            while (std::getline(iss, name, ',')) {
                if (!name.empty()) excludeFollower.insert(name);
            }
        } else if ((arg == "--top-n" || arg == "-tn") && i + 1 < argc) {
            N = std::stoul(argv[++i]);
        }
    }

    // Initialize the data loader
    DataLoader dataLoader(userFilePath, connectionFilePath);

    // Load user and connection data
    std::vector<User> users = dataLoader.loadUserData();
    std::vector<Connection> connections = dataLoader.loadConnectionData();
    
    std::cout << "Loaded " << users.size() << " users and " 
              << connections.size() << " connections." << std::endl;

    // Initialize the user graph
    UserGraph userGraph;
    for (const auto& connection : connections) {
        // Exclude if follower or followee is in exclusion lists
        if (excludeFollowing.count(connection.follower) || excludeFollower.count(connection.followee)) {
            std::cout << "Excluding connection from " << connection.follower 
                      << " to " << connection.followee << " due to exclusion list." << std::endl;
            continue;
        }
        userGraph.addConnection(connection.follower, connection.followee);
    }
    for (const auto& user : users) {
        if (excludeFollowing.count(user.user_name) || excludeFollower.count(user.user_name)) {
            std::cout << "Excluding user " << user.user_name 
                      << " due to exclusion list." << std::endl;
            continue;
        }
        userGraph.addUser(user.user_name);
    }
    
    // Initialize the SCC finder
    SCCFinder sccFinder(userGraph.FollowingList, userGraph.FollowersList);
    std::cout << "Testing SCCFinder with " 
              << userGraph.FollowingList.size() << " followees and " 
              << userGraph.FollowersList.size() << " followers." 
              << std::endl;

    // Find strongly connected components
    std::vector<std::vector<std::string>> sccs = sccFinder.getSCCs();
    std::cout << "Found " << sccs.size() << " strongly connected components." << std::endl;
    for (const auto& scc : sccs) {
        if (scc.empty()) continue;
        if (scc.size() < 2) {
            continue;
        }
        // Print each SCC
        std::cout << "SCC size: " << scc.size() << " - ";
        std::cout << "SCC: ";
        for (const auto& user : scc) {
            std::cout << user << " ";
        }
        std::cout << std::endl;
    }

    // Initialize the ranking system
    Ranking ranking(userGraph.FollowingList, userGraph.FollowersList);
    // Get top N influencers and followers
    std::vector<std::string> topInfluencers = ranking.getTopNInfluencers(N);
    std::vector<std::string> topFollowers = ranking.getTopNFollowers(N);
    std::cout << "Top " << N << " influencers: ";
    for (const auto& influencer : topInfluencers) {
        std::cout << influencer << " ";
    }
    std::cout << std::endl;
    std::cout << "Top " << N << " followers: ";
    for (const auto& follower : topFollowers) {
        std::cout << follower << " ";
    }
    std::cout << std::endl;

    std::cout << "Analyzing followees for newspapers: ";
    std::string newspaper;
    std::string tendency;
    for (const auto& [newspaper, tendency] : politicalTendency) {
        std::cout << newspaper << " (" << tendency << "), ";
    }
    std::cout << std::endl;

    
    // Initialize the political analyzer
    //PoliticalAnalyzer politicalAnalyzer(userGraph);
    
    // Analyze political tendencies
    //politicalAnalyzer.assignPoliticalTendency();
    
    // Report influential users
    //politicalAnalyzer.reportInfluentialUsers();
    
    std::cout << "Analysis complete." << std::endl;
    return 0;
}