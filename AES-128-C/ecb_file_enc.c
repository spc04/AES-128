#include <stdio.h>
#include <math.h>
#include<stdint.h>


#include "final_dec.h"
#include "ecb.h"


void main () {

	unsigned char key[16], m[5000];
	int ch=0, bl;


	FILE *inputFile = fopen("text.txt", "r"); // To read the input file.
    	if (inputFile == NULL) {
        	printf("Error: Unable to open input file.\n");
   	}

	for (int i=0; i<16; i++) {		// Scanning the key from the first line.
		fscanf(inputFile, "%02hhx ", &key[i]);
		}
	fscanf(inputFile, "\n\n\n");

	int len=0;	// This variable will gradually count the length of the plaintext.
	while ((ch = fgetc(inputFile)) != EOF) {
		m[len] = (unsigned char) ch;
		len+=1;
	}	

	fclose(inputFile);
	
	// Now, "len" holds the plaintext length.
	int flag=0,s;
	while ((len%16)!=0) {
		s=16-(len%16);
		for (int i=0; i<s; i++) m[len+i] = s;
		flag = 1;
		break;
	}		
	
	while (flag==0) {
		s=16;
		for (int i=0; i<s; i++) m[len+i] = 0x10;
		break;
		} // These two "while" loops are used to apply proper padding (PKCS#7).
	
	len = len+s; // Text length after padding.


	bl = len/16; // Number of Blocks.
	
	
	Word result[44];
	
	KeyExpansion(key, 10, result);
	
	unsigned char c[len];
	
	ECB_Enc(m, bl, result, c);
	
	
	
	FILE* outputFile = fopen("ecb_cipher.txt", "w"); // To write the Ciphertext into a new file.
		if (outputFile == NULL) {
        		printf("Error: Unable to open output file.\n");
    		}

	fprintf(outputFile, "The Encrypted Message is (using ECB mode with AES-128 Encryption) :-");
	
	fprintf(outputFile, "\n\n");
	
	for (int i=0; i<len; i++) fprintf(outputFile, "%c", (char)c[i]);

	fclose(outputFile);
}

