#include <iostream>
#include <fstream>
#include <regex>
#include <functional>

std::ofstream out("../data.out");
    
int string_to_number(const std::string& str) {

    int nr = 0;
    
    for (auto& chr : str) {
        nr = nr * 10 + chr - '0';
    }
    
    return nr;
}

void solve_first(const std::string& text) {

    std::regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
    
    unsigned long long rez = 0;
    
    for (std::sregex_iterator it(text.begin(), text.end(), pattern), end; it != end; ++it) {
        
        int a = string_to_number((*it)[1].str());
        int b = string_to_number((*it)[2].str());
        
        rez = rez + (unsigned long long) (a) * b;
        
    }
    
    out << "First: " << rez << std::endl;
}


void solve_second(const std::string& text) {

    std::regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\)|do\(\)|don't\(\))");
    
    unsigned long long rez = 0;
    
    bool enabled = true;
    
    for (std::sregex_iterator it(text.begin(), text.end(), pattern), end; it != end; ++it) {
        
        std::cout << "Match: " << it->str() << std::endl;
        
        std::string match = it->str();
        
        if (match == "do()") {
            enabled = true;
        }
        else if (match == "don't()") {
            enabled = false;
        }
        else if (enabled) {
            int a = string_to_number((*it)[1].str());
            int b = string_to_number((*it)[2].str());
            
            rez = rez + (unsigned long long) (a) * b;
        }
    }
    
    out << "Second: " << rez;
}

int main() {

    std::ifstream in("../data.in");
    if (!in.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return 1;
    }
    
    std::ostringstream buffer; 
    buffer << in.rdbuf();

    std::string text = buffer.str();
    
    solve_first(text);
    
    solve_second(text);
    
}