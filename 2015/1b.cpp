#include <fstream>
#include <iostream>

int main()
{
    std::ifstream input("input.txt");
    int floor = 0;
    int position = 0;
    char instruction = 0;

    while (input >> instruction && floor != -1)
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

        ++position;
    }

    std::cout << position << std::endl;

    return 0;
}
