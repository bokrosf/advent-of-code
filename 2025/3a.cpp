#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

int largest_joltage(std::string_view battery_bank);

int main()
{
    std::string line;
    int joltage_sum = 0;

    while (std::cin >> line && line.length() > 0)
    {
        joltage_sum += largest_joltage(line);
    }

    std::cout << joltage_sum << std::endl;


    return 0;
}

int largest_joltage(std::string_view battery_bank)
{
    std::ostringstream joltage_text;
    auto max = std::max_element(battery_bank.begin(), battery_bank.end() - 1);
    joltage_text << *max;
    max = std::max_element(max + 1, battery_bank.end());
    joltage_text << *max;

    return std::atoi(joltage_text.str().data());
}
