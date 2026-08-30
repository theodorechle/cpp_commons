#include <iostream>
#include <list>
#include <string>

namespace commons {
    constexpr size_t MIN_SPACE_BETWEEN_DIFF_LINES = 2;

    std::list<std::string> textToLines(const std::string &text);

    size_t longestLineSize(const std::list<std::string> &lines);

    void showDiff(const std::string &firstText, const std::string &secondText, const std::string &firstTitle, const std::string &secondTitle,
                  std::ostream &flow = std::clog);
}
