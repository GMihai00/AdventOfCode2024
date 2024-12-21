#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>

#include "models/Map.hpp"

std::vector<std::string> read_data(std::ifstream& in) {

    std::string line;
    std::vector<std::string> rez;
    while(std::getline(in, line)) {
        rez.push_back(line);
    }
    
    return rez;
}

void solve_first(std::shared_ptr<Map> map, std::ofstream& out, bool display = false) {

    auto rez = map->get_number_antinodes_first(display);
    
    out << "First: " << rez << std::endl;
    
    if (display)
        out << *map;
}

void solve_second(std::shared_ptr<Map> map, std::ofstream& out) {
    auto rez = map->get_number_antinodes_second();
    
    out << "Second: " << rez << std::endl;
    
    out << *map;
}

int main() {
    
    std::ifstream in("../data.in");
    
    if (!in.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return 1;
    }
    
    std::ofstream out("../data.out");
    
    auto data = read_data(in);
    
    auto map = std::make_shared<Map>(data);
    
    solve_first(map, out);
    
    solve_second(map, out);
    
    return 0;
}