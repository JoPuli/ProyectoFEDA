#ifndef POLITICALANALYZER_H
#define POLITICALANALYZER_H

#include <string>
#include <vector>
#include "UserGraph.h"

class PoliticalAnalyzer {
public:
    PoliticalAnalyzer(UserGraph& userGraph);
    void assignPoliticalTendency();
    std::vector<std::string> reportInfluentialUsers(int threshold);

private:
    UserGraph& userGraph;
    void analyzeUserTendency(const std::string& userId);
};

#endif // POLITICALANALYZER_H