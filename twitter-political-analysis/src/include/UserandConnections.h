#ifndef USERANDCONNECTIONS_H
#define USERANDCONNECTIONS_H
#include <string>

struct User {
    std::string user_id;
    std::string user_name;
    std::string number_tweets;
    std::string friends_count;
    std::string followers_count;
    std::string created_at;
};

struct Connection {
    std::string followee;
    std::string follower;
}; 

#endif // USERANDCONNECTIONS_H