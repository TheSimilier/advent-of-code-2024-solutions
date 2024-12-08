#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>
#include <unordered_map>
#include <deque>

struct Point {
    uint16_t x;
    uint16_t y;

    bool operator==(Point p) const {
        return (p.x == x && p.y == y);
    }
};

struct Direction {
    int16_t x;
    int16_t y;

    bool operator==(Direction d) const {
        return (d.x == x && d.y == y);
    }
};

template <>
struct std::hash<Point> {
    std::size_t operator()(Point const& s) const {
        return ((std::hash<uint16_t>()(s.x)
            ^ (std::hash<uint16_t>()(s.y) << 1)) >> 1);
    }
};

template<>
struct std::hash<Direction> {
    std::size_t operator()(Direction const& s) const {
        return ((std::hash<uint16_t>()(s.x)
            ^ (std::hash<uint16_t>()(s.y) << 1)) >> 1);
    }
};

int main()
{
    std::unordered_map<char, std::vector<Point>> frequencyLocations;
    size_t width;
    size_t height;


    std::string line;
    std::ifstream fileIn;
    uint16_t lineIndex = 1;

    fileIn.open("./input.txt");
    while (std::getline(fileIn, line)) {
        uint16_t columnIndex = 1;
        std::vector<char> row;
        for (char currChar : line) {
            if (currChar != '.') {
                if (frequencyLocations.find(currChar) != frequencyLocations.end()) {
                    frequencyLocations[currChar].push_back({ .x = columnIndex, .y = lineIndex });
                }
                else {
                    std::vector<Point> currFreq;
                    currFreq.push_back({ .x = columnIndex, .y = lineIndex });
                    frequencyLocations.emplace(currChar, currFreq);
                }
            }
            ++columnIndex;
        }
        width = columnIndex-1;
        ++lineIndex;
    }
    height = lineIndex-1;
    fileIn.close();
    
    uint16_t sumAntiNodes = 0;
    std::vector<Point> locationNodesFreq;

    for (auto currPair : frequencyLocations) {
        const auto& locations = currPair.second;

        if (locations.size() < 2) continue;
        for (auto i = 0; i <= locations.size() - 2; i++) {
            const auto& p1 = locations[i];

            if (std::find(locationNodesFreq.begin(), locationNodesFreq.end(), p1) == locationNodesFreq.end()) {
                locationNodesFreq.push_back(p1);
                ++sumAntiNodes;
            }

            for (auto j = i + 1; j <= locations.size() - 1; j++) {
                const auto& p2 = locations[j];
                const auto deltaX = p1.x - p2.x;
                const auto deltaY = p1.y - p2.y;

                if (std::find(locationNodesFreq.begin(), locationNodesFreq.end(), p2) == locationNodesFreq.end()) {
                    locationNodesFreq.push_back(p2);
                    ++sumAntiNodes;
                }
                auto runningDeltaX = deltaX;
                auto runningDeltaY = deltaY;
                while (std::abs(runningDeltaX) <= width && std::abs(runningDeltaY) <= height) {
					Point p3{
						.x = static_cast<uint16_t>(p1.x + runningDeltaX),
						.y = static_cast<uint16_t>(p1.y + runningDeltaY),
					};
					Point p4{
						.x = static_cast<uint16_t>(p2.x - runningDeltaX),
						.y = static_cast<uint16_t>(p2.y - runningDeltaY),
					};

					if (p3.x <= width && p3.x > 0 && p3.y <= height && p3.y > 0 && std::find(locationNodesFreq.begin(), locationNodesFreq.end(), p3) == locationNodesFreq.end()) {
						locationNodesFreq.push_back(p3);
						++sumAntiNodes;
					}
					if (p4.x <= width && p4.x > 0 && p4.y <= height && p4.y > 0 && std::find(locationNodesFreq.begin(), locationNodesFreq.end(), p4) == locationNodesFreq.end()) {
						locationNodesFreq.push_back(p4);
						++sumAntiNodes;
					}

                    runningDeltaX += deltaX;
                    runningDeltaY += deltaY;
                }
            }
        }
    }

    std::printf("antinode count: %i\n", sumAntiNodes);
}

