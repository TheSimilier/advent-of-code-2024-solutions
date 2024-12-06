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

bool testBlockForLoop(const std::vector<std::vector<char>>& charMap, std::unordered_map<Point, Direction>& walkedRoute, std::deque<Point>& remainingBlocker,
    const Point& startPosition, const Point& block) {
	Direction currentDirection{};
	currentDirection.x = 0;
	currentDirection.y = -1;
	auto currentPosition = startPosition;
    bool trackingActive = false;
    uint16_t counterSinceLastMove = 0;
    std::unordered_map<Point, std::unordered_map<Direction, uint16_t>> pointToVisitCount;
	while (currentPosition.x < charMap[0].size() && currentPosition.x >= 0 && currentPosition.y < charMap.size() && currentPosition.y >= 0) {
            if (currentPosition.y + currentDirection.y >= charMap.size() || currentPosition.y + currentDirection.y < 0
                || currentPosition.x + currentDirection.x >= charMap[0].size() || currentPosition.x + currentDirection.x < 0) break;
		const Point nextPoint{
			.x = static_cast<uint16_t>(currentPosition.x + currentDirection.x),
			.y = static_cast<uint16_t>(currentPosition.y + currentDirection.y),
		};
		auto& nextChar = charMap[nextPoint.y][nextPoint.x];
        const bool hitBlocker = nextPoint.x == block.x && nextPoint.y == block.y;

		if (nextChar == '#' || hitBlocker) {
			auto prevX = currentDirection.x;
			currentDirection.x = -1*currentDirection.y;
			currentDirection.y = prevX;
            ++counterSinceLastMove;
            if (counterSinceLastMove > 5) return false;
			continue;
		}

		if (nextChar == '.') {
            counterSinceLastMove = 0;
			currentPosition.x += currentDirection.x;
			currentPosition.y += currentDirection.y;
		}

        if (pointToVisitCount.find(currentPosition) != pointToVisitCount.end()) {
            auto& map = pointToVisitCount[currentPosition];
            auto it = map.find(currentDirection);
            if (it != map.end()) {
                map[currentDirection]++;
                if (map[currentDirection] > 3) return true;
            }
            else {
                map.emplace(currentDirection, 1);
            }
        }
        else {
            std::unordered_map<Direction, uint16_t> directionToCount;
            directionToCount.emplace(currentDirection, 1);
            pointToVisitCount.emplace(currentPosition, directionToCount);
        }
	}
	return false;
}

int main()
{
    std::vector<std::vector<char>> charMap;
    Point startPosition{};
    std::unordered_map<Point, Direction> walkedSquareToWalkedDirection;
    std::deque<Point> stackOfRouteForBlocking;



    std::string line;
    std::ifstream fileIn;
    uint16_t lineIndex = 0;

    fileIn.open("./input.txt");
    while (std::getline(fileIn, line)) {
        uint16_t columnIndex = 0;
        std::vector<char> row;
        for (char currChar : line) {
            if (currChar == '^') {
                startPosition.x = columnIndex;
                startPosition.y = lineIndex;
                currChar = '.';
            }
            row.push_back(currChar);
            ++columnIndex;
        }
        charMap.push_back(row);
        ++lineIndex;
    }
    fileIn.close();

    uint16_t stepCount = 0;
    auto charMap2 = charMap;

    {
		Direction currentDirection{};
		currentDirection.x = 0;
		currentDirection.y = -1;
        auto currentPosition = startPosition;
		while (currentPosition.x < charMap[0].size() && currentPosition.x >= 0 && currentPosition.y < charMap.size() && currentPosition.y >= 0) {
            if (currentPosition.y + currentDirection.y >= charMap.size() || currentPosition.y + currentDirection.y < 0
                || currentPosition.x + currentDirection.x >= charMap[0].size() || currentPosition.x + currentDirection.x < 0) break;
			auto& nextChar = charMap[currentPosition.y + currentDirection.y][currentPosition.x + currentDirection.x];
			if (nextChar == '#') {
				auto prevX = currentDirection.x;
				currentDirection.x = -1*currentDirection.y;
				currentDirection.y = prevX;

				continue;
			}

			if (nextChar == '.' || nextChar == 'X') {
				if (nextChar != 'X') ++stepCount;
				nextChar = 'X';
				currentPosition.x += currentDirection.x;
				currentPosition.y += currentDirection.y;

                walkedSquareToWalkedDirection.emplace(currentPosition, currentDirection);
                if (currentPosition != startPosition)stackOfRouteForBlocking.push_back(currentPosition);
			}
		}
    }

    uint16_t loopCount = 0;
    std::unordered_map<Point, bool> pointToHitLoop;
    for (uint16_t x = std::size(charMap2[0]); x >= 1; x--) {
        for (uint16_t y = std::size(charMap); y >= 1; y--) {
            Point currBlocker{ .x = static_cast<uint16_t>(x-1), .y = static_cast<uint16_t>(y-1) };
            if (currBlocker == startPosition) continue;
            if (pointToHitLoop.contains(currBlocker)) continue;
            bool hitLoop = false;
            if (testBlockForLoop(charMap2, walkedSquareToWalkedDirection, stackOfRouteForBlocking, startPosition, currBlocker)) {
                hitLoop = true;
                ++loopCount;
            }
            pointToHitLoop.emplace(currBlocker, hitLoop);
        }
        std::printf("column %i done\n", x);
    }

    std::printf("loop count: %i\n", loopCount);
    std::printf("step count: %i\n", stepCount);
}

