#include <vector>
#include <string>
#include <stack>

class Equation {

private:
    long long m_result;
    std::vector<long long> m_variables;
    const std::vector<char> m_operations = {'*', '+'};
    const std::vector<char> m_operations_second = {'*', '+', '|'};
    
    const bool backtrack_valid(const std::vector<char>& valid_operations, std::stack<char>& ops, const long long current_value);
    
public:   
    Equation(std::string line);
    
    const long long get_result();
    
    const bool can_become_valid();
    
    const bool can_become_valid_second();
};
