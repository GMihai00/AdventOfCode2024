#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

std::ifstream in("data.in");
std::ofstream out("data.out");


long long get_number_ocurencs(std::vector<long long> data, long long target) {

    auto lower = std::lower_bound(data.begin(), data.end(), target);
    auto upper = std::upper_bound(data.begin(), data.end(), target);
    
    if (lower != data.end() && *lower == target) {
        
        return upper - lower;
    }
    else {
        return 0;
    }

}

int main() {
    
    
    std::vector<long long> first_list;
    std::vector<long long> second_list;
    
    std::string line;
    
    while (std::getline(in, line)) {
    
        long long a, b;
        a = 0;
        b = 0;
        bool split_found = false;
        
        for (auto chr : line) {
            if (chr >= '0' && chr <= '9') {
                if (!split_found)
                    a = a * 10 + chr - '0';
                else 
                    b = b * 10 + chr - '0';
            }
            else {
                split_found = true;
            }
        }
        
        first_list.push_back(a);
        second_list.push_back(b);
        
    }
    
    std::sort(first_list.begin(), first_list.end());
    std::sort(second_list.begin(), second_list.end());
    
    
    long long dif = 0;
    
    for (int i = 0; i < first_list.size(); i++) {
    
        dif += abs(first_list[i] - second_list[i]);
    }
    
    out << "First: " << dif << std::endl;
    
    
    long long similarity = 0;
    
    for (int i = 0; i < first_list.size(); i++) {
        
        similarity += first_list[i] * get_number_ocurencs(second_list, first_list[i]);
        
    }
    
    out << "Second: " << similarity;
    
    return 0;
}