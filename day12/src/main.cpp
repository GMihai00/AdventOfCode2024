#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include "models/Garden.hpp"

std::vector<std::string> read_data(std::ifstream& in) {
    
    std::vector<std::string> rez;
    
    std::string line;
    while(std::getline(in, line)) {
        rez.push_back(line);
    }
    
    return rez;
}

void solve_first(std::shared_ptr<Garden> garden, std::ofstream& out) {
    
    auto rez = garden->get_total_fence_price();
    
    out << "First: " << rez << std::endl;
}

void solve_second(std::shared_ptr<Garden> garden, std::ofstream& out) {
    
    auto rez = garden->get_total_fence_discounted_price();
    
    out << "Second: " << rez;
}

int main() {
    
    std::ifstream in("../data.in");
    
    if (!in.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return 1;
    }
    
    std::ofstream out("../data.out");
    
    auto data = read_data(in);
    
    auto garden = std::make_shared<Garden>(data);
    
    solve_first(garden, out);
    
    solve_second(garden, out);
}