#include <iostream>
#include <fstream>
#include <vector>


bool is_safe(std::vector<long long> levels, int left, int right) {
    
    if (right - left + 1 < 2) {
        return true;
    }
    
    bool asc_desc = levels[left + 1] > levels[left];
        
    for (int i = left; i < right - 1; i++) {
    
        long long dif = abs(levels[i] - levels[i + 1]);
        
        if (!(dif >= 1 && dif <= 3  )) {
            return false;
        }
        
        if (!((levels[i + 1] > levels[i]) == asc_desc)) {
            return false;
        }
    }
    
    return true;  
}

bool check_if_combination_safe(std::vector<long long> levels, int left, int right, bool asc_desc) {
    long long dif = abs(levels[left] - levels[right]);
    if (!(dif >= 1 && dif <= 3)) {
        
        return false;
    }
    
    if (!((levels[right] > levels[left]) == asc_desc)) {
        
        return false;
    }
    
    return true;
}

bool check_for_poz_i_removed(std::vector<long long> levels, int poz) {

    std::vector<long long> levels_copy;
        
    for (int i = 0; i < levels.size(); i++)
        if (i != poz) 
            levels_copy.push_back(levels[i]);
    
    return is_safe(levels_copy, 0, levels_copy.size());
}

// brute force 
// bool is_safe_using_adapter_raw(std::vector<long long> levels) {
    
//     if (is_safe(levels, 0, levels.size()))
//         return true;
    
//     for (int i = 0; i < levels.size(); i++) {
//         if (check_for_poz_i_removed(levels, i))
//             return true;
//     }
    
//     return false;
// }


bool is_safe_using_adapter(std::vector<long long> levels) {
    if (levels.size() < 2) {
        return true;
    }
    
    // 1st element removed case
    
    if (is_safe(levels, 1, levels.size()))
        return true;
    
    // 2nd element removed case
    {
        std::vector<long long> levels_copy;
        
        for (int i = 0; i < levels.size(); i++)
            if (i != 1) 
                levels_copy.push_back(levels[i]);
        
        if (is_safe(levels_copy, 0, levels_copy.size()))
            return true;
    }
        

    // last element removed case
    if (is_safe(levels, 0, levels.size() - 1))
        return true;
        
    // remove any element
    bool asc_desc = levels[1] > levels[0];
    
    int left = 0;
    int right = 1;
    
    for (int i = 0; i < levels.size(); i++){
        
        if (!check_if_combination_safe(levels, i, i + 1, asc_desc))
        {
            if (check_for_poz_i_removed(levels, i) || check_for_poz_i_removed(levels, i + 1))
                return true;
            
            return false;
        }
    }
    
    return true;
}

int main() {
    
    std::ifstream in("../data.in");
    if (!in.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return 1;
    }
    
    std::ofstream out("../data.out");
    
    std::string line;
    
    long long safe_reports = 0;
    long long safe_reports_adaptor = 0;
    
    while(std::getline(in, line)) {
    
        long long nr = 0; 
        
        std::vector<long long> levels;
        levels.clear();
        
        for (auto & chr : line) {
            if (chr <= '9' && chr >= '0') {
                nr = nr * 10 + chr - '0';
            }
            else {
                levels.push_back(nr);
                nr = 0;
            }
        }
        
        if (nr != 0) {
            levels.push_back(nr);
        }
        
        if (levels.size() < 2) {
            safe_reports++;
            safe_reports_adaptor++;
            continue;
        }
        
        safe_reports_adaptor += (is_safe_using_adapter(levels) == true);

        if (levels[0] == levels[1]){
            continue;
        }
        
        safe_reports += (is_safe(levels, 0, levels.size()) == true);
        
    }
    
    out << "First. Safe reports: " << safe_reports << std::endl;
    out << "Second. Safe reports: " << safe_reports_adaptor << std::endl;
    
    return 0;
}