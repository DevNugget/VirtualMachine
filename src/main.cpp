#include <iostream>
#include <iomanip>

#include "vm.h"
#include "file_reader.h"

VirtualMachine vm;

int main(int argc, char *argv[]) {
  std::string readable = "-bReadable";
  std::string binary = "-bBin";

  if (argv[1] == readable) {
    ConvBytesToName(argv[2]);
  } else if (argv[1] == binary) {
    std::vector<unsigned char> bytecode = InstructionToBytecode(argv[2]);
    for (auto b : bytecode) {
      std::cout << "0x" << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(b) << ' ';
    }
    std::cout << '\n';
  } else {
    vm.code = ReadBytes(argv[1]);
    vm.Execute();
  }
}
