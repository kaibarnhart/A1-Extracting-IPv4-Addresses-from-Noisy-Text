/*
 * Name: Kai Barnhart
 * Course: EECS 677
 * Assignment: IPv4 Address Parser
 * Date: September 27, 2026
 *
 * Description:
 * This program reads a line of text and searches for one valid IPv4
 * address with an optional port number. It validates each complete
 * candidate token and manually converts all numeric values without
 * using built-in string-to-number conversion functions.
 *
 * Source: ChatGPT was used to help generate and review parts of the
 * parsing and validation logic.
 */

#include <iostream>
#include <string>

using namespace std;

// ChatGPT helped with this helper function.
// Checks whether a character can be part of an IPv4 candidate.
bool isTokenChar(char c)
{
    return (c >= '0' && c <= '9') || c == '.' || c == ':';
}

// ChatGPT helped generate and review this parsing function.
// It manually builds a number from individual digit characters.
bool parseNumber(const string& token, size_t& pos,
                 int maxDigits, unsigned long maxValue,
                 unsigned long& value)
{
    value = 0;

    // Must begin with a digit.
    if (pos >= token.length() ||
        token[pos] < '0' || token[pos] > '9')
    {
        return false;
    }

    size_t start = pos;
    int digitCount = 0;

    // Leading zero is only allowed when the number is exactly 0.
    if (token[pos] == '0')
    {
        pos++;

        if (pos < token.length() &&
            token[pos] >= '0' && token[pos] <= '9')
        {
            return false;
        }

        value = 0;
        return true;
    }

    // Build the number one digit at a time.
    while (pos < token.length() &&
           token[pos] >= '0' && token[pos] <= '9')
    {
        digitCount++;

        if (digitCount > maxDigits)
        {
            return false;
        }

        value = value * 10 + (token[pos] - '0');

        if (value > maxValue)
        {
            return false;
        }

        pos++;
    }

    return pos > start;
}

// ChatGPT helped generate and review the IPv4 and port validation.
bool validateToken(const string& token,
                   unsigned long& address,
                   int& port)
{
    size_t pos = 0;
    unsigned long octets[4];

    // Read exactly four octets.
    for (int i = 0; i < 4; i++)
    {
        if (!parseNumber(token, pos, 3, 255, octets[i]))
        {
            return false;
        }

        // First three octets must be followed by periods.
        if (i < 3)
        {
            if (pos >= token.length() || token[pos] != '.')
            {
                return false;
            }

            pos++;
        }
    }

    port = -1;

    // Check for an optional port after the fourth octet.
    if (pos < token.length())
    {
        if (token[pos] != ':')
        {
            return false;
        }

        pos++;

        unsigned long portValue;

        if (!parseNumber(token, pos, 5, 65535, portValue))
        {
            return false;
        }

        port = static_cast<int>(portValue);
    }

    // Reject the token if anything remains after the address/port.
    if (pos != token.length())
    {
        return false;
    }

    // ChatGPT helped with combining the octets into one 32-bit value.
    address =
        (octets[0] << 24) |
        (octets[1] << 16) |
        (octets[2] << 8) |
        octets[3];

    return true;
}

// ChatGPT helped generate and review the candidate scanning logic.
bool extractIPv4(const string& str,
                 unsigned long& outAddress,
                 int& outPort)
{
    outAddress = 0;
    outPort = -1;

    size_t i = 0;

    // Search through the entire line.
    while (i < str.length())
    {
        // Skip characters that cannot be part of an address.
        if (!isTokenChar(str[i]))
        {
            i++;
            continue;
        }

        size_t start = i;

        // Read the complete candidate token.
        while (i < str.length() && isTokenChar(str[i]))
        {
            i++;
        }

        string token = str.substr(start, i - start);

        unsigned long address;
        int port;

        // Validate the complete token.
        if (validateToken(token, address, port))
        {
            outAddress = address;
            outPort = port;
            return true;
        }
    }

    return false;
}

int main()
{
    string input;

    // Keep asking for input until END is entered.
    while (true)
    {
        cout << "Enter a string (or 'END' to quit): ";
        getline(cin, input);

        if (input == "END")
        {
            cout << "Program terminated." << endl;
            break;
        }

        unsigned long address = 0;
        int port = -1;

        if (extractIPv4(input, address, port))
        {
            // Convert the 32-bit value back into four octets for output.
            unsigned long a = (address >> 24) & 255;
            unsigned long b = (address >> 16) & 255;
            unsigned long c = (address >> 8) & 255;
            unsigned long d = address & 255;

            cout << "Extracted IPv4 address: "
                 << a << "."
                 << b << "."
                 << c << "."
                 << d
                 << " (decimal value: "
                 << address
                 << ", port: ";

            if (port == -1)
            {
                cout << "none";
            }
            else
            {
                cout << port;
            }

            cout << ")" << endl;
        }
        else
        {
            cout << "Invalid input: no valid IPv4 address found" << endl;
        }
    }

    return 0;
}