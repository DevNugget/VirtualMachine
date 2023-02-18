#ifndef FILE_READER_H
#define FILE_READER_H

#include <vector>
#include <string>

std::vector<uint8_t> ReadBytes(const std::string& filename);
void ConvBytesToName(const std::string& fname);
std::vector<uint8_t> InstructionToBytecode(const std::string& filename);

#endif
