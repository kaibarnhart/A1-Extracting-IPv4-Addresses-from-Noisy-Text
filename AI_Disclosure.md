# AI Disclosure

I used ChatGPT by OpenAI, GPT-5.6 Sol, on September 26 and September 27, 2026.

## How I Used AI

I used ChatGPT to help generate and review parts of my C++ program. ChatGPT helped with the token scanning logic, manual number parsing, IPv4 validation, port validation, combining the four octets into one 32-bit value, and creating test cases.

## Prompts Used

One of the prompts I used was:

"Write a C++ solution for my IPv4 parsing assignment. I need to implement bool extractIPv4(const std::string& str, unsigned long& outAddress, int& outPort). The program should scan text for a valid IPv4 address with an optional port. It must validate the whole candidate token and manually convert digits without using stoi, atoi, sscanf, regex, or IP parsing libraries."

I also asked ChatGPT to review the code for edge cases such as leading zeros, invalid octets, invalid ports, extra periods, extra colons, missing octets, and partial matches.

I later asked ChatGPT to help create additional test cases.

## Modifications and Review

I reviewed the AI-generated code and tested it myself. I added comments, added a header at the top of the source file, and tested the code with both the sample inputs and extra edge cases.

I specifically checked cases like:

- `192.168.1.1.`
- `192.168.01.1`
- `256.1.1.1`
- `1.2.3.4:65535`
- `1.2.3.4:65536`
- `1.2.3.4:080`
- `1.2..3.4`
- `1.2.3.4:80:90`

## Verification Statement

I understand the code I am submitting and reviewed how each function works.

I tested the program and it works as intended for the required sample cases and the additional test cases I created.

I am not currently aware of any unresolved bugs or limitations.