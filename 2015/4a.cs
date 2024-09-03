using System;
using System.Linq;
using System.Security.Cryptography;
using System.Text;

namespace AdventOfCode;

public class Program
{
    public static void Main(string[] args)
    {
        if (!args.Any())
        {
            Console.WriteLine("Secret prefix required.");
            return;
        }

        string secret = args.First();

        for (uint i = 0; i < uint.MaxValue; ++i)
        {
            byte[] bytes = Encoding.UTF8.GetBytes($"{secret}{i}");
            byte[] hashedBytes = MD5.HashData(bytes);
            string encodedText = Convert.ToHexString(hashedBytes);

            if (encodedText.StartsWith("00000"))
            {
                Console.WriteLine(i);
                return;
            }
        }

        Console.WriteLine("Not found.");
    }
}
