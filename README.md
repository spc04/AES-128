# AES-128 Implementations

This repository contains two implementations of the AES-128 encryption algorithm:

1. **AES-128-C**: A pure C implementation supporting multiple block cipher modes (ECB, CBC, CFB, OFB).
2. **AES-128-Intrin**: An optimized implementation using Intel AES-NI intrinsics for hardware-accelerated encryption.

## Features

### AES-128-C
- Pure C implementation without external dependencies
- Supports the following modes of operation:
  - ECB (Electronic Codebook)
  - CBC (Cipher Block Chaining)
  - CFB (Cipher Feedback)
  - OFB (Output Feedback)
- File encryption and decryption utilities for each mode
- PKCS#7 padding support

### AES-128-Intrin
- Uses Intel AES-NI instructions for high performance
- Hardware-accelerated key expansion, encryption, and decryption
- Requires a CPU with AES-NI support

## Usage

### AES-128-C

Each mode has separate encryption and decryption programs. The programs read from `text.txt` and write output to mode-specific files.

#### Input Format
The first line of `text.txt` should contain the 128-bit key in hexadecimal format (32 hex characters):
```
0123456789abcdef0123456789abcdef
```

The remaining content is the plaintext to encrypt.

#### Compilation
```bash
gcc -o ecb_enc ecb_file_enc.c final_dec.c
gcc -o ecb_dec ecb_file_dec.c final_dec.c
# Similarly for other modes
```

#### Running
```bash
./ecb_enc    # Encrypts using ECB mode, outputs to ecb_cipher.txt
./ecb_dec    # Decrypts using ECB mode, outputs to ecb_plain.txt
```

### AES-128-Intrin

#### Compilation
```bash
gcc -o intrin aes_intrin.c -maes -msse4.1
```

#### Running
```bash
./intrin
```

## Requirements

- GCC compiler
- For AES-128-Intrin: CPU with AES-NI support and GCC with AES intrinsics

## File Structure

```
AES-128-main/
├── README.md
├── AES-128-C/
│   ├── README.md
│   ├── final_dec.c      # Core AES functions
│   ├── final_dec.h      # AES headers and utilities
│   ├── ecb.h            # ECB mode implementation
│   ├── ecb_file_enc.c   # ECB encryption utility
│   ├── ecb_file_dec.c   # ECB decryption utility
│   ├── cbc.h            # CBC mode implementation
│   ├── cbc_file_enc.c   # CBC encryption utility
│   ├── cbc_file_dec.c   # CBC decryption utility
│   ├── cfb.h            # CFB mode implementation
│   ├── cfb_file_enc.c   # CFB encryption utility
│   ├── cfb_file_dec.c   # CFB decryption utility
│   ├── ofb.h            # OFB mode implementation
│   ├── ofb_file_enc.c   # OFB encryption utility
│   ├── ofb_file_dec.c   # OFB decryption utility
│   └── text.txt         # Sample input file
└── AES-128-Intrin/
    ├── README.md
    └── aes_intrin.c     # Intel intrinsics implementation
```

## Security Note

This implementation is for educational purposes. For production use, consider using established cryptographic libraries like OpenSSL.
