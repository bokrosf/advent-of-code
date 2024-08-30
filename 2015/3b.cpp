#include <array>
#include <iostream>
#include <unordered_map>

struct vector2
{
    int x;
    int y;

    vector2();
    vector2(int x, int y);
    bool operator==(const vector2 &rhs) const;
    vector2 &operator+=(const vector2 &rhs);
};

template <>
struct std::hash<vector2>
{
    size_t operator()(const vector2 &vector) const;
};

vector2 direction_signal_to_vector(char direction);

int main()
{
    std::unordered_map<vector2, size_t> visits;
    std::array<vector2, 2> courier_positions{vector2(), vector2()};
    visits[courier_positions[0]] = 2;
    char direction = 0;
    size_t courier_index = 0;

    while (std::cin >> direction)
    {
        courier_positions[courier_index] += direction_signal_to_vector(direction);
        ++visits[courier_positions[courier_index]];
        courier_index = (courier_index + 1) % courier_positions.size();
    }

    std::cout << visits.size() << std::endl;

    return 0;
}

vector2::vector2()
    : vector2(0, 0)
{
}

vector2::vector2(int x, int y)
    : x(x)
    , y(y)
{
}

bool vector2::operator==(const vector2 &rhs) const
{
    return x == rhs.x && y == rhs.y;
}

vector2 &vector2::operator+=(const vector2 &rhs)
{
    x += rhs.x;
    y += rhs.y;

    return *this;
}

size_t std::hash<vector2>::operator()(const vector2 &vector) const
{
    size_t hash = std::hash<int>()(vector.x);
    hash *= hash;
    
    return hash + std::hash<int>()(vector.y);
}

vector2 direction_signal_to_vector(char direction)
{
    switch (direction)
    {
        case '^':
            return vector2(0, 1);
        case 'v':
            return vector2(0, -1);
        case '>':
            return vector2(1, 0);
        case '<':
            return vector2(-1, 0);
        default:
            throw "UnkownDirection";
    }
}
