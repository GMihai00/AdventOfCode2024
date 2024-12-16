#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <algorithm>

std::ofstream out("../data.out");

long long get_nr_occurrences(const std::string& text) {

    long long rez = 0;
        
    {
        std::regex pattern(R"(XMAS)");
        for (std::sregex_iterator it(text.begin(), text.end(), pattern), end; it != end; ++it) {
            rez++;
        }
    }
    
    {
        std::regex pattern(R"(SAMX)");
        for (std::sregex_iterator it(text.begin(), text.end(), pattern), end; it != end; ++it) {
            rez++;
        }
    }
    
    return rez;
}

long long get_count_horizontal(const std::vector<std::string>& text) {

    long long rez = 0;
    for (const auto& line : text) {
        rez += get_nr_occurrences(line);
    }
    
    std::cout << __func__ << ": " <<  rez << std::endl;
    
    return rez;
}

long long get_count_vertical(const std::vector<std::string>& text) {

    long long rez = 0;
    for (int j = 0; j < text[0].size(); j++){
        std::string line = "";
        for (int i = 0; i < text.size(); i++) {
            line.push_back(text[i][j]);
        }
        rez += get_nr_occurrences(line);
    }
    
    std::cout << __func__ << ": " <<  rez << std::endl;
    
    return rez;
}

long long get_count_second_diagonal(const std::vector<std::string>& text) {

    long long rez = 0;
    
    // [10][0]
    // [9][1]
    // [8][2]
    // [7][3]
    // [6][4]
    // [5][5]
    // [4][6]
    // [3][7]
    // [2][8]
    // [1][9]
    // [0][10]
    
    // second diagonal
    
    {  
        std::string line = "";
        for (int i = text.size() - 1; i >= 0; i--) {
        
            line.push_back(text[i][text.size() - 1  - i]);
        }
        rez += get_nr_occurrences(line);
    }
    
    
    // [0][0]
    
    // [1][0]
    // [0][1]
    
    
    // [2][0]
    // [1][1]
    // [0][2]
    // ...
    
    // [10][8]
    // [9][9]
    // [8][10]
    
    // [10][9]
    // [9][10]
    
    // [10][10]
    
    // above and below the second diagonal
    
    for (int it = 0; it < text.size() - 1; it++){
        
        std::string line_above = "";
        std::string line_below = "";
        
        for (int i = it; i >= 0; i--) {
            line_above.push_back(text[i][it - i]);
            
            // std::cout << i << "-" << it - i << " ";
            
            line_below.push_back(text[text.size() - 1 - (it - i)][text.size() - 1 - i]);
            
            // std::cout << text.size() - 1 - (it - i) << "-" << text.size() - 1 - i << " ";
        }
        
        rez += get_nr_occurrences(line_above);
        rez += get_nr_occurrences(line_below);
    }
    
    std::cout << __func__ << ": " <<  rez << std::endl;
        
    return rez;
    
}

long long get_count_first_diagonal(const std::vector<std::string>& text) {
    
    // [0][9]
    
    // [0][8]
    // [1][9]
    
    // [0][7]
    // [1][8]
    // [2][9]
    
    // [0][6]
    // [1][7]
    // [2][8]
    // [3][9]
    
    
    // [0][5]
    // [1][6]
    // [2][7]
    // [3][8]
    // [4][9]
    
    // [0][4]
    // [1][5]
    //
    
    // ...
    
    // [0][0]
    // [1][1]
    // [2][2]
    // [3][3]
    // ...
    
    // [8][0]
    // [9][1]
    
    // [9][0]
    
    long long rez = 0;
        
    // first diagonal
    {
        std::string line = "";
        for (int i = 0; i < text.size(); i++)
        {
            line.push_back(text[i][i]);
        }
        rez += get_nr_occurrences(line);
    }
    
    // above and below the first diagonal
    
    for (int it = 0; it < text.size() - 1; it++){
    
        std::string line_above = "";
        std::string line_below = "";
        
        for (int i = 0; i <= it; i++) {
            line_above.push_back(text[i][text.size() - 1 - it + i]);
            line_below.push_back(text[text.size() - 1 - it + i][i]);
        }
        
        rez += get_nr_occurrences(line_above);
        rez += get_nr_occurrences(line_below);
    }
    
    std::cout << __func__ << ": " <<  rez << std::endl;
    
    return rez;
}

void solve_first(const std::vector<std::string>& text) {

    long long rez = get_count_horizontal(text) + 
        get_count_vertical(text) +
        get_count_first_diagonal(text) + 
        get_count_second_diagonal(text);
        
    out << "First: " << rez << std::endl;
}

std::string get3by3_first_diagonal(const std::vector<std::string>& text, int i, int j) {
    
    std::string line = "";
    
    for (int it = 2; it >= 0; it--)
        line.push_back(text[i + it][j + 2 - it]);
    
    return line;
}

std::string get3by3_second_diagonal(const std::vector<std::string>& text, int i, int j) {
    std::string line = "";
    
    for (int it = 0; it < 3; it++)
        line.push_back(text[i + it][j + it]);
    
    return line;
}

void solve_second(const std::vector<std::string>& text) {

    long long rez = 0;
    
    for (int i = 0; i < text.size() - 2; i++)
    {
        for (int j = 0; j < text[i].size() - 2; j++)
        {
            std::string second_diagonal = get3by3_second_diagonal(text, i, j);
            std::string first_diagonal = get3by3_first_diagonal(text, i, j);
            
            if (second_diagonal == "MAS" || second_diagonal == "SAM")
            {
                if (first_diagonal == "MAS" || first_diagonal == "SAM")
                    rez++;
            }
        }
    }
        
    out << "Second: " << rez << std::endl;
}

int main() {

    std::ifstream in("../data.in");
    
    if (!in.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return 1;
    }
    
    std::string line;
    
    std::vector<std::string> text;
    
    while(std::getline(in, line)) {
        text.push_back(line);
    }
    
    // solve_first(text);
    
    solve_second(text);
}