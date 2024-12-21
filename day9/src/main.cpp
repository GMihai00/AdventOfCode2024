#include <iostream>
#include <fstream>
#include "models/Memory.hpp"
#include <memory>

void solve_first(std::shared_ptr<Memory> memory, std::ofstream& out) {

    auto rez = memory->get_checksum_first();
    
    out << "First: " << rez << std::endl;
}

void solve_second(std::shared_ptr<Memory> memory, std::ofstream& out) {

    auto rez = memory->get_checksum_first();
    
    out << "Second: " << rez;
}

int main() {
    
    std::ifstream in("../data.in");
    
    if (!in.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return 1;
    }
    
    std::ofstream out("../data.out");

    std::string data;
    
    if (!std::getline(in, data)) {
        std::cerr << "Invalid input" << std::endl;
        return 1;
    }
    
    auto memory = std::make_shared<Memory>(data);
    
    solve_first(memory, out);
    
}