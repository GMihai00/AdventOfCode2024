#include "Map.hpp"
#include <iostream>


void Map::build_antenna_map()
{
    for (int i = 0; i < m_horizontal_map.size(); i++) {
        for (int j = 0; j < m_horizontal_map[i].size(); j++) {
            auto value = m_horizontal_map[i][j];
            if (value != '.') {
                m_antenna_map[value].push_back({i, j});
            }
        }
    }
}

const bool Map::is_inside_map(const std::pair<int,int>& poz)
{
    return poz.first >= 0 && poz.first < m_horizontal_map.size() 
        && poz.second >= 0 && poz.second < m_horizontal_map[0].size();
}

const bool Map::is_valid_new_antinode(const std::pair<int,int>& poz, const std::vector<std::vector<bool>>& visited)
{
    // check if points are inside map        
    if (!is_inside_map(poz))
        return false;
        
    // check if point is not already found
    int i = poz.first;
    int j = poz.second;
    
    if (visited[i][j] == true)
        return false;
    
    // antinodes can overlap with other antennas
    // if (m_horizontal_map[i][j] != '.')
    //     return false;
    
    return true;
}

const std::pair<int,int> Map::get_antinode(const std::pair<int,int>& antenna1, const std::pair<int,int>& antenna2)
{
    // 5, 5 first
    // 3, 4 second
    
    // 1, 3 rez
    
    // 3, 4 first
    // 5, 5 second
    
    // 7, 6 rez
    
    auto oy_distance = antenna2.first - antenna1.first;
    auto ox_distance = antenna2.second - antenna1.second;
    
    return {antenna2.first + oy_distance, antenna2.second + ox_distance};
    
}

const std::pair<std::pair<int,int>,std::pair<int,int>> Map::get_potential_antinodes_locations(const std::pair<int,int>& antenna1, const std::pair<int,int>& antenna2)
{
    return {get_antinode(antenna1, antenna2), get_antinode(antenna2, antenna1)};
}

long long Map::get_antinodes_in_direction(const std::pair<int,int>& antenna1, const std::pair<int,int>& antenna2, std::vector<std::vector<bool>>& visited)
{
    auto current = antenna1;
    auto next = antenna2;
    
    long long rez = 0;
    
    do {
        auto antinode = get_antinode(current, next);
        if (!is_inside_map(antinode)) {
            return rez;
        }
        
        visited[antinode.first][antinode.second] = true;
        rez++;
        
        current = next;
        next = antinode;
        
    }while(true);
    
}


Map::Map(const std::vector<std::string>& map): m_horizontal_map(map)
{
    build_antenna_map();
}

long long Map::get_number_antinodes_second()
{
    int n = m_horizontal_map.size();
    int m = m_horizontal_map[0].size();
    
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));

    for (const auto& entry : m_antenna_map) {
        const auto& antenna_locations = entry.second;
        
        for (int i = 0; i < antenna_locations.size() - 1; i++) {
            for (int j = i + 1; j < antenna_locations.size(); j++) {
                
                get_antinodes_in_direction(antenna_locations[i], antenna_locations[j], visited);
                get_antinodes_in_direction(antenna_locations[j], antenna_locations[i], visited);
                
                // if (get_antinodes_in_direction(antenna_locations[i], antenna_locations[j], visited) 
                //     + get_antinodes_in_direction(antenna_locations[j], antenna_locations[i], visited) != 0)
                // {
                //     visited[antenna_locations[i].first][antenna_locations[i].second] = true;
                //     visited[antenna_locations[j].first][antenna_locations[j].second] = true;
                // }
                
                // for some sort of reason in final result antennas that don't have antinodes on map count as antinodes ...
                // this is wrong if you ask me
                visited[antenna_locations[i].first][antenna_locations[i].second] = true;
                visited[antenna_locations[j].first][antenna_locations[j].second] = true;
                
            }
        }
    }
    
    
    long long rez = 0;
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++) {
            if (visited[i][j] == true) {
            
                rez++;
                if (m_horizontal_map[i][j] == '.')
                    m_horizontal_map[i][j] = '#';
            }
        }
    }
    
    return rez;
}

//<= 2 * (n - 1)! antinodes, n - number of antennas with same frequency
long long Map::get_number_antinodes_first(bool display_antinodes)
{
    int n = m_horizontal_map.size();
    int m = m_horizontal_map[0].size();
    
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));

    for (const auto& entry : m_antenna_map) {
        const auto& antenna_locations = entry.second;
        
        for (int i = 0; i < antenna_locations.size() - 1; i++) {
            for (int j = i + 1; j < antenna_locations.size(); j++) {
            
                // each combo should have 2 points, calculate them (something similar to manhaten distance)
                auto potential_antinode_positions = get_potential_antinodes_locations(antenna_locations[i], antenna_locations[j]);
                
                // std::cout << potential_antinode_positions.first.first << " " << potential_antinode_positions.first.second << std::endl;
                // std::cout << potential_antinode_positions.second.first << " " << potential_antinode_positions.second.second << std::endl;
                
                if (is_valid_new_antinode(potential_antinode_positions.first, visited))
                {
                    visited[potential_antinode_positions.first.first][potential_antinode_positions.first.second] = true;
                }
                
                if (is_valid_new_antinode(potential_antinode_positions.second, visited))
                {
                    visited[potential_antinode_positions.second.first][potential_antinode_positions.second.second] = true;
                }
            }
        }
    }
    
    
    long long rez = 0;
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++) {
            if (visited[i][j] == true) {
            
                rez++;
                if (display_antinodes)
                    m_horizontal_map[i][j] = '#';
            }
        }
    }
    
    return rez;
}

std::ostream& operator<<(std::ostream& os, const Map& map)
{
    for (const auto& line : map.m_horizontal_map){
        os << line << std::endl;
    }
    
    return os;
}
