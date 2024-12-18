#include <vector>
#include <string>
#include <iostream>

class Map {

public:
    std::vector<std::string> m_vertical_view;
    std::vector<std::string> m_horizontal_view;
    std::pair<int, int> m_guard_initial_position;
    
    Map(const std::vector<std::string>& view);
    
    friend std::ostream& operator<<(std::ostream& os, const Map& map);
};