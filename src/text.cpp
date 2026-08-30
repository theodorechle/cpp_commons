#include "text.hpp"

namespace commons {
    std::list<std::string> textToLines(const std::string &text) {
        std::list<std::string> lines = {};
        size_t lineStartIndex = 0;
        for (size_t index = 0; index < text.size(); index++) {
            if (text[index] == '\n') {
                lines.push_back(text.substr(lineStartIndex, index - lineStartIndex));
                lineStartIndex = index + 1;
            }
        }
        return lines;
    }

    size_t longestLineSize(const std::list<std::string> &lines) {
        size_t longestSize = 0;
        for (const std::string &line : lines) {
            if (line.size() > longestSize) longestSize = line.size();
        }
        return longestSize;
    }

    void showDiff(const std::string &firstText, const std::string &secondText, std::ostream &flow) {
        std::list<std::string> firstNodeLines = textToLines(firstText);
        std::list<std::string> secondNodeLines = textToLines(secondText);

        size_t longestLineSizeFirstString = longestLineSize(firstNodeLines);

        std::list<std::string>::const_iterator firstNodeLinesIt = firstNodeLines.cbegin();
        std::list<std::string>::const_iterator secondNodeLinesIt = secondNodeLines.cbegin();

        while (firstNodeLinesIt != firstNodeLines.cend() && secondNodeLinesIt != secondNodeLines.cend()) {
            std::string line = *firstNodeLinesIt;
            line += std::string(longestLineSizeFirstString - firstNodeLinesIt->size() + MIN_SPACE_BETWEEN_DIFF_LINES, ' ');
            line += *secondNodeLinesIt;
            flow << line << "\n";
            firstNodeLinesIt++;
            secondNodeLinesIt++;
        }
        while (firstNodeLinesIt != firstNodeLines.cend()) {
            flow << *firstNodeLinesIt << "\n";
            firstNodeLinesIt++;
        }
        while (secondNodeLinesIt != secondNodeLines.cend()) {
            flow << std::string(longestLineSizeFirstString + MIN_SPACE_BETWEEN_DIFF_LINES, ' ') << *secondNodeLinesIt << "\n";
            secondNodeLinesIt++;
        }
    }
}
