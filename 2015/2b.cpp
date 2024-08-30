#include <algorithm>
#include <array>
#include <iostream>
#include <string>

struct box
{
    int length;
    int width;
    int height;

    int volume() const;
    int smallest_perimeter() const;
};

std::istream &operator>>(std::istream &stream, box &box);

int main()
{
    int ribbon_length = 0;
    box box;    

    while (std::cin >> box)
    {
        ribbon_length += box.volume() + box.smallest_perimeter();
    }

    std::cout << ribbon_length << std::endl;

    return 0;
}

std::istream &operator>>(std::istream &stream, box &box)
{
    char delimeter = 0;
    stream >> box.length >> delimeter >> box.width >> delimeter >> box.height;

    return stream; 
}

int box::volume() const
{
    return width * height * length;
}

int box::smallest_perimeter() const
{
    std::array<int, 3> dimensions{length, width, height};
    std::sort(dimensions.begin(), dimensions.end());

    return 2 * (dimensions[0] + dimensions[1]);
}
