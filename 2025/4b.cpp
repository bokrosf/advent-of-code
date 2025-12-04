#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

const char empty_space = 0;
const char paper = 1;

void initialize_row(std::string &row);
void count_neighbours(char &a, char &b);
size_t remove_accessible_papers(std::string &row);

int main()
{
    // Reading input and transforming to numbers.
    std::vector<std::string> room;
    std::string line;

    while (std::cin >> line && line.length() > 0)
    {
        char rolls_of_paper = '@';

        for (char &c : line)
        {
            c = c == rolls_of_paper ? paper : empty_space;
        }

        room.push_back(line);
    }

    // Empty data for easier cycle implementation instead of
    // branching and code duplication.
    room.push_back(std::string(room.begin()->length(), empty_space));

    size_t removed_sum = 0;
    size_t room_width = room.begin()->length();
    bool removing = true;

    while (removing)
    {
        size_t removed = 0;

        for (size_t row = 0; row < room.size() - 1; ++row)
        {
            for (size_t column = 1; column < room_width; ++column)
            {
                count_neighbours(room[row][column], room[row][column - 1]);
                count_neighbours(room[row][column], room[row + 1][column - 1]);
                count_neighbours(room[row][column - 1], room[row + 1][column]);
            }

            for (size_t column = 0; column < room_width; ++column)
            {
                count_neighbours(room[row][column], room[row + 1][column]);
            }

            removed += remove_accessible_papers(room[row]);

            for (char &c : room[row])
            {
                if (c >= paper)
                {
                    c = paper;
                }
            }
        }

        removed_sum += removed;
        removing &= removed > 0;
    }

    std::cout << removed_sum << std::endl;

    return 0;
}

void count_neighbours(char &a, char &b)
{
    if (a >= paper && b >= paper)
    {
        ++a;
        ++b;
    }
}

size_t remove_accessible_papers(std::string &row)
{
    const char movable_adjacent_count = 4;
    size_t count = 0;

    for (char &c : row)
    {
        if (c >= paper && c <= movable_adjacent_count)
        {
            ++count;
            c = empty_space;
        }
    }

    return count;
}
