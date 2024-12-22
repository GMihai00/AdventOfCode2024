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

const unsigned long long StoneLine::solve_second()
{
    
    std::map<std::string, unsigned long long> freq_map;
    
    for (const auto& stone : m_stones) {
        freq_map[stone]++;
    }
    
    
    for (int i = 0; i < 75; i++) {
        std::map<std::string, unsigned long long> new_freq_map;
        
        for (const auto& it : freq_map) {
            auto stone = it.first;
            auto freq = it.second;
            
            auto stones = apply_rule_to_stone(stone);
            
            for (const auto& stn : stones) {
                new_freq_map[stn]+=freq;
            }
            
        }
        
        freq_map = new_freq_map;
        
    }
    
    unsigned long long rez = 0;
    
    for (const auto& it : freq_map) {
        rez += it.second;
    }
    
    return rez;
    
}
