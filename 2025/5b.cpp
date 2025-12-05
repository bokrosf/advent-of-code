#include <algorithm>
#include <iostream>
#include <istream>
#include <list>
#include <optional>
#include <sstream>

using id_type = ulong;

struct id_range
{
    id_type from;
    id_type to;

    id_type length() const;
    bool precedes(const id_range &other) const;
    bool overlaps(const id_range &other) const;
    id_range unite_with(const id_range &other) const;
};

using range_iterator = std::list<id_range>::const_iterator;

struct insertion_point
{
    std::optional<range_iterator> preceded;
    std::optional<range_iterator> begin_overlapped;
    std::optional<range_iterator> end_overlapped;
};

std::list<id_range> read_ranges(std::istream &input);
insertion_point find_insertion_point(const std::list<id_range> &ranges, const id_range &r);
size_t available_id_count(const std::list<id_range> &ranges);

int main()
{
    auto ranges = read_ranges(std::cin);
    std::cout << available_id_count(ranges) << std::endl;

    return 0;
}

std::list<id_range> read_ranges(std::istream &input)
{
    std::list<id_range> ranges;
    std::string line;

    while (std::getline(std::cin, line) && line.length() > 0)
    {
        std::istringstream s(line);
        const char delimeter = '-';
        id_range r;
        s >> r.from;
        s.ignore(1, delimeter);
        s >> r.to;

        auto point = find_insertion_point(ranges, r);

        if (point.preceded.has_value())
        {
            ranges.insert(*point.preceded, r);
        }
        else if (point.begin_overlapped)
        {
            r = r.unite_with(**point.begin_overlapped).unite_with(*(--*point.end_overlapped));
            ranges.insert(*point.begin_overlapped, r);
            ranges.erase(*point.begin_overlapped, ++*point.end_overlapped);
        }
        else
        {
            ranges.push_back(r);
        }
    }

    return ranges;
}

insertion_point find_insertion_point(const std::list<id_range> &ranges, const id_range &r)
{
    for (auto it = ranges.begin(); it != ranges.end(); ++it)
    {
        if (r.precedes(*it))
        {
            return insertion_point{.preceded = it};
        }
        else if (r.overlaps(*it))
        {
            insertion_point point
            {
                .begin_overlapped = it,
                .end_overlapped = ++it
            };

            while (*point.end_overlapped != ranges.end() && r.overlaps(**point.end_overlapped))
            {
                ++*point.end_overlapped;
            }

            return point;
        }
    }

    return insertion_point();
}

size_t available_id_count(const std::list<id_range> &ranges)
{
    size_t sum = 0;

    for (auto &r : ranges)
    {
        sum += r.to - r.from + 1;
    }

    return sum;
}

id_type id_range::length() const
{
    return to - from + 1;
}

bool id_range::precedes(const id_range &other) const
{
    return to < other.from;
}

bool id_range::overlaps(const id_range &other) const
{
    id_range overlapped = unite_with(other);

    return overlapped.length() < length() + other.length();
}

id_range id_range::unite_with(const id_range &other) const
{
    return id_range
    {
        .from = std::min(from, other.from),
        .to = std::max(to, other.to)
    };
}
