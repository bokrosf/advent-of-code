#include <fstream>
#include <iostream>

int main()
{
    std::ifstream input("input.txt");
    int floor = 0;
    int position = 0;

    while (!input.eof() && floor != -1)
    {
        char instruction = 0;
        input >> instruction;

        switch (instruction)
        {
            case '(':
                ++floor;
                break;
            case ')':
                --floor;
                break;
        }

        ++position;
    }

    std::cout << position << std::endl;

    return 0;
}
