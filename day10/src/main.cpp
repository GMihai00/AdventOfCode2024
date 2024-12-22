#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include "models/TrailMap.hpp"

std::vector<std::string> read_data(std::ifstream& in) {

    std::vector<std::string> rez;
    
    std::string line;
    
    while(std::getline(in, line)) {
    
        rez.push_back(line);
    }
    
    return rez;
} 

void solve_first(std::shared_ptr<TrailMap> map, std::ofstream& out) {
    
    auto rez = map->get_total_trail_score();
    
    out << "First: " << rez << std::endl;
}

void solve_second(std::shared_ptr<TrailMap> map, std::ofstream& out) {
    
    auto rez = map->get_total_trail_rating();
    
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
    
    auto map = std::make_shared<TrailMap>(data);
    
    solve_first(map, out);
    
    solve_second(map, out);
}