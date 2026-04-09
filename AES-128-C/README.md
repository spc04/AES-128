# AES-128-C

Pure C implementation of AES-128 encryption supporting multiple block cipher modes.

## Supported Modes
- ECB (Electronic Codebook)
- CBC (Cipher Block Chaining)
- CFB (Cipher Feedback)
- OFB (Output Feedback)

## Files
- `final_dec.c/h`: Core AES encryption/decryption functions
- `ecb.h`, `cbc.h`, `cfb.h`, `ofb.h`: Mode-specific implementations
- `*_file_enc.c`: Encryption utilities for each mode
- `*_file_dec.c`: Decryption utilities for each mode

## Usage
See the main README.md for compilation and usage instructions.

