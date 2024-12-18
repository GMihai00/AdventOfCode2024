#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <memory>
#include "./models/Map.hpp"

std::vector<std::string> read_data(std::ifstream& in) {
    
    std::vector<std::string> rez;
    
    std::string line;
    
    while (std::getline(in , line)) {
    
        rez.push_back(line);
    }
    
    return rez;
}

long long solve_brute_force(const std::shared_ptr<Map> map) {

    std::vector<std::pair<int,int>> directions = {
        {-1, 0},
        {0, 1},
        {1, 0},
        {0, -1}
    };
    
    int current_direction = 0;
    
    auto current_position = map->m_guard_initial_position;
    
    int n = map->m_horizontal_view.size();
    int m = map->m_horizontal_view[0].size();  
    
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));
    
    while (current_position.first < n && 
        current_position.second < m && current_position.first >= 0 && current_position.second >= 0) {
    
        visited[current_position.first][current_position.second] = true;

        int i = current_position.first + directions[current_direction].first;
        int j = current_position.second + directions[current_direction].second;
        
        std::cout << i << " " << j << std::endl;
        
        std::pair<int, int> next = {i , j};

        if (!(next.first < n && next.second < m && i >= 0 && j >= 0)) {
            break;
        }
        
        if (map->m_horizontal_view[i][j] != '#') {
            current_position = next;
        } 
        else {
            current_direction++;
            if (current_direction == directions.size())
                current_direction = 0;
        }
        
        
    }
    
    long long rez = 0;
    
    for (int i = 0; i < visited.size(); i++)
    {
        for (int j = 0; j < visited[i].size(); j++)
        {
            if (visited[i][j] == true) 
            {   
                rez++;
                map->m_horizontal_view[i][j] = 'X';
            }
        }
    }
    
    return rez;
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
    
    auto rez=  solve_brute_force(map);
    
    out << "First: " << rez << std::endl;
    
    out << *map;
}