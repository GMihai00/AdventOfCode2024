#include "Equation.hpp"

#include <regex>

long long concat_integers(long long left, long long right) {
    
    long long rez = left;
    
    auto str_int = std::to_string(right);
    
    for (const auto& chr : str_int) {
        rez = rez * 10 + chr - '0';
    }
    
    return rez;
}

const bool Equation::backtrack_valid(const std::vector<char>& valid_operations, std::stack<char>& ops, const long long current_value)
{
    if (ops.size() == m_variables.size() - 1)
        return current_value == m_result;
    
    if (current_value > m_result)
        return false;
        
    for (const auto& op : valid_operations) {
        ops.push(op);
        long long value;
        if (op == '*') {
            
            value = current_value * m_variables[ops.size()];
            
        } else if (op == '+') {
            
            value = current_value + m_variables[ops.size()];
            
        } else if (op == '|') {
            
            value = concat_integers(current_value, m_variables[ops.size()]);
        }
        
        if (backtrack_valid(valid_operations, ops, value))
            return true;
        
        ops.pop();
    }
    
    return false;
}

Equation::Equation(std::string line)
{
    std::regex pattern(R"(^(\d+):((?: \d+)+)$)");
    
    std::smatch match;
    
    if (std::regex_match(line, match, pattern)) {
        
        {
            std::istringstream iss(match[1]);
            iss >> m_result;
        }
        
        {
            std::istringstream iss(match[2]);
            int value;
            while (iss >> value) {
                m_variables.push_back(value);
            }
        }
        
    } else {
        throw std::runtime_error("Invalid input:" + line);
    }
}

const long long Equation::get_result()
{
    return m_result;
}

const bool Equation::can_become_valid()
{
    std::stack<char> ops;
    return backtrack_valid(m_operations, ops, m_variables[0]);
}

const bool Equation::can_become_valid_second()
{
    std::stack<char> ops;
    return backtrack_valid(m_operations_second, ops, m_variables[0]);
}