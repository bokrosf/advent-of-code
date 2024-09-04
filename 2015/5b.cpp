#include <iostream>
#include <regex>
#include <string>

int count_matches(const std::string &text, const std::string &pattern);

int main()
{
    int nice_string_count = 0;
    std::string text;

    while (std::cin >> text)
    {
        std::string pair_of_two = "(.)(.).*\\1\\2";
        std::string repeat_around_one = "(.).\\1";

        if (count_matches(text, pair_of_two) >= 1 && count_matches(text, repeat_around_one) >= 1)
        {
            ++nice_string_count;
        }
    }

    std::cout << nice_string_count << std::endl;
    
    return 0;
}

int count_matches(const std::string &text, const std::string &pattern)
{
    std::string checked_text = text;
    std::basic_regex regex(pattern);
    std::smatch match;
    int count = 0;

    while (std::regex_search(checked_text, match, regex))
    {
        checked_text = match.suffix().str();
        ++count;
    }

    return count;
}
