#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include<stdint.h>
#include <time.h>

#include "final_dec.h"
#include "cbc.h"


void main () {

	unsigned char key[16], m[5000];
	int ch=0, bl;


	FILE *inputFile = fopen("text.txt", "r");
    	if (inputFile == NULL) {
        	printf("Error: Unable to open input file.\n");
   	}

	for (int i=0; i<16; i++) {
		fscanf(inputFile, "%02hhx ", &key[i]);
		}
	fscanf(inputFile, "\n\n\n");

	int len=0;
	while ((ch = fgetc(inputFile)) != EOF) {
		m[len] = (unsigned char) ch;
		len+=1;
	}	

	fclose(inputFile);
	
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
		}
	
	len = len+s;


	bl = len/16;
	
	
	Word result[44];
	
	KeyExpansion(key, 10, result);
	
	unsigned char c[len];
	
	unsigned char IV[16];
	
	srand(time(0)); // Seed the Random Number Generator for IV.
	
	for (int i=0; i<16; i++) {
        	IV[i] = (unsigned char)(rand() % 256);
    		}
	
	
	CBC_Enc(IV, m, bl, result, c);
	
	
	
	FILE* outputFile = fopen("cbc_cipher.txt", "w");
		if (outputFile == NULL) {
        		printf("Error: Unable to open output file.\n");
    		}

	fprintf(outputFile, "IV = ");
	
	for (int i=0;i<16;i++) fprintf(outputFile, "%02x ", IV[i]); // Putting the IV value in the first line (before the ciphertext).
	
	fprintf(outputFile, "\n\nThe Encrypted Message is (using CBC mode with AES-128 Encryption) :-");
	
	fprintf(outputFile, "\n\n");
	
	for (int i=0; i<len; i++) fprintf(outputFile, "%c", (char)c[i]);

	fclose(outputFile);
}

