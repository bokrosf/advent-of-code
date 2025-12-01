#include <cmath>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <string_view>

const int dial_range = 100;

int line_to_rotation(std::string_view line)
{
    int sign = 1;

    switch (line[0])
    {
        case 'L':
            sign = -1;
            break;
        case 'R':
            sign = 1;
            break;
    }

    line.remove_prefix(1);

    return sign * std::atoi(line.data());
}

int rotate(int dial, int amount)
{
    amount %= dial_range;

    return (dial_range + dial + amount) % dial_range;
}

int main()
{
    int dial = 50;
    int dial_reached_zero_count = 0;
    std::ifstream input("input");
    std::string line;

    while (input >> line)
    {
        int rotation = line_to_rotation(line);
        dial_reached_zero_count += std::abs(rotation) / dial_range;
        int new_dial = rotate(dial, rotation);

        if (dial != 0 && new_dial != 0)
        {
            dial_reached_zero_count += (rotation > 0 && new_dial < dial);
            dial_reached_zero_count += (rotation < 0 && new_dial > dial);
        }

        dial = new_dial;
        dial_reached_zero_count += dial == 0;
    }

    std::cout << dial_reached_zero_count << std::endl;

    return 0;
}
