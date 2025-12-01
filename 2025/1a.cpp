#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <string_view>

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
    const int dial_range = 100;

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
        dial = rotate(dial, rotation);

        if (dial == 0)
        {
            ++dial_reached_zero_count;
        }
    }

    std::cout << dial_reached_zero_count << std::endl;

    return 0;
}
