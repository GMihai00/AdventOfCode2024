#include <iostream>
#include <fstream>
#include <memory>
#include "models/StoneLine.hpp"

void solve_first(std::shared_ptr<StoneLine> stone_line, std::ofstream& out) {

    auto rez = stone_line->solve_first();
    
    out << "First: " << rez << std::endl;
}

void solve_second(std::shared_ptr<StoneLine> stone_line, std::ofstream& out) {

    auto rez = stone_line->solve_second();
    
    out << "Second: " << rez;
}

int main() {
    
    std::ifstream in("../data.in");
    
    if (!in.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return 1;
    }
    
    std::ofstream out("../data.out");
    
    std::string line;
    
    if(!std::getline(in, line)){
    
        std::cerr << "Invalid input data";
        return 1;
    }
    
    auto stone_line = std::make_shared<StoneLine>(line);
    
    solve_first(stone_line, out);
    
    solve_second(stone_line, out);
}