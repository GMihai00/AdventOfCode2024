#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>

#include "models/ClawGame.hpp"

std::vector<std::string> read_data(std::ifstream& in) {
    
    std::vector<std::string> rez;
    std::string line;
    while (std::getline(in, line)) {
        rez.push_back(line);
    }
    
    return rez;
}

std::vector<std::shared_ptr<ClawGame>> build_game_data(const std::vector<std::string>& data) {
    
    std::vector<std::shared_ptr<ClawGame>> rez;
    
    for (int i = 0; i < data.size(); i+=4) {
        rez.push_back(std::make_shared<ClawGame>(data[i], data[i + 1], data[i + 2]));
    }
    
    return rez;
}

void solve_first(const std::vector<std::shared_ptr<ClawGame>>& game_data,  std::ofstream& out) {

    long long rez = 0;
    
    for (const auto& game : game_data) {
        
        if (auto val = game->brute_force_best_combination(); val != std::nullopt) {
            rez += *val;
        }
        
    }
    
    out << "First: " << rez << std::endl;
}

void solve_second(const std::vector<std::shared_ptr<ClawGame>>& game_data,  std::ofstream& out) {

    long long rez = 0;
    
    for (const auto& game : game_data) {
        
        if (auto val = game->get_best_combination(); val != std::nullopt) {
            rez += *val;
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
    
    std::ofstream out("../data.out");
    
    auto data = read_data(in);
    
    auto game_data = build_game_data(data);
    
    solve_first(game_data, out);
    
    solve_second(game_data, out);
}