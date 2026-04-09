#include "final_dec.h"

void OFB_Enc_Dec (unsigned char *IV, unsigned char *m, int bl, Word result[], unsigned char *c) {
	
	unsigned char yTemp[16], cTemp[16];
	
	Cipher(IV, 10, result, yTemp);
	for (int j=0; j<16; j++) c[j] = yTemp[j] ^ m[j];
	
	for (int i=1; i<bl; i++) {
		Cipher(yTemp, 10, result, cTemp); 
		for (int j=0; j<16; j++) c[(16*i)+j] = cTemp[j] ^ m[(16*i)+j];
		for (int j=0; j<16; j++) yTemp[j] = cTemp[j];
		}
	}
	
