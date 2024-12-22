#include "StoneLine.hpp"

#include <iostream>
#include <sstream>
#include <algorithm>
#include <utility> 

namespace helpers {
    inline void normalize_stone_number(std::string& stone) {
        
        int it = 0;
        
        while (it < stone.size() - 1 && stone[it] == '0')
            it++;
            
        stone = stone.substr(it, stone.size() - it);
    }
}

std::vector<std::string> StoneLine::apply_rule_to_stone(const std::string& stone)
{
    if (stone == "0")
        return {"1"};
        
    if (stone.size() % 2 == 0) {
        
        auto left = stone.substr(0, stone.size() / 2);
        auto right = stone.substr(stone.size() / 2, stone.size() / 2);
        helpers::normalize_stone_number(right);
        
        return  {left, right};
    }
    
    auto numeric_value = std::stoull(stone);
    
    numeric_value *= 2024;
    
    return {std::to_string(numeric_value)};
}

std::vector<std::string> StoneLine::blink(const std::vector<std::string>& stones)
{
    std::vector<std::string> new_array;
    
    for (const auto& stone : stones) {
    
        auto stones = apply_rule_to_stone(stone);
    
        
        new_array.insert(new_array.end(), stones.begin(), stones.end());
    }
    
    // std::cout << "------------------------------------------\n";
    std::for_each(new_array.begin() , new_array.end(), 
        [](const std::string& stone) { 
            // std::cout << stone << " ";
        });
        
    // std::cout << "\nSize: " << new_array.size();
    // std::cout << "\n------------------------------------------\n\n";
    
    return new_array;
}

void StoneLine::collect_stone_values(const std::string & line)
{
    std::istringstream iss(line);
    
    std::string word;
    while (iss >> word) {
        m_stones.push_back(word);
    }
}

std::pair<int,std::vector<std::string>> StoneLine::get_precomputed_value(const std::string& stone, const int blinks_left)
{
    if (auto it = m_available_blink_sizes.find(stone); it != m_available_blink_sizes.end()) {
        
        if (auto it2 = it->second.lower_bound(-blinks_left); it2 != it->second.end()){
            
            auto stone_copy = stone;
            auto number = *it2;
            std::pair<std::string, int> entry = std::make_pair(stone_copy, number);
            
            if (auto it3 = m_blink_map.find(entry); it3 != m_blink_map.end()) {
                return {number, it3->second};
            }
            else {
                throw std::runtime_error("something went wrong with set-map sync");
                
            }
        }
    }

    return {0, {}};
}

std::vector<std::string> StoneLine::blink_recursive(const std::string& stone, const int blinks_left)
{
    std::vector<std::string> rez;
    
    if (blinks_left < 0)
        throw std::runtime_error("something went bad");
        
    if (blinks_left == 0)
        return {stone}; // no more need for blinks
    
    auto value = get_precomputed_value(stone, blinks_left);
    
    if (value.first != blinks_left)
    {
        // std::cout << stone << std::endl;
        auto stones = apply_rule_to_stone(stone);
        
        for (const auto& stn : stones) {
            auto blink_rez = blink_recursive(stn, blinks_left - 1);
            rez.insert(rez.end(), blink_rez.begin(), blink_rez.end());
        }
    }
    else {
        rez.insert(rez.end(), value.second.begin(), value.second.end());
    }
    
    auto stone_copy = stone;
    std::pair<std::string, int> entry = std::make_pair(stone_copy, -blinks_left);
    
    m_blink_map[entry] = rez;
    m_available_blink_sizes[stone].insert(-blinks_left);
    
    return rez;
}

StoneLine::StoneLine(const std::string& line)
{
    collect_stone_values(line);
}

const long long StoneLine::solve_first()
{

    long long rez = 0;
    
    for (const auto& stone : m_stones) {
        std::vector<std::string> stone_copy = {stone};
        
        for (int i = 0; i < 25; i++)
        {
            stone_copy = blink(stone_copy);
        }
        
        rez += stone_copy.size();
    }
    
    return rez;
}

const long long StoneLine::solve_second()
{
    long long rez = 0;
    for (const auto& stone : m_stones) {
        
        std::vector<std::string> stone_cpy = {stone};
        
        for (int i = 1; i <= 15; i++) {
            std::vector<std::string> new_stone_copy;
            
            for (const auto& stone : stone_cpy) {
                auto blink_rez = blink_recursive(stone, 5);
                new_stone_copy.insert(new_stone_copy.end(), blink_rez.begin(), blink_rez.end());
            }
            
            stone_cpy = new_stone_copy;
            
        }
        
        rez += stone_cpy.size();
        
    }
    
    return rez;
    
}
