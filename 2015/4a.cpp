#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>

std::string md5_hash(const std::string &text);

int main()
{
    // NOT COMPLETED md5_hash returns incorrect hash string.
    std::string secret = "";
    std::cout << md5_hash(secret) << std::endl;

    return 0;
}

uint32_t f_trans(uint32_t x, uint32_t y, uint32_t z)
{
    return (x & y) | (~x & z);
}

uint32_t g_trans(uint32_t x, uint32_t y, uint32_t z)
{
    return (x & z) | (y & ~z);
}

uint32_t h_trans(uint32_t x, uint32_t y, uint32_t z)
{
    return x ^ y ^ z;
}

uint32_t i_trans(uint32_t x, uint32_t y, uint32_t z)
{
    return y ^ (x | ~z);
}

typedef uint32_t (*word_hasher)(uint32_t x, uint32_t y, uint32_t z);

uint32_t round_shift(uint32_t value, uint32_t bit_number)
{
    return (value << bit_number) | (value >> (32 - bit_number));
}

void operation(
    uint32_t &a, 
    uint32_t b, 
    uint32_t c, 
    uint32_t d, 
    uint32_t k, 
    uint32_t s, 
    uint32_t i,
    uint32_t x[],
    uint32_t t[],
    std::function<uint32_t(uint32_t, uint32_t, uint32_t)> word_hasher)
{
    uint32_t shifted = round_shift(a + word_hasher(b, c, d) + x[k] + t[i], s);
    a = b + shifted;
}

void print_binary(uint8_t number)
{
    while (number > 0)
    {
        std::cout << (number & 1);
        number >>= 1;
    }
}

std::string md5_hash(const std::string &text)
{
    const uint64_t padding_max_length = 512 / 8;
    uint64_t padding_length = padding_max_length - (text.size() % padding_max_length);
    
    uint8_t *buffer = reinterpret_cast<uint8_t *>(std::calloc(1, text.size() + padding_length));
    std::memcpy(buffer, text.c_str(), text.length());
    buffer[text.length()] = 1;
    uint64_t *length_part = reinterpret_cast<uint64_t *>(buffer + text.length() + padding_length - 64);
    *length_part = text.length();

    uint32_t a = 0x67452301;
    uint32_t b = 0xefcdab89;
    uint32_t c = 0x98badcfe;
    uint32_t d = 0x10325476;
    uint32_t t[64];

    for (int i = 0; i < 64; ++i)
    {
        t[i] = 4294967296 * std::abs(std::sin(i + 1));
    }

    for (int i = 0; i < (text.length() + padding_length) / (4 * 16); ++i)
    {
        uint32_t x[16];
        uint32_t *sub_buffer = reinterpret_cast<uint32_t *>(buffer + i * 16);

        for (int j = 0; j < 16; ++j)
        {
            x[j] = sub_buffer[j];
        }

        uint32_t a_original = a;
        uint32_t b_original = b;
        uint32_t c_original = c;
        uint32_t d_original = d;

        // Round 0.
        for (uint32_t i = 0; i < 4; ++i)
        {
            uint32_t block_index = i * 4;
            operation(a, b, c, d, block_index, 7, block_index, x, t, f_trans);
            operation(d, a, b, c, block_index + 1, 12, block_index + 1, x, t, f_trans);
            operation(c, d, a, b, block_index + 2, 17, block_index + 2, x, t, f_trans);
            operation(b, c, d, a, block_index + 3, 22, block_index + 3, x, t, f_trans);
        }

        // Round 1.
        uint32_t k_start = 1;
        uint32_t k_step = 5;
        uint32_t round = 1;
        
        auto evaluate_k = [k_start, k_step](uint32_t index)
        {
            return (k_start + (index * k_step)) % 16;
        };

        auto evaluate_t_index = [&t, round](uint32_t iteration, uint32_t index)
        {
            return (round * 16) + (iteration * 4) + index;
        };

        for (uint32_t i = 0; i < 4; ++i)
        {
            operation(a, b, c, d, evaluate_k(0), 5, evaluate_t_index(i, 0), x, t, g_trans);
            operation(d, a, b, c, evaluate_k(1), 9, evaluate_t_index(i, 1), x, t, g_trans);
            operation(c, d, a, b, evaluate_k(2), 14, evaluate_t_index(i, 2), x, t, g_trans);
            operation(b, c, d, a, evaluate_k(3), 20, evaluate_t_index(i, 3), x, t, g_trans);
            k_start = evaluate_k(4);
        }

        // Round 2.
        k_start = 5;
        k_step = 3;
        ++round;

        for (uint32_t i = 0; i < 4; ++i)
        {
            operation(a, b, c, d, evaluate_k(0), 4, evaluate_t_index(i, 0), x, t, h_trans);
            operation(d, a, b, c, evaluate_k(1), 11, evaluate_t_index(i, 1), x, t, h_trans);
            operation(c, d, a, b, evaluate_k(2), 16, evaluate_t_index(i, 2), x, t, h_trans);
            operation(b, c, d, a, evaluate_k(3), 23, evaluate_t_index(i, 3), x, t, h_trans);
            k_start = evaluate_k(4);
        }

        // Round 4.
        k_start = 0;
        k_step = 7;
        ++round;

        for (uint32_t i = 0; i < 4; ++i)
        {
            operation(a, b, c, d, evaluate_k(0), 6, evaluate_t_index(i, 0), x, t, i_trans);
            operation(d, a, b, c, evaluate_k(1), 10, evaluate_t_index(i, 1), x, t, i_trans);
            operation(c, d, a, b, evaluate_k(2), 15, evaluate_t_index(i, 2), x, t, i_trans);
            operation(b, c, d, a, evaluate_k(3), 21, evaluate_t_index(i, 3), x, t, i_trans);
            k_start = evaluate_k(4);
        }

        a += a_original;
        b += b_original;
        c += c_original;
        d += d_original;
    }

    std::free(buffer);
    std::stringstream encoded_text;
    encoded_text << std::hex << a;
    
    return encoded_text.str();
}
