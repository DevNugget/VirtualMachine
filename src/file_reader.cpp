#include "file_reader.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <unordered_map>

std::vector<uint8_t> ReadBytes(const std::string& filename) {
  std::vector<uint8_t> bytecode;

    std::ifstream input(filename);
    if (!input) {
        std::cerr << "Error: Failed to open input file " << filename << '\n';
        return {};
    }

    std::string byte;
    while (input >> byte) {
        if (byte.size() < 4 || byte.substr(0, 2) != "0x") {
            std::cerr << "Error: Invalid byte format " << byte << '\n';
            return {};
        }

        uint8_t opcode = std::stoi(byte.substr(2), nullptr, 16);
        bytecode.push_back(opcode);
    }

    return bytecode;
}

void ConvBytesToName(const std::string& fname) {
    std::ifstream input(fname);
    if (!input) {
        std::cerr << "Error: Failed to open input file " << fname << '\n';
        return;
    }

    std::string byte;
    while (input >> byte) {
        if (byte.size() < 4 || byte.substr(0, 2) != "0x") {
            std::cerr << "Error: Invalid byte format " << byte << '\n';
            return;
        }

        uint8_t opcode = std::stoi(byte.substr(2), nullptr, 16);
        //std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(opcode) << ' ';

        switch (opcode) {
            case 0x00: std::cout << "HALT" << '\n'; break;
            case 0x01: {
                std::cout << "PUSH";
                std::string arg;
                if (input >> arg) {
                    if (arg.size() < 4 || arg.substr(0, 2) != "0x") {
                        std::cerr << "Error: Invalid argument format " << arg << '\n';
                        return;
                    }
                    uint8_t argval = std::stoi(arg.substr(2), nullptr, 16);
                    std::cout << " " << std::hex << static_cast<int>(argval) << '\n';
                }
                break;
            }
            case 0x02: std::cout << "POP" << '\n'; break;
            case 0x03: std::cout << "ADD" << '\n'; break;
            case 0x04: std::cout << "SUB" << '\n'; break;
            case 0x05: std::cout << "MUL" << '\n'; break;
            case 0x06: std::cout << "DIV" << '\n'; break;
            case 0x07: std::cout << "SWAP" << '\n'; break;
            case 0x08: std::cout << "DUP" << '\n'; break;
            case 0x09: {
                std::cout << "JMP";
                std::string arg;
                if (input >> arg) {
                    if (arg.size() < 4 || arg.substr(0, 2) != "0x") {
                        std::cerr << "Error: Invalid argument format " << arg << '\n';
                        return;
                    }
                    uint8_t argval = std::stoi(arg.substr(2), nullptr, 16);
                    std::cout << " " << std::hex << static_cast<int>(argval) << '\n';
                }
                break;
            }
            case 0x0a: std::cout << "OUT_I8" << '\n'; break;
            case 0x0b: std::cout << "CMP" << '\n'; break;
            case 0x0c: {
                std::cout << "JE";
                std::string arg;
                if (input >> arg) {
                    if (arg.size() < 4 || arg.substr(0, 2) != "0x") {
                        std::cerr << "Error: Invalid argument format " << arg << '\n';
                        return;
                    }
                    uint8_t argval = std::stoi(arg.substr(2), nullptr, 16);
                    std::cout << " " << std::hex << static_cast<int>(argval) << '\n';
                }
                break;
            }
            case 0x0d: {
                std::cout << "JNE";
                std::string arg;
                if (input >> arg) {
                    if (arg.size() < 4 || arg.substr(0, 2) != "0x") {
                        std::cerr << "Error: Invalid argument format " << arg << '\n';
                        return;
                    }
                    uint8_t argval = std::stoi(arg.substr(2), nullptr, 16);
                    std::cout << " " << std::hex << static_cast<int>(argval) << '\n';
                }
                break;
            }
            case 0x0e: {
                std::cout << "JG";
                std::string arg;
                if (input >> arg) {
                    if (arg.size() < 4 || arg.substr(0, 2) != "0x") {
                        std::cerr << "Error: Invalid argument format " << arg << '\n';
                        return;
                    }
                    uint8_t argval = std::stoi(arg.substr(2), nullptr, 16);
                    std::cout << " " << std::hex << static_cast<int>(argval) << '\n';
                }
                break;
            }
            case 0x0f: {
                std::cout << "JL";
                std::string arg;
                if (input >> arg) {
                    if (arg.size() < 4 || arg.substr(0, 2) != "0x") {
                        std::cerr << "Error: Invalid argument format " << arg << '\n';
                        return;
                    }
                    uint8_t argval = std::stoi(arg.substr(2), nullptr, 16);
                    std::cout << " " << std::hex << static_cast<int>(argval) << '\n';
                }
                break;
            }
        }
    }
}

std::vector<uint8_t> InstructionToBytecode(const std::string& filename) {
    std::unordered_map<std::string, unsigned char> opcode_map = {
      {"HALT",   0x00},
      {"PUSH",   0x01},
      {"POP",    0x02},
      {"ADD",    0x03},
      {"SUB",    0x04},
      {"MUL",    0x05},
      {"DIV",    0x06},
      {"SWAP",   0x07},
      {"DUP",    0x08},
      {"JMP",    0x09},
      {"OUT_I8", 0x0a},
      {"CMP",    0x0b},
      {"JE",     0x0c},
      {"JNE",    0x0d},
      {"JG",     0x0e},
      {"JL",     0x0f},
    };

    std::vector<uint8_t> bytecode;

    std::ifstream file(filename); // Open the file
    std::vector<std::string> instr_vec; // Create a vector to store the words
    std::string inst;

    while (file >> inst) { // Read each word from the file
        instr_vec.push_back(inst); // Add the word to the vector
    }

    file.close(); // Close the file

    for (const std::string& instr : instr_vec) {
        // Check if the instruction is a decimal number
        if (isdigit(instr[0])) {
            // Convert decimal number to hexadecimal
            int dec_num = stoi(instr);
            std::stringstream stream;
            stream << "0x" << std::hex << dec_num;
            std::string hex_num = stream.str();

            // Add the hexadecimal number to the bytecode vector
            bytecode.push_back(stoul(hex_num, nullptr, 0));
        }
        else {
            // Get the instruction code from the opcode map
            uint8_t opcode = opcode_map.at(instr);

            // Add the opcode to the bytecode vector
            bytecode.push_back(opcode);
        }
    }

    return bytecode;
}




