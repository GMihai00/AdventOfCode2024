#include "Robot.hpp"

#include <regex>
#include <string>

void Robot::extract_position_and_velocity(const std::string & line)
{
    std::regex pattern(R"(p=(-?\d+),(-?\d+) v=(-?\d+),(-?\d+))");
    
    std::smatch match;

    if (std::regex_search(line, match, pattern)) {
        m_initial_pos.second = std::stoi(match[1].str());
        m_initial_pos.first = std::stoi(match[2].str());
        m_velocity.second= std::stoi(match[3].str());
        m_velocity.first = std::stoi(match[4].str());
    }
    else {
        throw std::runtime_error("Unable to extract robot data from line: " + line);
    }
}

Robot::Robot(const std::string & line)
{
    extract_position_and_velocity(line);
}

std::pair<int,int> Robot::get_next_position(const int seconds)
{    
    int y = (long long) m_initial_pos.first + (long long) m_velocity.first * seconds;
    
    y %= GRID_HEIGHT;
    
    if (y < 0) {
        y = GRID_HEIGHT + y;
    }
    
    int x = (long long) m_initial_pos.second + (long long) m_velocity.second * seconds;
    
    x %= GRID_WIDTH;
    
    if (x < 0) {
        x = GRID_WIDTH + x;
    }
    
    return {y, x};
}
