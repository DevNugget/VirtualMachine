#include "vm.h"

void VirtualMachine::Execute() {
  uint8_t instruction;
  
  // Loop through the code until a HALT instruction is encountered
  for (ip = 0; (instruction = code[ip]) != HALT; ip++) {
    
    //std::cout << "IP: " << (int32_t)ip << '\n'<< "Inst: " << (uint32_t)instruction << '\n';

    // Depending on the instruction encountered, execute a certain action
    switch (instruction) {
      case PUSH:
      {
        // Increment the instruction pointer to point to the argument of PUSH,
        // then push the argument onto the stack
        stack.push_back(code[++ip]);
        break;
      }
      
      case POP:
      {
        if (stack.empty()) {
          std::cerr << "Error: No elements in stack to perform POP instruction." << std::endl;
          break;
        }
        stack.pop_back();
        break;
      }

      case ADD:
      {
        if (stack.size() < 2) {
          std::cerr << "Error: Not enough elements in stack for ADD instruction." << '\n';
          break;
        }
        int8_t a = stack.back();
        stack.pop_back();
        int8_t b = stack.back();
        stack.pop_back();
        stack.push_back(a + b);
        break;
      }

      case SUB:
      {
        if (stack.size() < 2) {
          std::cerr << "Error: Not enough elements in stack for SUB instruction." << '\n';
          break;
        }
        int8_t b = stack.back();
        stack.pop_back();
        int8_t a = stack.back();
        stack.pop_back();
        stack.push_back(a - b);
        break;
      }

      case MUL:
      {
        if (stack.size() < 2) {
          std::cerr << "Error: Not enough elements in stack for MUL instruction." << '\n';
          break;
        }
        int8_t a = stack.back();
        stack.pop_back();
        int8_t b = stack.back();
        stack.pop_back();
        stack.push_back(a * b);
        break;
      }

      case DIV:
      {
        if (stack.size() < 2) {
          std::cerr << "Error: Not enough elements in stack for DIV instruction." << '\n';
          break;
        }
        int8_t b = stack.back();
        stack.pop_back();
        int8_t a = stack.back();
        stack.pop_back();
        stack.push_back(a / b);
        break;
      }

      case SWAP:
      {
        if (stack.size() < 2) {
          std::cerr << "Error: Not enough elements in stack for SWAP instruction." << '\n';
          break;
        }
        int8_t a = stack.back();
        stack.pop_back();
        int8_t b = stack.back();
        stack.pop_back();
        stack.push_back(b);
        stack.push_back(a);
        break;
      }

      case DUP:
      {
        if (stack.empty()) {
          std::cerr << "Error: No value on stack to duplicate (DUP instruction)." << '\n';
          break;
        }
        stack.push_back(stack.back());
        break;
      }

      case JMP:
      {
        int8_t address = code[++ip];
        //std::cout << "JMP ADDRESS: " << (uint32_t)address << '\n';
        ip = address - 1;
        break;
      }

      case OUT_I8:
      {
        std::cout << (int32_t)stack.back() << '\n';
        stack.pop_back();
        break;
      }

      case CMP:
      {
        int8_t b = stack.back();
        stack.pop_back();
        int8_t a = stack.back();
        stack.pop_back();

        if (a == b) {
          stack.push_back(EQUAL);
        } else if (a != b) {
          stack.push_back(NEQUAL);
        } else if (a < b) {
          stack.push_back(LOWER);
        } else if (a > b) {
          stack.push_back(GREATER);
        }
        break;
      }

      case JE:
      {
        CheckedJump(EQUAL); 
        break;
      }

      case JNE:
      {
        CheckedJump(NEQUAL);
        break;
      }

      case JG:
      {
        CheckedJump(GREATER);
        break;
      }

      case JL:
      {
        CheckedJump(LOWER);
        break;
      }
    }
  }
}

void VirtualMachine::CheckedJump(int8_t condition) {
  int8_t address = code[++ip];

  if (stack.back() == condition) {
    stack.pop_back();
    ip = address - 1;
  }
}
