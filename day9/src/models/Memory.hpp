#include <vector>
#include <string>
class Memory {

private:
    std::vector<unsigned long long> m_occupied_disk;
    std::vector<unsigned long long> m_free_space;

    void build_disk_space(const std::string& data);
    
    std::pair<std::vector<unsigned long long>, std::vector<unsigned long long>> determine_starting_positions_intervals();
public:
    Memory(const std::string& data);
    
    const unsigned long long get_checksum_first();
    
    const unsigned long long get_checksum_second();
};