#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

void puzzle1(std::vector<std::vector<char>>& charMap, std::vector<std::tuple<uint16_t, uint16_t>>& centerPositions) {
    uint16_t xmasCount = 0;
    for (auto& currX : centerPositions) {
        auto xCoord = std::get<0>(currX);
        auto yCoord = std::get<1>(currX);

        if (yCoord >= 3) {
            xmasCount += charMap[yCoord - 1][xCoord] == 'M' && charMap[yCoord - 2][xCoord] == 'A' && charMap[yCoord - 3][xCoord] == 'S';
            if (xCoord >= 3) xmasCount += charMap[yCoord - 1][xCoord - 1] == 'M' && charMap[yCoord - 2][xCoord - 2] == 'A' && charMap[yCoord - 3][xCoord - 3] == 'S';
            if (xCoord < charMap[yCoord].size() - 3) xmasCount += charMap[yCoord - 1][xCoord + 1] == 'M' && charMap[yCoord - 2][xCoord + 2] == 'A' && charMap[yCoord - 3][xCoord + 3] == 'S';
        }
        if (yCoord < charMap.size() - 3) {
            xmasCount += charMap[yCoord + 1][xCoord] == 'M' && charMap[yCoord + 2][xCoord] == 'A' && charMap[yCoord + 3][xCoord] == 'S';
            if (xCoord >= 3) xmasCount += charMap[yCoord + 1][xCoord - 1] == 'M' && charMap[yCoord + 2][xCoord - 2] == 'A' && charMap[yCoord + 3][xCoord - 3] == 'S';
            if (xCoord < charMap[yCoord].size() - 3) xmasCount += charMap[yCoord + 1][xCoord + 1] == 'M' && charMap[yCoord + 2][xCoord + 2] == 'A' && charMap[yCoord + 3][xCoord + 3] == 'S';
        }
        if (xCoord >= 3) xmasCount += charMap[yCoord][xCoord - 1] == 'M' && charMap[yCoord][xCoord - 2] == 'A' && charMap[yCoord][xCoord - 3] == 'S';
        if (xCoord < charMap[yCoord].size() - 3) xmasCount += charMap[yCoord][xCoord + 1] == 'M' && charMap[yCoord][xCoord + 2] == 'A' && charMap[yCoord][xCoord + 3] == 'S';
    }

    std::printf("%i\n", xmasCount);
}

void puzzle2(std::vector<std::vector<char>>& charMap, std::vector<std::tuple<uint16_t, uint16_t>>& centerPositions) {
    uint16_t crossedMasCount = 0;
    for (auto& currA : centerPositions) {
        auto xCoord = std::get<0>(currA);
        auto yCoord = std::get<1>(currA);

        if (
            (yCoord >= 1 && yCoord < charMap.size() - 1 && xCoord >= 1 && xCoord < charMap[yCoord].size() - 1)
                && (charMap[yCoord - 1][xCoord - 1] == 'M' && charMap[yCoord - 1][xCoord + 1] == 'M' && charMap[yCoord + 1][xCoord - 1] == 'S' && charMap[yCoord + 1][xCoord + 1] == 'S')
                || (charMap[yCoord + 1][xCoord - 1] == 'M' && charMap[yCoord + 1][xCoord + 1] == 'M' && charMap[yCoord - 1][xCoord - 1] == 'S' && charMap[yCoord - 1][xCoord + 1] == 'S')
                || (charMap[yCoord - 1][xCoord - 1] == 'M' && charMap[yCoord + 1][xCoord - 1] == 'M' && charMap[yCoord - 1][xCoord + 1] == 'S' && charMap[yCoord + 1][xCoord + 1] == 'S')
                || (charMap[yCoord - 1][xCoord + 1] == 'M' && charMap[yCoord + 1][xCoord + 1] == 'M' && charMap[yCoord - 1][xCoord - 1] == 'S' && charMap[yCoord + 1][xCoord - 1] == 'S')
                ) {
            ++crossedMasCount;
        }
    }

    std::printf("%i\n", crossedMasCount);
}

int main()
{
    std::vector<std::vector<char>> charMap;
    std::vector<std::tuple<uint16_t, uint16_t>> centerXPositions;
    std::vector<std::tuple<uint16_t, uint16_t>> centerAPositions;

    std::string line;
    std::ifstream fileIn;
    uint16_t lineIndex = 0;

    fileIn.open("./input.txt");
    while (std::getline(fileIn, line)) {
        uint16_t columnIndex = 0;
        std::vector<char> row;
        for (const char currChar : line) {
            row.push_back(currChar);
            if (currChar == 'X') {
                centerXPositions.push_back(std::make_tuple(columnIndex, lineIndex));
            }
            if (currChar == 'A') {
                centerAPositions.push_back(std::make_tuple(columnIndex, lineIndex));
            }
            ++columnIndex;
        }
        charMap.push_back(row);
        ++lineIndex;
    }
	fileIn.close();
    puzzle1(charMap, centerXPositions);
    puzzle2(charMap, centerAPositions);
}
