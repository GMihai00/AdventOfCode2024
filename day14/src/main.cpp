
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <optional>
#include <map>

#include "models/Robot.hpp"

std::vector<std::string> read_data(std::ifstream& in) {
    
    std::vector<std::string> rez;
    std::string line;
    
    while(std::getline(in, line)){
        rez.push_back(line);
    }
    
    return rez;
}

std::vector<std::shared_ptr<Robot>> build_robots(const std::vector<std::string>& data) {
    std::vector<std::shared_ptr<Robot>>  rez;
    
    for (const auto& line : data) {
    
        rez.push_back(std::make_shared<Robot>(line));
    }
    
    return rez;
}

constexpr int waiting_time = 100;

std::optional<short> get_quadrant(const std::pair<int, int> pos) {
    
    std::pair<int, int> center = {GRID_HEIGHT  / 2, GRID_WIDTH / 2};
    // ignore mid positions
    if (pos.first == center.first || pos.second == center.second)
        return std::nullopt;
        
    
    if (pos.second > center.second) {
        // I / IV
        if (pos.first < center.first) {
            return 1;
        } else {
            return 4;
        }
    
    } else {
        // II / III
        if (pos.first < center.first) {
            return 2;
        } else {
            return 3;
        }
    }
    
}

void solve_first(const std::vector<std::shared_ptr<Robot>>& robots, std::ofstream& out, bool display_map = false) {

    long long rez = 1;
    
    std::map<short, long long> quadrant_robot_count;
    
    std::vector<std::vector<int>> final_map(GRID_HEIGHT, std::vector<int>(GRID_WIDTH, 0));
    
    for (const auto& robot : robots) {
        
        auto next_pos = robot->get_next_position(waiting_time);
        
        final_map[next_pos.first][next_pos.second]++;
        
        if (auto quadrant = get_quadrant(next_pos); quadrant != std::nullopt) {
            quadrant_robot_count[*quadrant]++;
        }
    }
    
    for (int i = 1; i <= 4; i++) {
        rez *= quadrant_robot_count[i];
    }
    
    out << "First: " << rez << std::endl;
    
    if (display_map) {
        for (int i = 0; i < GRID_HEIGHT; i++) {
            for (int j = 0; j < GRID_WIDTH; j++)
            {
                if (i == GRID_HEIGHT / 2 || j == GRID_WIDTH / 2)
                    out << " ";
                else
                    out << final_map[i][j];
            }
                
            out << std::endl;
        }
    }
}

bool can_apply_kernel( const std::vector<std::vector<int>>& final_map, const std::pair<int, int> size = {5, 5}) {

    for (int i = 0; i < final_map.size() - size.first; i++)
    {
        for (int j = 0; j < final_map[i].size() - size.second; j++) {
            bool ok = true;
            
            for (int p = 0; p < 5; p++) {
                for (int f = 0; f < 5; f++) {
                    if (final_map[i + p][j + f] == 0) {
                        ok = false;
                        p = 5;
                        f = 5;
                    }
                }
            }
            
            if (ok == true)
                return true;
            
        }
    }
    
    return false;
}


void solve_second(const std::vector<std::shared_ptr<Robot>>& robots, std::ofstream& out) {

    long long rez = 0;    
    bool tree_found = false;
    
    std::vector<std::vector<int>> final_map;
    
    while(!tree_found) {
        
        final_map = std::vector<std::vector<int>>(GRID_HEIGHT, std::vector<int>(GRID_WIDTH, 0));
        
        for (const auto& robot : robots) {
            
            auto next_pos = robot->get_next_position(rez);
            
            final_map[next_pos.first][next_pos.second]++;
        
        }
        
        if (can_apply_kernel(final_map)) {
            tree_found = true;
        }
        else {
            rez++;
        }
    }
    
    out << "Second: " << rez << std::endl;
    
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++)
        {
            if (i == GRID_HEIGHT / 2 || j == GRID_WIDTH / 2)
                out << " ";
            else
                out << final_map[i][j];
        }
            
        out << std::endl;
    }
}

int main() {
    
    std::ifstream in("../data.in");
    
    if (!in.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return 1;
    }
    
    std::ofstream out("../data.out");
    
    auto data = read_data(in);
    
    auto robots = build_robots(data);
    
    solve_first(robots, out);
    
    solve_second(robots, out);
}