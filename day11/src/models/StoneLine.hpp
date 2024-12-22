#include <vector>
#include <string>
#include <map>
#include <set>
#include <functional>

class StoneLine {

private:
    std::vector<std::string> m_stones;
    
    
    std::vector<std::string> apply_rule_to_stone(const std::string& stone);
    
    std::vector<std::string> blink(const std::vector<std::string>& stones);
    void collect_stone_values(const std::string& line);
    
public:
    StoneLine(const std::string& line);
    
    const long long solve_first();
    
    const unsigned long long solve_second();
};