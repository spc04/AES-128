#include "final_dec.h"

void CFB_Enc (unsigned char *IV, unsigned char *m, int bl, Word result[], unsigned char *c) {
	
	unsigned char yTemp[16], cTemp[16];
	
	Cipher(IV, 10, result, yTemp);
	for (int j=0; j<16; j++) cTemp[j] = yTemp[j] ^ m[j];
	for (int j=0; j<16; j++) c[j] = cTemp[j];
	
	for (int i=1; i<bl; i++) {
		Cipher(cTemp, 10, result, yTemp); 
		for (int j=0; j<16; j++) cTemp[j] = yTemp[j] ^ m[(16*i)+j];
		for (int j=0; j<16; j++) c[(16*i)+j] = cTemp[j];
		}
	}
	
void CFB_Dec (unsigned char *IV, unsigned char *c, int bl, Word result[], unsigned char *m) {
	
	unsigned char yTemp[16], cTemp[16];
	
	Cipher(IV, 10, result, yTemp);
	for (int j=0; j<16; j++) m[j] = yTemp[j] ^ c[j];
	for (int j=0; j<16; j++) cTemp[j] = c[j];
	
	for (int i=1; i<bl; i++) {
		Cipher(cTemp, 10, result, yTemp); 
		for (int j=0; j<16; j++) m[(16*i)+j] = yTemp[j] ^ c[(16*i)+j];
		for (int j=0; j<16; j++) cTemp[j] = c[(16*i)+j];
		}
	}
		
