#include "Map.hpp"

Map::Map(const std::vector<std::string>& view) : m_horizontal_view(view.begin(), view.end()) {

    for (int j = 0; j < view[0].size(); j++)
    {
        m_vertical_view.push_back({});
        for (int i = 0; i < view.size(); i++) {
            m_vertical_view[j].push_back(view[i][j]);
            if (view[i][j] == '^') {
                m_guard_initial_position = {i, j};
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