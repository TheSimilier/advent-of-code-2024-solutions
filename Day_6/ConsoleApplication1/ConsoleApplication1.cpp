#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

struct Point {
    uint16_t x;
    uint16_t y;
};

struct Direction {
    int16_t x;
    int16_t y;
};

struct IncompleteRectangle {
    Point p1, p2, p3;
};

struct PotentialRectangleCandidate {
    Point p1;
    Direction walkingDir;
};

int main()
{
    std::vector<std::vector<char>> charMap;
    Point currentPosition{};



    std::string line;
    std::ifstream fileIn;
    uint16_t lineIndex = 0;

    fileIn.open("./input.txt");
    while (std::getline(fileIn, line)) {
        uint16_t columnIndex = 0;
        std::vector<char> row;
        for (char currChar : line) {
            if (currChar == '^') {
                currentPosition.x = columnIndex;
                currentPosition.y = lineIndex;
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
    std::vector<IncompleteRectangle> incompleteRectangles;
    std::vector<PotentialRectangleCandidate> potentialCandidates;

    {
		IncompleteRectangle startingRectangle{};
		startingRectangle.p1 = currentPosition;
		incompleteRectangles.push_back(startingRectangle);

		Direction currentDirection{};
		currentDirection.x = 0;
		currentDirection.y = -1;
        bool turned = false;
		while (currentPosition.x < charMap[0].size() - 1 && currentPosition.x > 0 && currentPosition.y < charMap.size() - 1 && currentPosition.y > 0) {
			auto& nextChar = charMap[currentPosition.y + currentDirection.y][currentPosition.x + currentDirection.x];
			if (nextChar == '#') {
				auto prevX = currentDirection.x;
				currentDirection.x = -1*currentDirection.y;
				currentDirection.y = prevX;

				//add current point to the last 3 incomplete rectangles
				for (int index = std::ssize(incompleteRectangles) - 1; index >= 0 && index >= std::ssize(incompleteRectangles) - 2; index--) {
					auto& rect = incompleteRectangles[index];
					if (rect.p2.x == 0) {
						rect.p2 = currentPosition;
						continue;
					}
					if (rect.p3.x == 0) {
						rect.p3 = currentPosition;
					}
				}
				IncompleteRectangle newRect{};
				newRect.p1 = currentPosition;
				incompleteRectangles.push_back(newRect);
                turned = true;
				continue;
			}

            auto leftChar = charMap[currentPosition.y + -1 * currentDirection.x][currentPosition.x + currentDirection.y];
            if (!turned && leftChar == '#') {
                potentialCandidates.push_back({
                    .p1 = currentPosition,
                    .walkingDir = currentDirection,
                    });
            }

			if (nextChar == '.' || nextChar == 'X') {
				if (nextChar != 'X') ++stepCount;
				nextChar = 'X';
				currentPosition.x += currentDirection.x;
				currentPosition.y += currentDirection.y;
                turned = false;
			}
		}
    }

    //iterate over incomplete rectangle list
    //see if 3 points create a valid axis-aligned rectangle
    //find 4th point
    //traverse along the 4 points in order with distance of circumference of the rectangle
    //if traversal leads back to 4th point a loop point is found
    //verify loop point doesnt break prior traversal?
    uint16_t loopCount = 0;
    for (const auto& rect : incompleteRectangles) {
        if (rect.p1.x == 0 || rect.p2.x == 0 || rect.p3.x == 0) continue;
        const auto& p1 = rect.p1;
        const auto& p2 = rect.p2;
        const auto& p3 = rect.p3;

        const Point p4{
            .x = static_cast<uint16_t>(p3.x - (p2.x - p1.x)),
            .y = static_cast<uint16_t>(p3.y - (p2.y - p1.y)),
        };

        Direction currentDirection{};
        const auto deltaX = p1.x - p4.x;
        const auto deltaY = p1.y - p4.y;
        currentDirection.x = deltaX > 0 ? 1 : deltaX < 0 ? -1 : 0;
        currentDirection.y = deltaY > 0 ? 1 : deltaY < 0 ? -1 : 0;

        const auto walkDistance = 2 * (std::abs(p1.x - p2.x) + std::abs(p1.y - p2.y)) + 2 * (std::abs(p2.x - p3.x) + std::abs(p2.y - p3.y));
        auto testPosition = p4;

        for (int i = walkDistance; i > 0; i--) {
			auto& nextChar = charMap[testPosition.y + currentDirection.y][testPosition.x + currentDirection.x];

            if (nextChar == '#') {
                auto prevX = currentDirection.x;
                currentDirection.x = -1 * currentDirection.y;
                currentDirection.y = prevX;
                continue;
            }

			if (nextChar == '.' || nextChar == 'X') {
				currentPosition.x += currentDirection.x;
				currentPosition.y += currentDirection.y;
			}
        }

        if (testPosition.x != p4.x && testPosition.y != p4.y) continue;

        ++loopCount;
    }

    std::printf("loop count: %i\n", loopCount);
    std::printf("step count: %i\n", stepCount +1);
}

