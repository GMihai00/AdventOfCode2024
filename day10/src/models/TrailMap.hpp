#include <vector>
#include <vector>
#include <string>

class TrailMap {

private:
    std::vector<std::vector<short>> m_horizontal_view;
    std::vector<std::pair<int, int>> m_trail_start_positions;
    
    void build_map(const std::vector<std::string>& data);
    
    const long long get_trail_score(const std::pair<int, int>& trail_head);
    
    const long long get_trail_rating(const std::pair<int, int>& trail_head);
    
    const bool is_inside_map(const std::pair<int, int>& poz);
public:
    TrailMap(const std::vector<std::string>& data);

    const long long get_total_trail_score();
    const long long get_total_trail_rating();
};
