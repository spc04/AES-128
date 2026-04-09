#include <stdio.h>
#include <math.h>
#include<stdint.h>


#include "final_dec.h"
#include "ecb.h"

void main () {

	unsigned char key[16] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c}; // Key is known to the receiver.
	unsigned char c[5000];
	int ch=0, bl;
	
	
	FILE *cipherFile = fopen("ecb_cipher.txt", "r"); // Opening the ciphertext file and scanning the encrypted text.
    	if (cipherFile == NULL) {
        	printf("Error: Unable to open input file.\n");
   	}
	
	fscanf(cipherFile, "The Encrypted Message is (using ECB mode with AES-128 Encryption) :-\n\n");
	
	int len=0;
	while ((ch = fgetc(cipherFile)) != EOF) {
		c[len] = (unsigned char) ch;
		len+=1;
	}	
	
	fclose(cipherFile);
	
	bl = len/16; // The padded and encrypted text will always have length as a multiple of 16.
	
	Word result[44];
	
	KeyExpansion(key, 10, result);
	
	unsigned char m1[len];
	
	ECB_Dec(c, bl, result, m1);
	
	int val = 0x10, flag=0;
	while (m1[len-1] != val) {
		len = len - m1[len-1];
		flag=1;
		break;
		}
	
	while (flag==0) {
		len = len - val;
		break;
		} // To discard the padding after decrypting.
	
	
	FILE *plaintextFile = fopen("ecb_decrypt.txt", "w"); // To write the retrieved plaintext into a new file.
		if (plaintextFile == NULL) {
        		printf("Error: Unable to open output file.\n");
    		}

	fprintf(plaintextFile, "The Decrypted Message is :-");
	
	fprintf(plaintextFile, "\n\n");
	
	for (int i=0; i<len; i++) fprintf(plaintextFile, "%c", (char)m1[i]);

	fclose(plaintextFile);

	
	
	
	
}
