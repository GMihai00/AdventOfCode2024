#include "Garden.hpp"
#include <queue>
#include <iostream>

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

const long long Garden::count_number_edges(const std::vector<std::vector<bool>>& is_edge)
{
    long long rez = 0;
    std::vector<std::vector<bool>> edge_visited(m_horizontal_view.size(), std::vector<bool>(m_horizontal_view[0].size(), false));
    
    for (int i = 0; i < m_horizontal_view.size(); i++) {
        for (int j = 0; j < m_horizontal_view[i].size(); j++) {
        
            if (is_edge[i][j] && !edge_visited[i][j]) {
                
                // TO DO
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
    
    std::vector<std::vector<bool>> is_edge(m_horizontal_view.size(), std::vector<bool>(m_horizontal_view[0].size(), false));
    
    while (!to_visit.empty()) {
    
        auto poz = to_visit.front();
        to_visit.pop();
        
        area++;
        
        auto edge_directions = get_edge_directions(poz);
        
        // to calculate perimeter
        if (edge_directions.size() > 0)
            is_edge[poz.first][poz.second] = true;;
            
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
    
    perimeter = count_number_edges(is_edge);
    
    auto map_copy = std::vector<std::string>(m_horizontal_view);
    
    for (int i = 0; i < is_edge.size(); i++)
        for (int j = 0; j < is_edge[i].size(); j++)
            map_copy[i][j] = '*';
        
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
