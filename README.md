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
## Building the emulator for RISC-V
This has been tested on Ubuntu 18.04 LTS. For installation on other distros 
please visit each project's repository.
0. Dependencies:
```bash
sudo apt-get install autoconf automake autotools-dev curl libmpc-dev \
libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf \
libtool patchutils bc zlib1g-dev libexpat-dev make gcc g++
```
1. Build the RISC-V Toolchain and set it up in your path:
```
git clone --recursive https://github.com/riscv/riscv-gnu-toolchain
# You can change prefix to any other directory without space in its name.
./configure --prefix=/opt/riscv --enable-multilib
sudo make -j $(nproc) linux
# export variables
export PATH="$PATH:/opt/riscv64/bin"
export RISCV="/opt/riscv64"
```
2. 

# Running the emulator on QEMU emulated BusyBear Linux:
0. Dependencies:

1. Build QEMU for RISC-V emulation:
```bash
git clone https://github.com/qemu/qemu
./configure --target-list=riscv64-softmmu,riscv32-softmmu
make -j $(nproc)
sudo make install
```
2. Download BusyBear Linux:
```bash
wget https://github.com/michaeljclark/busybear-linux/releases/download/v1.0/busybear.bin.bz2
wget https://github.com/michaeljclark/busybear-linux/releases/download/v1.0/bbl.bz2
bzip2 -dk bbl.bz2
bzip2 -dk busybear.bin.bz2
```


# Usage
```bash
./main "path-to-program"
```
