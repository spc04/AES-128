#include "final_dec.h"

void ECB_Enc (unsigned char *m, int bl, Word result[], unsigned char *c) {
	
	unsigned char mTemp[16], cTemp[16];
	
	for (int i=0; i<bl; i++) {
		for (int j=0; j<16; j++) mTemp[j] = m[(16*i)+j];
		Cipher(mTemp, 10, result, cTemp);
		for (int j=0; j<16; j++) c[(16*i)+j] = cTemp[j];
		}
	}

void ECB_Dec (unsigned char *c, int bl, Word result[], unsigned char *m1) {
	
	unsigned char cTemp[16], m1Temp[16];
	
	for (int i=0; i<bl; i++) {
		for (int j=0; j<16; j++) cTemp[j] = c[(16*i)+j];
		InvCipher(cTemp, 10, result, m1Temp);
		for (int j=0; j<16; j++) m1[(16*i)+j] = m1Temp[j];
		}
	
	}

