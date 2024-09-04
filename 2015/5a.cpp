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
        std::string vowel = "[aeiou]";
        std::string letter_duplication = "(.)\\1";
        std::string forbidden_words = "ab|cd|pq|xy";

        if (count_matches(text, vowel) >= 3 
            && count_matches(text, letter_duplication) >= 1
            && count_matches(text, forbidden_words) == 0)
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
