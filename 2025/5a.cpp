#include <algorithm>
#include <iostream>
#include <istream>
#include <sstream>
#include <vector>

using id_type = ulong;

struct id_range
{
    id_type from;
    id_type to;
};

std::vector<id_range> read_ranges(std::istream &input);
size_t fresh_food_count(std::istream &ids, const std::vector<id_range> &ranges);

int main()
{
    auto ranges = read_ranges(std::cin);
    std::cout << fresh_food_count(std::cin, ranges) << std::endl;

    return 0;
}

std::vector<id_range> read_ranges(std::istream &input)
{
    std::vector<id_range> ranges;
    std::string line;

    while (std::getline(std::cin, line) && line.length() > 0)
    {
        std::istringstream s(line);
        const char delimeter = '-';
        id_range r;
        s >> r.from;
        s.ignore(1, delimeter);
        s >> r.to;
        ranges.push_back(r);
    }

    return ranges;
}

size_t fresh_food_count(std::istream &ids, const std::vector<id_range> &ranges)
{
    size_t count = 0;
    id_type id;

    while (ids >> id)
    {
        auto inside_interval = [id](const id_range &r)
        {
            return id >= r.from && id <= r.to;
        };

        count += std::ranges::any_of(ranges, inside_interval);
    }

    return count;
}
