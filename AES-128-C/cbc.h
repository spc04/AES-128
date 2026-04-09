#include "final_dec.h"

void CBC_Enc (unsigned char *IV, unsigned char *m, int bl, Word result[], unsigned char *c) {
	
	unsigned char mTemp[16], cTemp[16];
	
	for (int j=0; j<16; j++) mTemp[j] = IV[j] ^ m[j];
	Cipher(mTemp, 10, result, cTemp);
	for (int j=0; j<16; j++) c[j] = cTemp[j];
	
	for (int i=1; i<bl; i++) {
		for (int j=0; j<16; j++) mTemp[j] = m[(16*i)+j] ^ cTemp[j];
		Cipher(mTemp, 10, result, cTemp);
		for (int j=0; j<16; j++) c[(16*i)+j] = cTemp[j];
		}
	}
	
void CBC_Dec (unsigned char *IV, unsigned char *c, int bl, Word result[], unsigned char *m1) {
	
	unsigned char cTemp[16], m1Temp[16];
	
	for (int j=0;j<16;j++) cTemp[j] = c[j];
	InvCipher(cTemp, 10, result, m1Temp);
	for (int j=0;j<16;j++) m1[j] = m1Temp[j] ^ IV[j];
	
	for (int i=1; i<bl; i++) {
		for (int j=0;j<16;j++) cTemp[j] = c[(16*i)+j];
		InvCipher(cTemp, 10, result, m1Temp);
		for (int j=0;j<16;j++) m1[(16*i)+j] = m1Temp[j] ^ c[(16*(i-1))+j];
		}
	}	
