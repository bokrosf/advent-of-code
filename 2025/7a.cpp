#include <iostream>
#include <string>
#include <utility>

const char beam_entry = 'S';
const char splitter = '^';
const char beam = '|';

int main()
{
    std::string previous;
    std::string current;
    std::getline(std::cin, previous);
    size_t position = previous.find(beam_entry);
    previous[position] = beam;
    size_t beam_split_count = 0;

    while (std::getline(std::cin, current) && current.length())
    {
        position = previous.find(beam, 0);

        while (position < previous.length() && position != std::string::npos)
        {
            if (current[position] == splitter)
            {
                ++beam_split_count;

                if (position >= 1)
                {
                    current[position - 1] = beam;
                }

                if (position <= (current.length() - 2))
                {
                    current[position + 1] = beam;
                }
            }
            else
            {
                current[position] = beam;
            }

            position = previous.find(beam, position + 1);
        }

        std::swap(previous, current);
    }

    std::cout << beam_split_count << std::endl;

    return 0;
}
