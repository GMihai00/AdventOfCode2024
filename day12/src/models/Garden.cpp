#include "Garden.hpp"
#include <queue>
#include <iostream>
#include <map>
#include <set>

const std::pair<long long, long long> Garden::get_sub_garden_area_and_perimeter(std::pair<int, int> starting_poz, std::vector<std::vector<bool>>& visited)
{
    // std::cout << m_horizontal_view[starting_poz.first][starting_poz.second] << std::endl;
    
    long long area = 0;
    long long perimeter = 0;
    
    std::queue<std::pair<int, int>> to_visit;
    
    to_visit.push(starting_poz);
    
    visited[starting_poz.first][starting_poz.second] = true;
    
    while (!to_visit.empty()) {
    
        auto poz = to_visit.front();
        to_visit.pop();
        
        area++;
        perimeter+= calculate_cell_perimeter(poz);
        
        for (const auto& direction : directions) {
        
            auto next_poz = std::make_pair<>(poz.first + direction.first, poz.second + direction.second);
            
            if (is_inside_map(next_poz)) {
            
                if (visited[next_poz.first][next_poz.second] == false && 
                    m_horizontal_view[next_poz.first][next_poz.second] == m_horizontal_view[poz.first][poz.second]) {
                    
                    visited[next_poz.first][next_poz.second] = true;
                    to_visit.push(next_poz);
                }
            }
        }
        
    }
    
    // std::cout << "Area: " << area << " Perimeter: " << perimeter << std::endl;
    return {area, perimeter};
}

const long long Garden::count_number_edges(const std::vector<std::vector<int>>& is_edge)
{
    long long rez = 0;
    
    std::map<std::pair<double, double>, std::pair<int, int>> edges;
    std::set<std::pair<double, double>> counted_edges;
    
    for (int i = 0; i < m_horizontal_view.size(); i++) {
        for (int j = 0; j < m_horizontal_view[i].size(); j++) {
        
            if (is_edge[i][j]) {
                
                for (const auto& direction: directions) {
                
                    auto next_poz = std::make_pair<>(i + direction.first, j + direction.second);
        
                    auto edge_position = std::make_pair<> (i + (double) direction.first / 2, j + (double) direction.second / 2);
                    
                    if (is_inside_map(next_poz)) {
            
                        if (m_horizontal_view[next_poz.first][next_poz.second] != m_horizontal_view[i][j]) {
                            edges[edge_position] = direction;
                        }
                    
                    }else {
                        edges[edge_position] = direction;
                    }
                }
            }
        }
    
    }
    
    for (const auto& entry : edges) {
        
        auto edge = entry.first;
        auto edge_direction = entry.second;
        
        if (counted_edges.find(edge) != counted_edges.end())
            continue;
        
        counted_edges.insert(edge);
        rez++;
        
        auto follow_directions = get_edge_follow_directions(edge_direction);
        
        for (const auto& direction : follow_directions) {
        
            auto edge_copy = edge;
            auto next_edge = std::make_pair<>(edge_copy.first + direction.first, edge_copy.second + direction.second);
            auto it = edges.find(next_edge);

            while(it != edges.end() && it->second.first == edge_direction.first && it->second.second == edge_direction.second) {
                
                counted_edges.insert(next_edge);
                edge_copy = next_edge;
                next_edge = std::make_pair<>(edge_copy.first + direction.first, edge_copy.second + direction.second);
                it = edges.find(next_edge);
            }
            
        }
        
    }
    
    return rez;
}

const std::pair<long long,long long> Garden::get_sub_garden_area_and_discounted_perimeter(std::pair<int,int> starting_poz, std::vector<std::vector<bool>>& visited)
{
    std::cout << m_horizontal_view[starting_poz.first][starting_poz.second] << std::endl;

    long long area = 0;
    long long perimeter = 0;
    
    std::queue<std::pair<int, int>> to_visit;
    
    to_visit.push(starting_poz);
    
    visited[starting_poz.first][starting_poz.second] = true;
    
    std::vector<std::vector<int>> edge_count(m_horizontal_view.size(), std::vector<int>(m_horizontal_view[0].size(), 0));
    
    while (!to_visit.empty()) {
    
        auto poz = to_visit.front();
        to_visit.pop();
        
        area++;
        
        auto edge_directions = get_edge_directions(poz);
        
        // to calculate perimeter
        if (edge_directions.size() > 0)
            edge_count[poz.first][poz.second] = edge_directions.size();
            
        for (const auto& direction : directions) {
        
            auto next_poz = std::make_pair<>(poz.first + direction.first, poz.second + direction.second);
            
            if (is_inside_map(next_poz)) {
            
                if (visited[next_poz.first][next_poz.second] == false && 
                    m_horizontal_view[next_poz.first][next_poz.second] == m_horizontal_view[poz.first][poz.second]) {
                    
                    visited[next_poz.first][next_poz.second] = true;
                    to_visit.push(next_poz);
                }
            }
        }
    }
    
    // do the left right to the end madness
    // just count edges as separate entities 
    
    perimeter = count_number_edges(edge_count);
    
    auto map_copy = std::vector<std::string>(m_horizontal_view);
    
    for (int i = 0; i < edge_count.size(); i++)
        for (int j = 0; j < edge_count[i].size(); j++)
            if (edge_count[i][j] != 0)
                map_copy[i][j] =  '0' + edge_count[i][j];
        
    for (const auto& line : map_copy) {
        std::cout << line << std::endl;
    }
    
    std::cout << std::endl;
    
    std::cout << "Area: " << area << " Perimeter: " << perimeter << std::endl;
    return {area, perimeter};
}

const std::vector<std::pair<int,int>> Garden::get_edge_directions(const std::pair<int,int>& poz)
{
    std::vector<std::pair<int,int>> rez;
    
    for (const auto& direction : directions) {
        
        auto next_poz = std::make_pair<>(poz.first + direction.first, poz.second + direction.second);
        
        if (is_inside_map(next_poz)) {
            
            if (m_horizontal_view[next_poz.first][next_poz.second] != m_horizontal_view[poz.first][poz.second]) {
                rez.push_back(direction);
            }
            
        }else {
            rez.push_back(direction);
        }
    }
    
    return rez;
}

// can be at most 4
const int Garden::calculate_cell_perimeter(const std::pair<int,int>& poz)
{
    int rez = 0;
    
    for (const auto& direction : directions) {
        
        auto next_poz = std::make_pair<>(poz.first + direction.first, poz.second + direction.second);
        
        if (is_inside_map(next_poz)) {
            
            if (m_horizontal_view[next_poz.first][next_poz.second] != m_horizontal_view[poz.first][poz.second]) {
                rez++;
            }
            
        }else {
            rez++;
        }
    }
    
    return rez;
}

const std::vector<std::pair<int, int>> Garden::get_edge_follow_directions(const std::pair<int,int> edge_direction)
{
    if (abs(edge_direction.first) == 1) {
        // if edge is above or bellow need to go left/right
        return  {{0, -1}, {0, 1}};
    } else {
        // if edge is to the right or to the left need to go up/down
        return {{1, 0}, {-1, 0}};
    }
}


const bool Garden::is_inside_map(const std::pair<int,int>& poz)
{
    return poz.first >= 0 && poz.first < m_horizontal_view.size() &&
        poz.second >= 0 && poz.second < m_horizontal_view[0].size();
}

Garden::Garden(const std::vector<std::string>& data) : m_horizontal_view(data)
{
}

const long long Garden::get_total_fence_price()
{
    long long rez = 0;
    
    std::vector<std::vector<bool>> visited(m_horizontal_view.size(), 
        std::vector<bool>(m_horizontal_view[0].size(), false));
    
    for (int i = 0; i < m_horizontal_view.size(); i++){
    
        for (int j = 0; j < m_horizontal_view[i].size(); j++) {
            if (visited[i][j] == false){
                auto area_perimeter = get_sub_garden_area_and_perimeter({i, j}, visited);
                
                rez = rez + area_perimeter.first * area_perimeter.second;
            }
        }
    }
    
    return rez;
}

const long long Garden::get_total_fence_discounted_price()
{
    long long rez = 0;
    
    std::vector<std::vector<bool>> visited(m_horizontal_view.size(), 
        std::vector<bool>(m_horizontal_view[0].size(), false));
    
    for (int i = 0; i < m_horizontal_view.size(); i++){
    
        for (int j = 0; j < m_horizontal_view[i].size(); j++) {
            if (visited[i][j] == false){
                auto area_perimeter = get_sub_garden_area_and_discounted_perimeter({i, j}, visited);
                
                rez = rez + area_perimeter.first * area_perimeter.second;
            }
        }
    }
    
    return rez;
}
