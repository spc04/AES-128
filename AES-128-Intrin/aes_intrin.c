// The following Code includes the KeyExpansion, Cipher and InvCipher operations of an AES-128 Encryption System using Intel Intrinsic Instructions.
// Compilation Instruction : gcc -o intrin aes_intrin.c -maes -msse4.1


#include <wmmintrin.h>
#include <emmintrin.h>
#include <smmintrin.h>
#include <stdio.h>
#include <stdint.h>


void printBytes(unsigned char *data, int num){ // To print a data with Big-Endian setting.
       
       printf("\n");
       for(int i=num-1; i>=0; i--)
               printf("%02x ", data[i]);
       printf("\n");
}

void printBytesRev(unsigned char *data, int num){ // To print a data with Little-Endian setting.
       
       printf("\n");
       for(int i=0; i<num; i++)
               printf("%02x ", data[i]);
       printf("\n");
}


void KeyExpansion (unsigned char *k, __m128i *RES, __m128i *IMC_RES) {
	
	__m128i TEMP;
	
	RES[0] = _mm_loadu_si128((__m128i*)k);
	IMC_RES[0] = RES[0];
	
	
	
	TEMP = _mm_aeskeygenassist_si128 (RES[0], 0x01);	
	TEMP = _mm_srli_si128(TEMP, 12);
	TEMP = _mm_xor_si128(RES[0], TEMP);
	RES[1] = _mm_set_epi32(0, 0, 0, _mm_extract_epi32(TEMP, 0));
	
	TEMP = _mm_slli_si128(RES[1], 4);
	TEMP = _mm_xor_si128(TEMP, RES[0]);
	RES[1] = _mm_insert_epi32(RES[1],_mm_extract_epi32(TEMP, 1) , 1);
	
	TEMP = _mm_slli_si128(RES[1], 4);
	TEMP = _mm_xor_si128(TEMP, RES[0]);
	RES[1] = _mm_insert_epi32(RES[1],_mm_extract_epi32(TEMP, 2) , 2);
	
	TEMP = _mm_slli_si128(RES[1], 4);
	TEMP = _mm_xor_si128(TEMP, RES[0]);
	RES[1] = _mm_insert_epi32(RES[1],_mm_extract_epi32(TEMP, 3) , 3);
	IMC_RES[1] = _mm_aesimc_si128(RES[1]);
	
	
	
	
	TEMP = _mm_aeskeygenassist_si128 (RES[1], 0x02);	
	TEMP = _mm_srli_si128(TEMP, 12);
	TEMP = _mm_xor_si128(RES[1], TEMP);
	RES[2] = _mm_set_epi32(0, 0, 0, _mm_extract_epi32(TEMP, 0));
	
	TEMP = _mm_slli_si128(RES[2], 4);
	TEMP = _mm_xor_si128(TEMP, RES[1]);
	RES[2] = _mm_insert_epi32(RES[2],_mm_extract_epi32(TEMP, 1) , 1);
	
	TEMP = _mm_slli_si128(RES[2], 4);
	TEMP = _mm_xor_si128(TEMP, RES[1]);
	RES[2] = _mm_insert_epi32(RES[2],_mm_extract_epi32(TEMP, 2) , 2);
	
	TEMP = _mm_slli_si128(RES[2], 4);
	TEMP = _mm_xor_si128(TEMP, RES[1]);
	RES[2] = _mm_insert_epi32(RES[2],_mm_extract_epi32(TEMP, 3) , 3);
	IMC_RES[2] = _mm_aesimc_si128(RES[2]);
	
	
	
	
	TEMP = _mm_aeskeygenassist_si128 (RES[2], 0x04);	
	TEMP = _mm_srli_si128(TEMP, 12);
	TEMP = _mm_xor_si128(RES[2], TEMP);
	RES[3] = _mm_set_epi32(0, 0, 0, _mm_extract_epi32(TEMP, 0));
	
	TEMP = _mm_slli_si128(RES[3], 4);
	TEMP = _mm_xor_si128(TEMP, RES[2]);
	RES[3] = _mm_insert_epi32(RES[3],_mm_extract_epi32(TEMP, 1) , 1);
	
	TEMP = _mm_slli_si128(RES[3], 4);
	TEMP = _mm_xor_si128(TEMP, RES[2]);
	RES[3] = _mm_insert_epi32(RES[3],_mm_extract_epi32(TEMP, 2) , 2);
	
	TEMP = _mm_slli_si128(RES[3], 4);
	TEMP = _mm_xor_si128(TEMP, RES[2]);
	RES[3] = _mm_insert_epi32(RES[3],_mm_extract_epi32(TEMP, 3) , 3);
	IMC_RES[3] = _mm_aesimc_si128(RES[3]);
	
	
	
	
	TEMP = _mm_aeskeygenassist_si128 (RES[3], 0x08);	
	TEMP = _mm_srli_si128(TEMP, 12);
	TEMP = _mm_xor_si128(RES[3], TEMP);
	RES[4] = _mm_set_epi32(0, 0, 0, _mm_extract_epi32(TEMP, 0));
	
	TEMP = _mm_slli_si128(RES[4], 4);
	TEMP = _mm_xor_si128(TEMP, RES[3]);
	RES[4] = _mm_insert_epi32(RES[4],_mm_extract_epi32(TEMP, 1) , 1);
	
	TEMP = _mm_slli_si128(RES[4], 4);
	TEMP = _mm_xor_si128(TEMP, RES[3]);
	RES[4] = _mm_insert_epi32(RES[4],_mm_extract_epi32(TEMP, 2) , 2);
	
	TEMP = _mm_slli_si128(RES[4], 4);
	TEMP = _mm_xor_si128(TEMP, RES[3]);
	RES[4] = _mm_insert_epi32(RES[4],_mm_extract_epi32(TEMP, 3) , 3);
	IMC_RES[4] = _mm_aesimc_si128(RES[4]);
	
	
	
	
	TEMP = _mm_aeskeygenassist_si128 (RES[4], 0x10);	
	TEMP = _mm_srli_si128(TEMP, 12);
	TEMP = _mm_xor_si128(RES[4], TEMP);
	RES[5] = _mm_set_epi32(0, 0, 0, _mm_extract_epi32(TEMP, 0));
	
	TEMP = _mm_slli_si128(RES[5], 4);
	TEMP = _mm_xor_si128(TEMP, RES[4]);
	RES[5] = _mm_insert_epi32(RES[5],_mm_extract_epi32(TEMP, 1) , 1);
	
	TEMP = _mm_slli_si128(RES[5], 4);
	TEMP = _mm_xor_si128(TEMP, RES[4]);
	RES[5] = _mm_insert_epi32(RES[5],_mm_extract_epi32(TEMP, 2) , 2);
	
	TEMP = _mm_slli_si128(RES[5], 4);
	TEMP = _mm_xor_si128(TEMP, RES[4]);
	RES[5] = _mm_insert_epi32(RES[5],_mm_extract_epi32(TEMP, 3) , 3);
	IMC_RES[5] = _mm_aesimc_si128(RES[5]);
	
	
	
	TEMP = _mm_aeskeygenassist_si128 (RES[5], 0x20);	
	TEMP = _mm_srli_si128(TEMP, 12);
	TEMP = _mm_xor_si128(RES[5], TEMP);
	RES[6] = _mm_set_epi32(0, 0, 0, _mm_extract_epi32(TEMP, 0));
	
	TEMP = _mm_slli_si128(RES[6], 4);
	TEMP = _mm_xor_si128(TEMP, RES[5]);
	RES[6] = _mm_insert_epi32(RES[6],_mm_extract_epi32(TEMP, 1) , 1);
	
	TEMP = _mm_slli_si128(RES[6], 4);
	TEMP = _mm_xor_si128(TEMP, RES[5]);
	RES[6] = _mm_insert_epi32(RES[6],_mm_extract_epi32(TEMP, 2) , 2);
	
	TEMP = _mm_slli_si128(RES[6], 4);
	TEMP = _mm_xor_si128(TEMP, RES[5]);
	RES[6] = _mm_insert_epi32(RES[6],_mm_extract_epi32(TEMP, 3) , 3);
	IMC_RES[6] = _mm_aesimc_si128(RES[6]);
	
	
	
	
	TEMP = _mm_aeskeygenassist_si128 (RES[6], 0x40);	
	TEMP = _mm_srli_si128(TEMP, 12);
	TEMP = _mm_xor_si128(RES[6], TEMP);
	RES[7] = _mm_set_epi32(0, 0, 0, _mm_extract_epi32(TEMP, 0));
	
	TEMP = _mm_slli_si128(RES[7], 4);
	TEMP = _mm_xor_si128(TEMP, RES[6]);
	RES[7] = _mm_insert_epi32(RES[7],_mm_extract_epi32(TEMP, 1) , 1);
	
	TEMP = _mm_slli_si128(RES[7], 4);
	TEMP = _mm_xor_si128(TEMP, RES[6]);
	RES[7] = _mm_insert_epi32(RES[7],_mm_extract_epi32(TEMP, 2) , 2);
	
	TEMP = _mm_slli_si128(RES[7], 4);
	TEMP = _mm_xor_si128(TEMP, RES[6]);
	RES[7] = _mm_insert_epi32(RES[7],_mm_extract_epi32(TEMP, 3) , 3);
	IMC_RES[7] = _mm_aesimc_si128(RES[7]);
	
	
	
	
	TEMP = _mm_aeskeygenassist_si128 (RES[7], 0x80);	
	TEMP = _mm_srli_si128(TEMP, 12);
	TEMP = _mm_xor_si128(RES[7], TEMP);
	RES[8] = _mm_set_epi32(0, 0, 0, _mm_extract_epi32(TEMP, 0));
	
	TEMP = _mm_slli_si128(RES[8], 4);
	TEMP = _mm_xor_si128(TEMP, RES[7]);
	RES[8] = _mm_insert_epi32(RES[8],_mm_extract_epi32(TEMP, 1) , 1);
	
	TEMP = _mm_slli_si128(RES[8], 4);
	TEMP = _mm_xor_si128(TEMP, RES[7]);
	RES[8] = _mm_insert_epi32(RES[8],_mm_extract_epi32(TEMP, 2) , 2);
	
	TEMP = _mm_slli_si128(RES[8], 4);
	TEMP = _mm_xor_si128(TEMP, RES[7]);
	RES[8] = _mm_insert_epi32(RES[8],_mm_extract_epi32(TEMP, 3) , 3);
	IMC_RES[8] = _mm_aesimc_si128(RES[8]);
	
	
	
	
	TEMP = _mm_aeskeygenassist_si128 (RES[8], 0x1b);	
	TEMP = _mm_srli_si128(TEMP, 12);
	TEMP = _mm_xor_si128(RES[8], TEMP);
	RES[9] = _mm_set_epi32(0, 0, 0, _mm_extract_epi32(TEMP, 0));
	
	TEMP = _mm_slli_si128(RES[9], 4);
	TEMP = _mm_xor_si128(TEMP, RES[8]);
	RES[9] = _mm_insert_epi32(RES[9],_mm_extract_epi32(TEMP, 1) , 1);
	
	TEMP = _mm_slli_si128(RES[9], 4);
	TEMP = _mm_xor_si128(TEMP, RES[8]);
	RES[9] = _mm_insert_epi32(RES[9],_mm_extract_epi32(TEMP, 2) , 2);
	
	TEMP = _mm_slli_si128(RES[9], 4);
	TEMP = _mm_xor_si128(TEMP, RES[8]);
	RES[9] = _mm_insert_epi32(RES[9],_mm_extract_epi32(TEMP, 3) , 3);
	IMC_RES[9] = _mm_aesimc_si128(RES[9]);
	
	
	
	
	TEMP = _mm_aeskeygenassist_si128 (RES[9], 0x36);	
	TEMP = _mm_srli_si128(TEMP, 12);
	TEMP = _mm_xor_si128(RES[9], TEMP);
	RES[10] = _mm_set_epi32(0, 0, 0, _mm_extract_epi32(TEMP, 0));
	
	TEMP = _mm_slli_si128(RES[10], 4);
	TEMP = _mm_xor_si128(TEMP, RES[9]);
	RES[10] = _mm_insert_epi32(RES[10],_mm_extract_epi32(TEMP, 1) , 1);
	
	TEMP = _mm_slli_si128(RES[10], 4);
	TEMP = _mm_xor_si128(TEMP, RES[9]);
	RES[10] = _mm_insert_epi32(RES[10],_mm_extract_epi32(TEMP, 2) , 2);
	
	TEMP = _mm_slli_si128(RES[10], 4);
	TEMP = _mm_xor_si128(TEMP, RES[9]);
	RES[10] = _mm_insert_epi32(RES[10],_mm_extract_epi32(TEMP, 3) , 3);
	IMC_RES[10] = RES[10];
	
	
	} // The 2nd argument of "_mm_aeskeygenassist_si128" needs to be a immediate 8-bit value, i.e. a constant value of 8-bit that is different for each round. So, we can't use any loop for this key expansion, instead, we have to do this 11 times and store it in the __m128i type array RES.
	  // Also,  IMC_RES is the "InverseMixColumn" operation applied on a __m128i type register (considering it as a "State"). It is necessary to generate the IMC_RES[i] for RES[i] for each 1<=i<=9 for the decryption process. 
	

void Cipher (unsigned char *m, __m128i *RES, unsigned char *c) { // The Encryption Function.
	
	__m128i C;
	
	C = _mm_loadu_si128((__m128i*)m);
	
	C = _mm_xor_si128(C, RES[0]);
	
	for (int r=1; r<10; r++) C = _mm_aesenc_si128 (C, RES[r]);
	
	C = _mm_aesenclast_si128(C, RES[10]); // The last round (the half round).
	
	_mm_storeu_si128(((__m128i*)c), C); 
	
	} 	
	
	
void InvCipher (unsigned char *c, __m128i *IMC_RES, unsigned char *m1) { // The Decryption Function.
	
	__m128i M;
	
	M = _mm_loadu_si128((__m128i*)c);
	
	M = _mm_xor_si128(M, IMC_RES[10]);
	
	for (int r=9; r>0; r--) M = _mm_aesdec_si128 (M, IMC_RES[r]);
	
	M = _mm_aesdeclast_si128(M, IMC_RES[0]); // For the last round (half round).
	
	_mm_storeu_si128(((__m128i*)m1), M);
	
	}	
	
	
	
void main () {

	unsigned char k[16] = {43,126,21,22,40,174,210,166,171,247,21,136,9,207,79,60};

	__m128i RES[11], IMC_RES[11];
	
	KeyExpansion(k, RES, IMC_RES);
	
	unsigned char m[16] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
	
	unsigned char c[16], m1[16];
	
	Cipher(m, RES, c);
	
	printf("\n\nThe ciphertext is : ");
	printBytesRev(c, 16);
	
	InvCipher(c, IMC_RES, m1);
	
	printf("\n\nThe plaintext is : ");
	printBytesRev(m1, 16);
}
	
	
	
	
	
	
	
	
