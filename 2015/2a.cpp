#include <algorithm>
#include <array>
#include <iostream>
#include <string>

struct box
{
    int length;
    int width;
    int height;

    int surface() const;
    int smallest_side_area() const;
};

std::istream &operator>>(std::istream &stream, box &box);

int main()
{
    int wrapping_paper_area = 0;
    box box;    

    while (std::cin >> box)
    {
        wrapping_paper_area += box.surface() + box.smallest_side_area();
    }

    std::cout << wrapping_paper_area << std::endl;

    return 0;
}

std::istream &operator>>(std::istream &stream, box &box)
{
    char delimeter = 0;
    stream >> box.length >> delimeter >> box.width >> delimeter >> box.height;

    return stream; 
}

int box::surface() const
{
    return 2 * (width * length + width * height + height * length);
}

int box::smallest_side_area() const
{
    std::array<int, 3> dimensions{length, width, height};
    std::sort(dimensions.begin(), dimensions.end());

    return dimensions[0] * dimensions[1];
}
