#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <set>
class Map {

public:
    std::vector<std::string> m_vertical_view;
    std::vector<std::string> m_horizontal_view;
    std::pair<int, int> m_guard_initial_position;
    std::map<int, std::vector<std::set<int>>> m_objects;
    
    Map(const std::vector<std::string>& view);
    
    friend std::ostream& operator<<(std::ostream& os, const Map& map);
};