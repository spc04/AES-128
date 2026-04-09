#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<stdint.h>
#include <time.h>


#include "final_dec.h"
#include "cfb.h"

void main () {

	unsigned char key[16] = {0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
	unsigned char c[5000];
	int ch=0, bl;
	
	
	FILE *cipherFile = fopen("cfb_cipher.txt", "r");
    	if (cipherFile == NULL) {
        	printf("Error: Unable to open input file.\n");
   	}
	
	unsigned char IV[16];
	
	fscanf(cipherFile, "IV = ");
	
	for (int i=0;i<16;i++) fscanf(cipherFile, "%02hhx ", &IV[i]);
	
	fscanf(cipherFile, "\n\nThe Encrypted Message is (using CFB mode with AES-128 Encryption) :-\n\n");
	
	int len=0;
	while ((ch = fgetc(cipherFile)) != EOF) {
		c[len] = (unsigned char) ch;
		len+=1;
	}	
	
	fclose(cipherFile);
	
	bl = len/16;
	
	Word result[44];
	
	KeyExpansion(key, 10, result);
	
	unsigned char m1[len];
	
	CFB_Dec(IV, c, bl, result, m1);
	
	int val = 0x10, flag=0;
	while (m1[len-1] != val) {
		len = len - m1[len-1];
		flag=1;
		break;
		}
	
	while (flag==0) {
		len = len - val;
		break;
		}
	
	
	FILE *plaintextFile = fopen("cfb_decrypt.txt", "w");
		if (plaintextFile == NULL) {
        		printf("Error: Unable to open output file.\n");
    		}

	fprintf(plaintextFile, "The Decrypted Message is :-");
	
	fprintf(plaintextFile, "\n\n");
	
	for (int i=0; i<len; i++) fprintf(plaintextFile, "%c", (char)m1[i]);

	fclose(plaintextFile);

	
	
	
	
}
