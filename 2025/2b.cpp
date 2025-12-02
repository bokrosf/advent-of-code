#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

std::string read_until(std::istream &input, char separator);
long sum_invalid_ids(long from, long to);
bool repeating_sequence(std::string_view id);

int main()
{
    long invalid_id_sum = 0;

    while (std::cin)
    {
        long from = std::atol(read_until(std::cin, '-').c_str());
        long to = std::atol(read_until(std::cin, ',').c_str());
        invalid_id_sum += sum_invalid_ids(from, to);
    }

    std::cout << invalid_id_sum << std::endl;

    return 0;
}

std::string read_until(std::istream &input, char separator)
{
    char read = 0;
    std::ostringstream sequence;

    while (input >> read && read != separator)
    {
        sequence << read;
    }

    return sequence.str();
}

long sum_invalid_ids(long from, long to)
{
    long sum = 0;

    for (long number = from; number <= to; ++number)
    {
        std::string text = std::to_string(number);
        sum += repeating_sequence(text) ? number : 0;
    }

    return sum;
}

bool repeating_sequence(std::string_view id)
{
    bool found = false;

    for (size_t parts = 2; !found && parts <= id.length(); ++parts)
    {
        if (id.length() % parts != 0)
        {
            continue;
        }

        size_t sequence_length = id.length() / parts;
        bool repeating = true;
        
        for (size_t i = 1; repeating && i < parts; ++i)
        {
            std::string_view start(
                id.begin(),
                id.begin() + sequence_length);

            std::string_view current(
                id.begin() + (i * sequence_length),
                id.begin() + ((i + 1) * sequence_length));

            repeating &= start == current;
        }

        found |= repeating;
    }

    return found;
}
