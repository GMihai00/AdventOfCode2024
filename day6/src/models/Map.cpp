#include "Map.hpp"

Map::Map(const std::vector<std::string>& view) : m_horizontal_view(view.begin(), view.end()) {
    
    std::vector<std::pair<int,int>> directions = {
        {-1, 0},
        {0, 1},
        {1, 0},
        {0, -1}
    };
    
    int n = view.size();
    int m = view[0].size();
    
    std::vector<std::set<int>> collided_up(m, std::set<int>());
    std::vector<std::set<int>> collided_down(m, std::set<int>());
    std::vector<std::set<int>> collided_right(n, std::set<int>());
    std::vector<std::set<int>> collided_left(n, std::set<int>());
    
    m_objects[0] = collided_up;
    m_objects[1] = collided_right;
    m_objects[2] = collided_down;
    m_objects[3] = collided_left;
    
    for (int j = 0; j < m; j++)
    {
        m_vertical_view.push_back({});
        for (int i = 0; i < n; i++) {
            m_vertical_view[j].push_back(view[i][j]);
            if (view[i][j] == '^') {
                m_guard_initial_position = {i, j};
            }
            else if (view[i][j] == '#') {
                
                for (int it = 0; it < 4; it++) {
                    int line = (it % 2 == 0) ? j : i;
                    int value = (it % 2 == 0) ? i : j;
                    
                    int asc;
                    
                    if (directions[it].first != 0)
                        asc = directions[it].first;
                    else 
                        asc =  directions[it].second;
                
                    m_objects[it][line].insert(value * asc);
                }
            }
        }
    }
    
}

std::ostream& operator<<(std::ostream& os, const Map& map)
{
    for (const auto& line : map.m_horizontal_view){
        os << line << std::endl;
    }
    
    return os;
}