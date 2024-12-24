#ifndef CLAW_GAME_HPP
#define CLAW_GAME_HPP

#ifndef OVERHEAD
#define OVERHEAD 10000000000000ULL
#endif

#include <string>
#include <optional>

class ClawGame {

private:
    std::pair<unsigned long long, unsigned long long> m_a_button_move;
    std::pair<unsigned long long, unsigned long long> m_b_button_move;
    std::pair<unsigned long long, unsigned long long> m_prize_location;
    
    const std::pair<unsigned long long, unsigned long long> extract_button_move(const std::string& line);
    const std::pair<unsigned long long, unsigned long long> extract_prize_location(const std::string& line);
    
    const std::optional<std::pair<unsigned long long, unsigned long long>> 
        try_solve_equation_maximization(unsigned long long a, unsigned long long b, unsigned long long rez);
    
public:
    ClawGame(const std::string& a, const std::string& b, const std::string& prize);
    
    const std::optional<unsigned long long> brute_force_best_combination();
    
    const std::optional<unsigned long long> get_best_combination();
};

#endif // CLAW_GAME_HPP