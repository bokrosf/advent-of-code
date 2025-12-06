#include <algorithm>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/types.h>
#include <vector>

const char operation_addition = '+';
const char operation_multiplication = '*';

using number_type = ulong;

struct problem
{
    char operation;
    std::vector<number_type> numbers;
};

std::vector<problem> read_problems(std::istream &input);

int main()
{
    auto problems = read_problems(std::cin);
    number_type sum = 0;

    for (auto &p : problems)
    {
        if (p.operation == operation_addition)
        {
            sum += std::ranges::fold_left(p.numbers, 0, std::plus<number_type>());
        }
        else if (p.operation == operation_multiplication)
        {
            sum += std::ranges::fold_left(p.numbers, 1, std::multiplies<number_type>());
        }
    }

    std::cout << sum << std::endl;

    return 0;
}

std::vector<problem> read_problems(std::istream &input)
{
    std::string line;
    std::getline(input, line);
    std::istringstream line_stream(line);
    std::vector<problem> problems;
    number_type number;

    while (line_stream >> number)
    {
        problem p;
        p.numbers.push_back(number);
        problems.push_back(p);
    }

    while (std::getline(input, line))
    {
        std::istringstream line_stream(line);
        auto problem = problems.begin();

        switch (line[0])
        {
            case operation_addition:
            case operation_multiplication:
                char operation;

                while (line_stream >> operation)
                {
                    problem->operation = operation;
                    ++problem;
                }
                break;
            default:
                while (line_stream >> number)
                {
                    problem->numbers.push_back(number);
                    ++problem;
                }
                break;
        }
    }

    return problems;
}
