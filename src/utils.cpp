#include <vector>
#include <string>

std::vector<std::string> split(std::string text, const std::string delimiter) {
    std::vector<std::string> result;

    int lhs = 0, rhs = 0;
    for (; rhs < text.size() && rhs + delimiter.size() < text.size(); rhs++) {
        bool is_equal = true;
        for (int i = 0; i < delimiter.size(); i++, rhs++) {
            if (text[rhs] != delimiter[i]) {
                is_equal = false;
                break;
            }
        }

        if (is_equal) {
            if (rhs - lhs > 1) {
                result.push_back(text.substr(lhs, rhs - lhs - delimiter.size()));
            }
            lhs = rhs;
        }
    }
    
    // Since in above for we have rhs + delimiter.size() < text.size();
    // there are cases when our rhs will not reach the end of the string
    //
    // Example:
    // text = "Authorization: Bearer 123"
    // delimiter = ": "
    //
    // Output:
    // {"Authorization", "Bearer 1"}
    //
    // Since ": " is 2 characters long, we don't have 2 last characters of our text
    rhs = text.size();

    if (rhs - lhs > 1) {
        result.push_back(text.substr(lhs, rhs - lhs));
    }

    return result;
}

bool is_empty(const std::string text) {
    for (const char c: text) {
        if (int(c) > 32) {
            return false;
        }
    }

    return true;
}
