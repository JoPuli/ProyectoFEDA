#include "UserGraph.h"

UserGraph::UserGraph() {}

void UserGraph::addUser(const std::string& username) {
    FollowersList[username];  // Ensure entry exists
    FollowingList[username];
}

void UserGraph::addConnection(const std::string& follower, const std::string& followee) {
    addUser(follower);
    addUser(followee);
    FollowingList[follower].insert(followee);
    FollowersList[followee].insert(follower);
    updateUserStats(follower);
    updateUserStats(followee);
}

std::unordered_set<std::string> UserGraph::getFollowers(const std::string& username) const {
    auto it = FollowersList.find(username);
    if (it != FollowersList.end()) {
        return it->second;
    }
    return {};
}

std::unordered_set<std::string> UserGraph::getFollowing(const std::string& username) const {
    auto it = FollowingList.find(username);
    if (it != FollowingList.end()) {
        return it->second;
    }
    return {};
}

void UserGraph::updateUserStats(const std::string& username) {
    n_followers = FollowersList[username].size();
    n_following = FollowingList[username].size();
}