#include "TrailMap.hpp"
#include <queue>
#include <iostream>

void TrailMap::build_map(const std::vector<std::string>& data)
{
    for (int i = 0; i < data.size(); i++) {
        m_horizontal_view.push_back({});
        for (int j = 0; j <  data[i].size(); j++) {
            m_horizontal_view[i].push_back(data[i][j]- '0');
            
            if (data[i][j] == '0') {
                m_trail_start_positions.push_back({i, j});
            }
        }
    }
}

const long long TrailMap::get_trail_score(const std::pair<int,int>& trail_head)
{
    long long score = 0;
    
    std::vector<std::vector<bool>> visited(m_horizontal_view.size(), std::vector<bool>(m_horizontal_view[0].size(), false));
    
    std::queue<std::pair<int, int>> to_visit;
    
    to_visit.push(trail_head);
    visited[trail_head.first][trail_head.second] = true;
            
    std::vector<std::pair<int, int>> directions = {
        {1, 0},
        {0, 1},
        {-1, 0},
        {0, -1}
    };
    
    while (!to_visit.empty()) {
    
        auto poz = to_visit.front();
        to_visit.pop();
        
        int current_hight = m_horizontal_view[poz.first][poz.second];
        
        if (current_hight == 9) {
            score++;
            continue;
        }
        
        for (const auto& direction : directions) {
        
            auto next_poz = std::make_pair(poz.first + direction.first, poz.second + direction.second);
            
            if (!is_inside_map(next_poz))
                continue;
                
            if (visited[next_poz.first][next_poz.second] == false && m_horizontal_view[next_poz.first][next_poz.second] - current_hight == 1) {
                to_visit.push(next_poz);
                visited[next_poz.first][next_poz.second] = true;
            }
        }
    }
    
    return score;
}


const bool TrailMap::is_inside_map(const std::pair<int, int>& poz)
{
    return poz.first >= 0 && poz.first < m_horizontal_view.size() &&
        poz.second >= 0 && poz.second < m_horizontal_view[poz.first].size();
}

TrailMap::TrailMap(const std::vector<std::string>& data)
{
    build_map(data);
}

const long long TrailMap::get_total_trail_score()
{
    long long rez = 0;
    
    for (const auto& trail_head : m_trail_start_positions) {
        rez += get_trail_score(trail_head);
    }
    
    return rez;
}

const long long TrailMap::get_trail_rating(const std::pair<int,int>& trail_head)
{
    long long score = 0;
    
    std::vector<std::vector<long long>> visit_count(m_horizontal_view.size(), std::vector<long long>(m_horizontal_view[0].size(), 0));
    
    auto compare = [](std::pair<int, std::pair<int, int>> a, std::pair<int, std::pair<int, int>> b) {
        return a.first > b.first;
    };
    
    std::priority_queue<std::pair<int, std::pair<int, int>>, std::vector<std::pair<int, std::pair<int, int>>>, decltype(compare)> to_visit(compare);
    
    to_visit.push({m_horizontal_view[trail_head.first][trail_head.second], trail_head});
    
    visit_count[trail_head.first][trail_head.second] = 1;
            
    std::vector<std::pair<int, int>> directions = {
        {1, 0},
        {0, 1},
        {-1, 0},
        {0, -1}
    };
    
    std::vector<std::pair<int, int>> reached_tops;
    
    while (!to_visit.empty()) {
    
        auto item = to_visit.top();
        auto poz = item.second;
        auto current_hight = item.first;
        to_visit.pop();
        
        // std::cout << current_hight << std::endl;
        
        if (current_hight == 9) {
            reached_tops.push_back(poz);
            continue;
        }
        
        for (const auto& direction : directions) {
        
            auto next_poz = std::make_pair(poz.first + direction.first, poz.second + direction.second);
            
            if (!is_inside_map(next_poz))
                continue;
                
            if (m_horizontal_view[next_poz.first][next_poz.second] - current_hight == 1) {
                
                if (visit_count[next_poz.first][next_poz.second] == 0)
                    to_visit.push({m_horizontal_view[next_poz.first][next_poz.second], next_poz});
                visit_count[next_poz.first][next_poz.second]+= visit_count[poz.first][poz.second];
            }
        }
    }
    
    for (const auto& top: reached_tops)
    {
        score += visit_count[top.first][top.second];
    }
    
    // std::cout << score << std::endl;
    
    return score;
}

const long long TrailMap::get_total_trail_rating()
{  
    long long rez = 0;
    
    for (const auto& trail_head : m_trail_start_positions) {
        rez += get_trail_rating(trail_head);
    }
    
    return rez;
    
    return 0;
}
