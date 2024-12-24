#include <string>
#include <vector>

class Garden {

private:
    std::vector<std::string> m_horizontal_view;
    
    const std::vector<std::pair<int, int>> directions = {
        {1, 0},
        {0, 1},
        {-1, 0},
        {0, -1}
    }; 
    
    const std::pair<long long, long long> get_sub_garden_area_and_perimeter(std::pair<int, int> starting_poz, std::vector<std::vector<bool>>& visited);
    const std::pair<long long, long long> get_sub_garden_area_and_discounted_perimeter(std::pair<int, int> starting_poz, std::vector<std::vector<bool>>& visited);

    const std::vector<std::pair<int, int>> get_edge_directions(const std::pair<int, int>& poz);
    const int calculate_cell_perimeter(const std::pair<int, int>& poz);
    
    const std::vector<std::pair<int, int>> get_edge_follow_directions(const std::pair<int, int> edge_direction);
    
    const long long count_number_edges(const std::vector<std::vector<int>>& is_edge);
    
    const bool is_inside_map(const std::pair<int, int>& poz);
public:
    Garden(const std::vector<std::string>& data);
    
    const long long get_total_fence_price();
    
    const long long get_total_fence_discounted_price();
};