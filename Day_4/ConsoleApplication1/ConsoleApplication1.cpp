// ConsoleApplication1.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

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
    puzzle1(charMap, centerXPositions);
    puzzle2(charMap, centerAPositions);
}

// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
