#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

long largest_joltage(std::string_view battery_bank);

int main()
{
    std::string line;
    long joltage_sum = 0;

    while (std::cin >> line && line != "")
    {
        joltage_sum += largest_joltage(line);
    }

    std::cout << joltage_sum << std::endl;


    return 0;
}

long largest_joltage(std::string_view battery_bank)
{
    std::ostringstream joltage_text;
    auto begin = battery_bank.begin();
    auto end = battery_bank.end() - 11;

    while (end <= battery_bank.end())
    {
        auto max = std::max_element(begin, end);
        joltage_text << *max;
        begin = max + 1;
        ++end;
    }

    return std::atol(joltage_text.str().data());
}
