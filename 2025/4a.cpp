#include <cstddef>
#include <iostream>
#include <new>
#include <stddef.h>
#include <string>
#include <string_view>

const char paper = 1;
const char movable_adjacent_count = 4;

struct buffer
{
    char *current;
    char *next;
    size_t width;
};

void fill_buffer(char buffer[], std::string_view arrangement_line);
void count_neighbours(char &a, char &b);
size_t accessible_paper_count(char row[], size_t width);

int main()
{
    std::string line;
    std::cin >> line;
    buffer buffer;
    buffer.width = line.length();
    buffer.current = new char[buffer.width];
    buffer.next = new char[buffer.width];
    fill_buffer(buffer.current, line);
    size_t accessible_paper_sum = 0;

    while (std::cin >> line && line.length() > 0)
    {
        fill_buffer(buffer.next, line);

        for (size_t i = 1; i < buffer.width; ++i)
        {
            count_neighbours(buffer.current[i], buffer.current[i - 1]);
            count_neighbours(buffer.current[i], buffer.next[i - 1]);
            count_neighbours(buffer.current[i - 1], buffer.next[i]);
        }

        for (size_t i = 0; i < buffer.width; ++i)
        {
            count_neighbours(buffer.current[i], buffer.next[i]);
        }

        accessible_paper_sum += accessible_paper_count(buffer.current, buffer.width);

        for (size_t i = 0; i < line.length(); ++i)
        {
            buffer.current[i] = buffer.next[i];
        }
    }

    for (size_t i = 1; i < buffer.width; ++i)
    {
        count_neighbours(buffer.current[i], buffer.current[i - 1]);
    }

    accessible_paper_sum += accessible_paper_count(buffer.current, buffer.width);
    std::cout << accessible_paper_sum << std::endl;

    return 0;
}

void fill_buffer(char buffer[], std::string_view arrangement_line)
{
    char rolls_of_paper = '@';

    for (size_t i = 0; i < arrangement_line.length(); ++i)
    {
        buffer[i] = arrangement_line[i] == rolls_of_paper ? paper : 0;
    }
}

void count_neighbours(char &a, char &b)
{
    if (a >= paper && b >= paper)
    {
        ++a;
        ++b;
    }
}

size_t accessible_paper_count(char row[], size_t width)
{
    size_t count = 0;

    for (size_t i = 0; i < width; ++i)
    {
        if (row[i] >= paper && row[i] <= movable_adjacent_count)
        {
            ++count;
        }
    }

    return count;
}
