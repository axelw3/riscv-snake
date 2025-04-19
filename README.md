# Snake

[![hqdefault](https://github.com/user-attachments/assets/a6206b47-23e2-4d08-9d09-f40df7e2a932)](https://www.youtube.com/watch?v=umetqKHsiI8)

An implementation of the classic Snake computer game in the C programming language. The project was written for the DTEK-V (DE10-Lite-based) board used in the IS1500 course at KTH. As inputs, the game digitally reads GPIO pins 0 through 3. Additionally, the button labelled `KEY1` is used for starting the game. The game is rendered to the on-board VGA controller.

Made by [axelw3](https://github.com/axelw3/) and Oskar W.

## Prerequisites
- A compatible board
- The [RISC-V GNU toolchain](https://github.com/riscv/riscv-gnu-toolchain) (32-bit, rv32gc+ilp32)
- The [Intel® Quartus® Prime Programmer and Tools](https://www.intel.com/content/www/us/en/software-kit/795187/intel-quartus-prime-lite-edition-design-software-version-23-1-for-linux.html) (we used 23.1std.0.991)

## Building
Compiling the code is simple:
```bash
make
```

Additional debugging functionality can be enabled by instead running `make wdebug`.

If you are using the DTEK-V board, the compiled binary can be uploaded using the `dtekv-run` utility (provided as part of the course materials) ([link](https://canvas.kth.se/courses/49299/files/8033111)):
```bash
dtekv-run ./main.bin
```
