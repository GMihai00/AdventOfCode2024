#include <vector>
#include <string>
#include <map>
#include <set>
#include <functional>

class StoneLine {

private:
    std::vector<std::string> m_stones;
    
    std::map<std::pair<std::string, int>, std::vector<std::string>> m_blink_map;
    
    // to add negative numbers here to be able to do lower bound
    std::map<std::string, std::set<int>> m_available_blink_sizes;
    
    std::vector<std::string> apply_rule_to_stone(const std::string& stone);
    std::vector<std::string> blink(const std::vector<std::string>& stones);
    void collect_stone_values(const std::string& line);
    
    std::pair<int, std::vector<std::string>> get_precomputed_value(const std::string& stone, const int blinks_left);
    
    std::vector<std::string> blink_recursive(const std::string& stone, const int blinks_left);
public:
    StoneLine(const std::string& line);
    
    const long long solve_first();
    
    const long long solve_second();
};