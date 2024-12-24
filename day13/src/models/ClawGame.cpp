#include "ClawGame.hpp"

#include <regex>
#include <functional>
#include <iostream>

const std::pair<unsigned long long, unsigned long long> ClawGame::extract_button_move(const std::string & line)
{
    std::regex pattern(R"(Button .: X\+(\d+), Y\+(\d+))");
    
    std::smatch match;

    if (std::regex_search(line, match, pattern)) {
        auto x = match[1].str();
        auto y = match[2].str();
        return {std::stoull(x), std::stoull(y)};
    } else {
        throw std::runtime_error("failed to find button match in line: " + line);
    }
    
}

const std::pair<unsigned long long, unsigned long long> ClawGame::extract_prize_location(const std::string & line)
{
    std::regex pattern(R"(Prize: X=(\d+), Y=(\d+))");
    
        std::smatch match;

    if (std::regex_search(line, match, pattern)) {
        auto x = match[1].str();
        auto y = match[2].str();
        return {std::stoull(x), std::stoull(y)};
    } else {
        throw std::runtime_error("failed to find prize match in line: " + line);
    }
    
}

const std::optional<std::pair<unsigned long long,unsigned long long>> ClawGame::try_solve_equation_maximization(unsigned long long a, unsigned long long b, unsigned long long rez)
{
    
    unsigned long long start = (rez / a) * a;
    for (auto it = start; it >= 0; it-=a) {
        unsigned long long current = rez - start;
        
        if (current % b == 0) {
            
            return std::make_pair<>(current / b, it / a);
        }
        
    }
    
    return std::nullopt;
}

ClawGame::ClawGame(const std::string & a, const std::string & b, const std::string & prize)
{
    m_a_button_move = extract_button_move(a);
    m_b_button_move = extract_button_move(b);
    m_prize_location = extract_prize_location(prize);
}

const std::optional<unsigned long long> ClawGame::brute_force_best_combination()
{
    const int a_cost = 3;
    const int b_cost = 1;
    
    std::optional<unsigned long long> rez = std::nullopt;
    
    for (int i = 0; i <= 100; i++){
        for (int j = 0; j <= 100; j++) {
        
            auto x_val = i * m_a_button_move.first + j * m_b_button_move.first;
            auto y_val = i * m_a_button_move.second + j * m_b_button_move.second;
            
            if (x_val > m_prize_location.first || y_val > m_prize_location.second){
                j = 101;
                continue;
            }
            
            if (x_val == m_prize_location.first && y_val == m_prize_location.second) {
                
                auto new_cost = (unsigned long long) a_cost * i + (unsigned long long) b_cost * j;
                
                rez = (rez == std::nullopt) ? new_cost : std::max(*rez, new_cost);
                
            }
            
        }
    }
    
    return rez;
}

// could be done with ILP as well
const std::optional<unsigned long long> ClawGame::get_best_combination()
{
    const int a_cost = 3;
    const int b_cost = 1;
    
    std::optional<unsigned long long> rez = std::nullopt;
    
    // first case: first and second button do the same thing and target coordinates are the same
    // it's better to straight up use the second button
    // we can do a binary search on integer values to try to get solution
    
    // Xa / Xb == Ya / Yb == Xprize / Yprize
    if (m_prize_location.first * m_b_button_move.first == m_prize_location.second * m_a_button_move.first &&
        m_prize_location.first * m_b_button_move.second == m_prize_location.second * m_a_button_move.second &&
        m_a_button_move.first * m_b_button_move.second == m_a_button_move.second * m_b_button_move.first) {
        
        // try to maximize a
        
        auto max_pair = try_solve_equation_maximization(m_a_button_move.first, m_b_button_move.first, m_prize_location.first);
        
        if (max_pair != std::nullopt) {
            rez = max_pair->first * a_cost + max_pair->second * b_cost; 
        }
        
        // try to maximize b
        
        max_pair = try_solve_equation_maximization(m_b_button_move.first, m_a_button_move.first, m_prize_location.first);
        
        if (max_pair != std::nullopt) {
            auto val = max_pair->first * b_cost + max_pair->second * a_cost; 
            
            rez = (rez == std::nullopt) ? val : std::max(*rez, val);

        }
        
        return rez;
    }
    
    // second case: equation is not solvable return null
    
    if (m_a_button_move.first * m_b_button_move.second == m_a_button_move.second * m_b_button_move.first &&
        m_prize_location.first != m_prize_location.second)
            return std::nullopt;
    
    // third case: we have 2 separate equations 
    // solve system of 2 equations with 2 variables
    // multiply by coefficient of X opposite equations + substract
    
    unsigned long long exponent = 0;
    unsigned long long divisor = 1;
    
    
    
    if ((OVERHEAD + m_prize_location.second) * m_a_button_move.first > (OVERHEAD + m_prize_location.first) * m_a_button_move.second) {
        exponent = (OVERHEAD + m_prize_location.second) * m_a_button_move.first - (OVERHEAD + m_prize_location.first) * m_a_button_move.second;
        divisor = m_b_button_move.second * m_a_button_move.first - m_b_button_move.first * m_a_button_move.second;
        
        // would result in negative a,b values
        if (m_b_button_move.second * m_a_button_move.first < m_b_button_move.first * m_a_button_move.second)
            return std::nullopt;
            
    } else {
        exponent = (OVERHEAD + m_prize_location.first) * m_a_button_move.second - (OVERHEAD + m_prize_location.second) * m_a_button_move.first;
        divisor = m_b_button_move.first * m_a_button_move.second - m_b_button_move.second * m_a_button_move.first;
        
        // would result in negative a,b values
        if (m_b_button_move.second * m_a_button_move.first > m_b_button_move.first * m_a_button_move.second)
            return std::nullopt;
    }
    
    // we are interested only in integer solutions of our equations
    if (exponent % divisor != 0) {
        return std::nullopt;
    }
    
    unsigned long long b_count = exponent / divisor;
    
    
    exponent = (OVERHEAD + m_prize_location.first - 
        b_count * m_b_button_move.first);
    
    divisor = m_a_button_move.first;
    
    // we are interested only in integer solutions of our equations
    if (exponent % divisor != 0) {
        return std::nullopt;
    }
    
    unsigned long long a_count = exponent / divisor;
    
    return a_count * a_cost + b_count * b_cost;
}
