# AES-128-Intrin

Optimized AES-128 implementation using Intel AES-NI intrinsics for hardware-accelerated encryption.

## Features
- Uses AES-NI instructions for high performance
- Key expansion, encryption, and decryption operations
- Requires CPU with AES-NI support

## Compilation
```bash
gcc -o intrin aes_intrin.c -maes -msse4.1
```

## Usage
See the main README.md for details.

