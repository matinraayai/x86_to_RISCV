# x86_to_RISCV
An x86 to RISC-V JIT Binary Translator

# Setup

```bash
git clone --recurse-submodules https://github.com/matinraayai/x86_to_RISCV/
cd x86_to_RISCV/zydis
git checkout master
cd dependencies/zycore
git submodule init && git submodule update
```

# Usage
```bash
./main "path-to-program"
```
