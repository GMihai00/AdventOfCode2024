#include <map>
#include <vector>
#include <functional>
#include <string>
#include <fstream>

class Map {

private:
    std::vector<std::string> m_horizontal_map;
    // values can be 0-9, 'a'-'z' 'A'-'Z' so not overlapping in asci
    // no need for set as I parse them only once
    std::map<int, std::vector<std::pair<int, int>>> m_antenna_map;
    
    void build_antenna_map();
    
    const bool is_inside_map(const std::pair<int, int>& poz);
    
    const bool is_valid_new_antinode(const std::pair<int, int>& poz, const std::vector<std::vector<bool>>& visited);
    
    const std::pair<int, int> get_antinode(const std::pair<int, int>& antenna1, const std::pair<int, int>& antenna2);
    
    const std::pair<std::pair<int, int>, std::pair<int, int>> 
        get_potential_antinodes_locations(const std::pair<int, int>& antenna1, const std::pair<int, int>& antenna2);
    
    
    long long get_antinodes_in_direction(const std::pair<int, int>& antenna1, const std::pair<int, int>& antenna2, std::vector<std::vector<bool>>& visited);
    
public:

    Map(const std::vector<std::string>& map);
    
    long long get_number_antinodes_first(bool display_antinodes = false);
    
    long long get_number_antinodes_second();
    
    friend std::ostream& operator<<(std::ostream& os, const Map& map);
};

