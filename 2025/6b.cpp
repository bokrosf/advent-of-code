#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <sstream>

using number_type = ulong;

const char operation_addition = '+';
const char operation_multiplication = '*';

int main()
{
    number_type sum = 0;
    std::map<size_t, std::ostringstream> number_sequences;
    std::map<size_t, char> operations;
    std::string line;

    // Reading input and storing in a computation friendly way.
    while (std::getline(std::cin, line) && line.length())
    {
        for (int i = line.length() - 1; i >= 0; --i)
        {
            if (line[i] >= '0' && line[i] <= '9')
            {
                number_sequences[i] << line[i];
            }
            else if (line[i] == operation_addition || line[i] == operation_multiplication)
            {
                operations[i] = line[i];
            }
        }
    }

    // Computing the result from right to left.
    auto number_it = number_sequences.rbegin();

    for (auto op_it = operations.rbegin(); op_it != operations.rend(); ++op_it)
    {
        number_type operation_result = op_it->second == operation_multiplication ? 1 : 0;

        while (number_it != number_sequences.rend() && number_it->first >= op_it->first)
        {
            number_type operand = std::strtoul(number_it->second.str().data(), nullptr, 10);

            if (op_it->second == operation_addition)
            {
                operation_result += operand;
            }
            else if (op_it->second == operation_multiplication)
            {
                operation_result *= operand;
            }

            ++number_it;
        }

        sum += operation_result;
    }

    std::cout << sum << std::endl;

    return 0;
}
