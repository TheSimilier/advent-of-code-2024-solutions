#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <unordered_map>

void clearMark(std::vector<std::vector<std::pair<int, bool>>>& topologyMap) {
    for (int i = 0; i < topologyMap.size(); i++) {
        for (int j = 0; j < topologyMap[0].size(); j++) {
            topologyMap[i][j].second = false;
        }
    }
}

int traverse(std::vector<std::vector<std::pair<int, bool>>>& topologyMap, uint16_t xCoord, uint16_t yCoord, int16_t preValue) {
    if (xCoord < 0 || xCoord >= topologyMap[0].size() || yCoord < 0 || yCoord >= topologyMap.size()) return 0;
    const auto first = topologyMap[yCoord][xCoord].first;
    const auto second = topologyMap[yCoord][xCoord].second;
    if (first <= preValue || first > preValue + 1) return 0;
    if (second == true) return 0;
    topologyMap[yCoord][xCoord].second = true;

    if (first == 9) return 1;
    int sum = 0;
    sum += traverse(topologyMap, xCoord, yCoord + 1, first);
    sum += traverse(topologyMap, xCoord, yCoord - 1, first);
    sum += traverse(topologyMap, xCoord + 1, yCoord, first);
    sum += traverse(topologyMap, xCoord - 1, yCoord, first);
    return sum;
}

int traverse2(std::vector<std::vector<std::pair<int, bool>>>& topologyMap, uint16_t xCoord, uint16_t yCoord, int16_t preValue) {
    if (xCoord < 0 || xCoord >= topologyMap[0].size() || yCoord < 0 || yCoord >= topologyMap.size()) return 0;
    const auto first = topologyMap[yCoord][xCoord].first;
    const auto second = topologyMap[yCoord][xCoord].second;
    if (first <= preValue || first > preValue + 1) return 0;

    if (first == 9) return 1;
    int sum = 0;
    sum += traverse2(topologyMap, xCoord, yCoord + 1, first);
    sum += traverse2(topologyMap, xCoord, yCoord - 1, first);
    sum += traverse2(topologyMap, xCoord + 1, yCoord, first);
    sum += traverse2(topologyMap, xCoord - 1, yCoord, first);
    return sum;
}

int main()
{
    std::vector<std::vector<std::pair<int, bool>>> topologyMap;
    std::vector<std::pair<uint16_t, uint16_t>> zeroPos;

    std::string line;
    std::ifstream fileIn;

    fileIn.open("./input.txt");
    uint16_t yCoord = 0;
    while (std::getline(fileIn, line)) {
        uint16_t xCoord = 0;
        topologyMap.push_back({});
        for (char currChar : line) {
            auto charValue = currChar - '0';
            topologyMap[yCoord].push_back(std::make_pair(charValue, false));
            if (charValue == 0) zeroPos.push_back(std::make_pair(xCoord, yCoord));
            ++xCoord;
        }
        ++yCoord;
    }
    fileIn.close();

    int sum = 0;

    for (auto& pair : zeroPos) {
        sum += traverse2(topologyMap, pair.first, pair.second, -1);
        clearMark(topologyMap);
    }

    
    std::printf("sum: %i\n", sum);
}

