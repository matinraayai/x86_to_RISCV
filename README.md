# x86_to_RISCV
An x86 to RISC-V JIT Binary Translator

# Setup

## Cloning the Repository
```bash
git clone --recurse-submodules https://github.com/matinraayai/x86_to_RISCV/
cd x86_to_RISCV/zydis
git checkout master
cd dependencies/zycore
git submodule init && git submodule update
```
Note: If encountered an "unsupported distribution" error from Zydis' header, 
simply go to Defines.h file located at zydis/dependencies/zycore/include/Zycore 
and make the header define ZYAN_X64 regardless of the target ISA and 
comment out the 'error "Unsupported architecture detected"'.

## Building the emulator for RISC-V
This has been tested on Ubuntu 18.04 LTS. For installation on other distros 
please visit each project's repository.
0. Dependencies:
```bash
sudo apt-get install autoconf automake autotools-dev curl libmpc-dev \
libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf \
libtool patchutils bc zlib1g-dev libexpat-dev make gcc g++ cmake
```
1. Build the RISC-V Toolchain and set it up in your path:
```
git clone --recursive https://github.com/riscv/riscv-gnu-toolchain
# You can change prefix to any other directory without space in its name.
./configure --prefix=/opt/riscv
sudo make -j $(nproc) linux
# export variables
export PATH="$PATH:/opt/riscv64/bin"
export RISCV="/opt/riscv64"
```
2. Build the translator's binary: 
```bash
cd build_riscv/
cmake .
make
```
3. Build the guest's binary:
```bash
cd build_x86/
cmake .
make
```

# Running the Emulator on AMD64 Using the riscv64-unknown-linux-gnu-run Tool from the RISC-V Toolchain:
```bash
riscv64-unknown-linux-gnu-run ./build_riscv/main_riscv ./build_x86/fibonacci
```
