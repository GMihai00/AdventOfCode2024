#include <iostream>
#include <fstream>
#include <memory>
#include "models/Equation.hpp"

std::vector<std::shared_ptr<Equation>> read_data(std::ifstream& in) {
    
    std::string line;
    
    std::vector<std::shared_ptr<Equation>> rez;
    
    while(std::getline(in, line)) {
        rez.push_back(std::make_shared<Equation>(line));
    }
    
    return rez;
}


void solve_first(const std::vector<std::shared_ptr<Equation>>& equations,  std::ofstream& out) {
    
    long long rez = 0;
    for (const auto& equation : equations) {
        if (equation->can_become_valid())
            rez += equation->get_result();
    }
    
    out << "First: " << rez << std::endl;
}

void solve_second(const std::vector<std::shared_ptr<Equation>>& equations,  std::ofstream& out) {
    
    long long rez = 0;
    for (const auto& equation : equations) {
        if (equation->can_become_valid_second())
            rez += equation->get_result();
    }
    
    out << "Second: " << rez << std::endl;
}

int main() {

    std::ifstream in("../data.in");
    
    if (!in.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return 1;
    }
    
    std::ofstream out("../data.out");
    
    auto equations = read_data(in);
    
    solve_first(equations, out);
    
    solve_second(equations, out);
}