#ifndef ROBOT_HPP
#define ROBOT_HPP

#define GRID_HEIGHT 103
#define GRID_WIDTH 101

#include <functional>
#include <string>

class Robot {

private:
    std::pair<int, int> m_initial_pos;
    std::pair<int, int> m_velocity;
    
    void extract_position_and_velocity(const std::string& line);
    
public:
    Robot(const std::string& line);
    
    std::pair<int, int> get_next_position(const int seconds);
};

#endif // ROBOT_HTPP