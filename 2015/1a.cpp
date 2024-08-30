#include <fstream>
#include <iostream>

int main()
{
    std::ifstream input("input.txt");
    int floor = 0;
    char instruction = 0;

    while (input >> instruction)
    {
        switch (instruction)
        {
            case '(':
                ++floor;
                break;
            case ')':
                --floor;
                break;
        }
    }

    std::cout << floor << std::endl;

    return 0;
}
