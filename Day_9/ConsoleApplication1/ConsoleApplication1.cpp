#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>

void puzzle1(std::deque<std::pair<int16_t, int>>& usedSpots, std::deque<std::pair<int16_t, int>>& freeSpots, std::vector<int16_t>& out) {
    bool nextSpotIsUsedSpot = true;
    while (usedSpots.size() > 0) {
        if (nextSpotIsUsedSpot) {
            auto currentSpot = usedSpots.front();
            usedSpots.pop_front();
            
            if (currentSpot.first == -1) {
                nextSpotIsUsedSpot = false;
                continue;
            }

            while (currentSpot.second > 0) {
                out.push_back(currentSpot.first);
                --currentSpot.second;
            }
            nextSpotIsUsedSpot = false;
        }
        else {
            auto freeSpot = freeSpots.front();
            freeSpots.pop_front();

            while (freeSpot.second > 0) {
                auto currentNum = usedSpots.back();
                usedSpots.pop_back();

                auto delta = freeSpot.second - currentNum.second;

                if (delta > 0) {
                    freeSpot.second -= currentNum.second;
                    while (currentNum.second > 0) {
                        out.push_back(currentNum.first);
                        --currentNum.second;
                    }
                }
                else if (delta < 0) {
                    currentNum.second -= freeSpot.second;
                    while (freeSpot.second > 0) {
                        out.push_back(currentNum.first);
                        --freeSpot.second;
                    }
                    usedSpots.push_back(currentNum);
                }
                else {
                    freeSpot.second = 0;
                    while (currentNum.second > 0) {
                        out.push_back(currentNum.first);
                        --currentNum.second;
                    }
                }
            }
            nextSpotIsUsedSpot = true;
        }
    }
}

void puzzle2(std::deque<std::pair<int16_t, int>>& usedSpots, std::deque<std::pair<int16_t, int>>& freeSpots, std::vector<int16_t>& out) {
    bool nextSpotIsUsedSpot = true;
    while (usedSpots.size() > 0) {
        if (nextSpotIsUsedSpot) {
            auto currentSpot = usedSpots.front();
            usedSpots.pop_front();

            while (currentSpot.second > 0) {
                out.push_back(currentSpot.first);
                --currentSpot.second;
            }
            nextSpotIsUsedSpot = false;
        }
        else {
            auto freeSpot = freeSpots.front();
            freeSpots.pop_front();

            while (freeSpot.second > 0) {
                int firstFittingIndex = usedSpots.size() - 1;
                for (firstFittingIndex; firstFittingIndex >= 0; firstFittingIndex--) {
                    auto pair = usedSpots[firstFittingIndex];
                    if (pair.first != -1 && pair.second <= freeSpot.second) break;
                }
                if (firstFittingIndex < 0) {
                    while (freeSpot.second > 0) {
                        out.push_back(-1);
                        --freeSpot.second;
                    }
                    break;
                }
                auto currentNum = usedSpots[firstFittingIndex];
                usedSpots[firstFittingIndex].first = -1;

                if (freeSpot.second - currentNum.second > 0) {
                    freeSpot.second -= currentNum.second;
                    while (currentNum.second > 0) {
                        out.push_back(currentNum.first);
                        --currentNum.second;
                    }
                }
                else {
                    freeSpot.second = 0;
                    while (currentNum.second > 0) {
                        out.push_back(currentNum.first);
                        --currentNum.second;
                    }
                }
            }
            nextSpotIsUsedSpot = true;
        }
    }
}

int main()
{
    std::deque<std::pair<int16_t, int>> usedSpots;
    std::deque<std::pair<int16_t, int>> freeSpots;

    std::string line;
    std::ifstream fileIn;

    fileIn.open("./input.txt");
    while (std::getline(fileIn, line)) {
        uint16_t index = 0;
        int16_t charValue = 0;
        for (char currChar : line) {
            int amount = currChar - '0';
            if (index % 2 == 0) {
                usedSpots.push_back(std::make_pair(charValue, amount));
                ++charValue;
            } else {
                freeSpots.push_back(std::make_pair(-1, amount));
            }
            ++index;
        }
    }
    fileIn.close();

    std::vector<int16_t> sortedVector;
    //puzzle1(usedSpots, freeSpots, sortedVector);
    puzzle2(usedSpots, freeSpots, sortedVector);

    long long checkSum = 0;
    for (int i = 0; i < sortedVector.size(); i++) {
        auto num = sortedVector[i];
        if (num == -1) continue;
        checkSum += i * num;
    }
    
    std::printf("checkSum: %llu\n", checkSum);
}

