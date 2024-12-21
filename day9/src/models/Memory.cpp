#include <exception>
#include <iostream>
#include "Memory.hpp"

namespace helpers {
    inline long long get_interval_sum(unsigned long long left, unsigned long long right) {
        
        if (left < 0 || right < 0)
            throw std::runtime_error("Invalid data passed to function: " + std::string(__func__));
        
        if (left >= 1)
            return right * (right + 1) / 2 - left * (left - 1) / 2;
        else 
            return right * (right + 1) / 2;
    }
}

void Memory::build_disk_space(const std::string & data)
{
    unsigned long long stored = 1;
    for (const char& chr : data) {
        unsigned long long len = chr - '0';
        if (stored == 1) {
            m_occupied_disk.push_back(len);
        }
        else {
            m_free_space.push_back(len);
        }
        
        stored = 1 - stored;
    }
}

Memory::Memory(const std::string & data)
{
    build_disk_space(data);
        
}

const unsigned long long Memory::get_checksum_first()
{
    unsigned long long rez = 0;
    
    // need to know how far I am to the right to calculate partial sums
    unsigned long long left_poz = 0;
    
    unsigned long long id_occupied_memory = 0;
    
    std::vector<unsigned long long> occupied_memory_copy = m_occupied_disk;
    
    unsigned long long id_free_memory = 0;
    
    unsigned long long state = 1;
    
    // first add already occupied memory state 1
    // then try to fill in empty memory state 0
    // repeat
    // ! be carefull when moving memory, memory to not be on the left hand side of the free space
        
    while(id_occupied_memory < occupied_memory_copy.size() && id_free_memory < m_free_space.size()) {
        
        if (state == 1) {
        
            auto next_poz = left_poz + occupied_memory_copy[id_occupied_memory];
            
            auto par_sum = helpers::get_interval_sum(left_poz, next_poz - 1);
            
            rez += id_occupied_memory * par_sum;
            
            left_poz = next_poz;
            
            id_occupied_memory++;
        
        } else {
            
            auto empty_memory_space = m_free_space[id_free_memory];

            while (empty_memory_space != 0 && id_occupied_memory < occupied_memory_copy.size()) {
                
                auto last_occupied_memory_length = occupied_memory_copy.back();
                
                if (last_occupied_memory_length < empty_memory_space) {
                    // move entire memory entry + add checksum
                    
                    auto next_poz = left_poz + last_occupied_memory_length;
                    
                    auto par_sum = helpers::get_interval_sum(left_poz, next_poz - 1);
                    
                    rez += (occupied_memory_copy.size() - 1) * par_sum; 
                    
                    left_poz = next_poz;
                    
                    // remove last position of the occupied_memory array
                    occupied_memory_copy.pop_back();
                    
                    // decrement empty_memory_space
                    empty_memory_space -= last_occupied_memory_length;
                }
                else {
                    // move partially the memory to free space + add checksum
                    auto next_poz = left_poz + empty_memory_space;
                    
                    auto par_sum = helpers::get_interval_sum(left_poz, next_poz - 1);
                    
                    rez += (occupied_memory_copy.size() - 1) * par_sum; 
                    
                    left_poz = next_poz;
                    
                    unsigned long long dif = last_occupied_memory_length - empty_memory_space;
                    
                    // remove last position of the occupied_memory array
                    occupied_memory_copy.pop_back();
                    
                    // in case left out data add it back to the end, it should retain the same id
                    if (dif != 0)
                        occupied_memory_copy.push_back(dif);
                        
                    // decrement empty_memory_space
                
                    empty_memory_space = 0;
                }
                
            }
            
            if (empty_memory_space == 0)
                id_free_memory++;
        }
        
        state = 1 - state;
    }
    
    return rez;
}
