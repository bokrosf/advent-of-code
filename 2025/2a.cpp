#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

std::string read_until(std::istream &input, char separator);
long sum_invalid_ids(long from, long to);

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

        if (text.length() % 2 == 0)
        {
            long half_length = text.length() / 2;
            long i = 0;

            while (i < half_length && text[i] == text[i + half_length])
            {
                ++i;
            }

            sum += (i == half_length) ? number : 0;
        }
    }

    return sum;
}
