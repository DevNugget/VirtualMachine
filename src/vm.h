#ifndef VM_H
#define VM_H

#include <vector>
#include <iostream>

// Instructions
#define HALT   0x00
#define PUSH   0x01
#define POP    0x02
#define ADD    0x03
#define SUB    0x04
#define MUL    0x05
#define DIV    0x06
#define SWAP   0x07
#define DUP    0x08
#define JMP    0x09
#define OUT_I8 0x0A
#define CMP    0x0B
#define JE     0x0C
#define JNE    0x0D
#define JG     0x0E
#define JL     0x0F

// Comparison results
#define EQUAL  -1
#define NEQUAL  0
#define GREATER 1
#define LOWER   2

class VirtualMachine {
  public:
  int8_t ip;
  std::vector<int8_t> stack;
  std::vector<uint8_t> code;

  void Execute();
  void CheckedJump(int8_t condition);
};

#endif
