#include <iostream>
#include <fstream>
#include <sstream>
#include <regex>

bool isNumber(const std::string& s) {
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

int main() {
    std::string input;
    std::cout << "Enter the expression: ";
    std::getline(std::cin, input);

    std::regex e ("<ABRIR> (.*) <CERRAR>");
    std::smatch match;

    if (std::regex_search(input, match, e) && match.size() > 1) {
        std::string expression = match.str(1);
        std::regex e2 ("([a-zA-Z]+)([0-9]+)([<>=!]+)([0-9]+)");
        std::smatch match2;

        if (std::regex_search(expression, match2, e2) && match2.size() > 4) {
            std::ofstream file("output.txt");
            file << "Variable: " << match2[1] << "\n";
            file << "Number: " << match2[2] << "\n";
            file << "Operator: " << match2[3] << "\n";
            file << "Number: " << match2[4] << "\n";
            std::cout << "Valid\n";
        } else {
            std::cout << "Invalid\n";
        }
    } else {
        std::cout << "Invalid\n";
    }

    return 0;
}