// The following Code includes the KeyExpansion, Cipher and InvCipher operations of an AES-128 Encryption System.
// Compilation Instruction : gcc -o aes final_dec.c -lm

#include <stdio.h>
#include <math.h>
#include<stdint.h>



typedef struct {
	unsigned char let[4];
	} Word; // Creating a structure "Word" with 4 unsigned char elements.

typedef struct {
	Word col[4];
	} State; // Essentially a "State" datatype is a 4x4 matrix, with each element being an unsigned char. The (i,j)-th entry of a state S = S.col[j].let[i]

void PrintWord (Word w) {
	printf("\n");
	for (int i=0;i<4;i++) printf("%02x ",w.let[i]);
	printf("\n");
	}	
	
Word XorWords (Word x, Word y) {
	
	Word z;
	for (int i=0; i<4; i++) z.let[i] = x.let[i] ^ y.let[i]; 
	return z;
	} 

void PrintState(State S, int Nb) {
	printf("\n");
	for (int i=0;i<Nb;i++) {
		for (int j=0; j<4; j++) printf("%02x ",S.col[i].let[j]);
		}
	printf("\n");
	} // "Nb" is the number of blocks that a State contains (i.e. the number of Columns the matrix has). Typically, for AES-128, we'll always have Nb = 4.

void PrintData(unsigned char *a, int n) {
	printf("\n");
	for (int i=0; i<n; i++) printf("%02x ", a[i]);
	printf("\n");	
	} // To print the first "n" elements of an unsigned char pointer type variable "a".


uint16_t f_mult(uint8_t a, uint8_t b) {
	
	uint8_t temp, and=0b00000001; // "and" variable acts as the mask here.
	uint16_t prod, c=0; 
	for (int i=0; i<8; i++) {
		
		temp = (b>>i) & and; // Putting the LSB (i+1)-th bit of "b" in "temp".
		
		prod = a * temp;
		
		c = c ^ (prod << i); // Shifting and XORing the product we got as "prod".
		}
	return c;
	} // Multiplying two 8-bit integers over the field F_(2^8). 
	
uint8_t Reduction(uint16_t c) {
	uint16_t temp, temp2=c, m, n, o, p;
	int k;
	uint8_t z;

	while ((temp2 >> 8) != 0) { // Running this process till the MSB 8 bits of "temp2" becomes 0.
		
		temp = temp2 >> 8;
		k=0;
	
		while (temp != 1) {
			temp = temp >> 1;
			k += 1;
			}
		temp = temp << k; // Now, "temp" has 1 in the (max_deg(temp2) - 8 + 1)-th bit and 0 in all the other bits, where max_deg(temp2) = (The position of the first MSB non-zero bit of temp2) - 1.
		
		m = temp << 8; 
		n = temp << 4; 
		o = temp << 3; 
		p = temp << 1; 
		
		temp2 = temp2 ^ m;    // for the component x^8 of m(x).
		temp2 = temp2 ^ n;    // for the component x^4 of m(x).
		temp2 = temp2 ^ o;    // for the component x^3 of m(x).
		temp2 = temp2 ^ p;    // for the component x   of m(x).
		temp2 = temp2 ^ temp; // for the component 1=x^0 of m(x).
		}
	
	z = (uint8_t)(temp2 & 0xff); // Extracting the LSB 8 bits of "temp2" and putting it in "z".
	return z;
	} // Reducing a 16-bit integer (a polynomial of degree at most 15) over F_(2^8) w.r.t the polynomial m(x) = x^8 + x^4 + x^3 + x + 1


static const unsigned char Sbox[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5,
    0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
    0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc,
    0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a,
    0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
    0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b,
    0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85,
    0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
    0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17,
    0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88,
    0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
    0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9,
    0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6,
    0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
    0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94,
    0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68,
    0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
}; // The AES S-Box in 1-dimensional manner.

static const unsigned char InvSbox[256] = {
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38,
    0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
    0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87,
    0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
    0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D,
    0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
    0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2,
    0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
    0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16,
    0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
    0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA,
    0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
    0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A,
    0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
    0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02,
    0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
    0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA,
    0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
    0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85,
    0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
    0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89,
    0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
    0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20,
    0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
    0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31,
    0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
    0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D,
    0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
    0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0,
    0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26,
    0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
}; // The Inverse of AES S-Box in 1-dimensional way.


Word RotWord (Word w) {

	unsigned char temp;
	temp = w.let[0];
	
	for (int i = 0; i < 4; i++) w.let[i] = w.let[i+1]; 
	w.let[3] = temp;
	
	return w;
	} // The Rotate Word operation.
	
Word SubWord (Word w) {
	for (int i = 0; i<4; i++) w.let[i] = Sbox[w.let[i]];
	return w;
	} // The S-Box operation on an 8-bit value (on an unsigned char).	

Word InvSubWord(Word w) {
	for (int i=0; i<4; i++) w.let[i] = InvSbox[w.let[i]];
	return w;
	} // Inverse of the S-Box operation on an 8-bit value (on an unsigned char).

Word Rcon (int j) {

	Word x;

	for (int i=1; i<4; i++) x.let[i] = 0x00;
	
	x.let[0] = Reduction(pow(0x02, (j-1))); // Taking the (j-1)-th power of 2 and Reducing it if necessary. 
	
	return x;
	} // A function required for the KeyExpansion operation.


void KeyExpansion(unsigned char *k, int rounds, Word result[] ) {

	int key_size_bytes = 16; // In AES-128, the Initial Key is of 16 bytes (an array of 16 unsigned char variables).
	int bl = key_size_bytes/4; // Number of blocks. Quite eventually, this is equal to 4 for AES-128.
	Word temp, rcon;
	
	for (int i = 0; i < bl; i++) {
		for (int j=0; j<4; j++) result[i].let[j] = k[(4*i)+j];
		} // Initialising the key values as the entries of the first 4 Words of the "result" array.
	
	for (int i = bl; i <  bl*(rounds +1); i++) {
	
		temp = result[i-1];
		
		while (i % bl == 0) {  // Runs only if "i" is a multiple of 4.
			temp = RotWord(temp);
			temp = SubWord(temp);
			rcon = Rcon(i/bl); // "Rcon" is applied on the value of the Round of Key Expansion we are in.
			temp = XorWords(temp, rcon);
			
			break; // So that for each value of "i", this while loop runs at most once.
			}
		
		result[i] = XorWords(result[i-bl], temp);
		
		}	
	
}

State SubBytes(State S) {
	State S1;
	for (int i=0; i<4; i++) S1.col[i] = SubWord(S.col[i]);
	return S1;
	} // Same as "SubWord" operation, but on a State.

State InvSubBytes(State S) {
	State S1;
	for (int i=0; i<4; i++) S1.col[i] = InvSubWord(S.col[i]);
	return S1;
	} // Inverse of the "SubBytes" operation.

State ShiftRows(State S) {

	State S1;
	for (int i=0; i<4; i++) {
		for (int j=0; j<4; j++) S1.col[j].let[i] = S.col[(j+i)%4].let[i];
		}
	return S1;
	} // Left shifting the i-th row of "S" by (i-1) elements.

State InvShiftRows(State S) {
	
	State S1;
	for (int i=0; i<4; i++) {
		for (int j=3; j>=0; j--) S1.col[j].let[i] = S.col[(j-i+4)%4].let[i];
		}
	return S1;
	} // Right shifting the i-th row of "S" by (i-1) elements.

State MixCol(State S) {
	
	State S1;
	
	for (int i=0; i<4; i++) {
		
S1.col[i].let[0] = Reduction(f_mult(0x02, S.col[i].let[0])) ^ Reduction(f_mult(0x03, S.col[i].let[1])) ^ S.col[i].let[2] ^ S.col[i].let[3];
		
		
S1.col[i].let[1] = Reduction(f_mult(0x02, S.col[i].let[1])) ^ Reduction(f_mult(0x03, S.col[i].let[2])) ^ S.col[i].let[0] ^ S.col[i].let[3];
		
		
S1.col[i].let[2] = Reduction(f_mult(0x02, S.col[i].let[2])) ^ Reduction(f_mult(0x03, S.col[i].let[3])) ^ S.col[i].let[0] ^ S.col[i].let[1];
		
		
S1.col[i].let[3] = Reduction(f_mult(0x02, S.col[i].let[3])) ^ Reduction(f_mult(0x03, S.col[i].let[0])) ^ S.col[i].let[1] ^ S.col[i].let[2];
		
		}
	return S1;
	} // This opeartion only takes (2*4*4=) 32 calls of the functions "f_mult" and "Reduction".

State MixColumn (State S) {
	
	State S1;
	for (int i=0; i<4; i++) {
		for (int j=0;j<4;j++) S1.col[i].let[j] = 0;
		} // Initialising "S1" to be a null matrix.
	
	Word w;
	w.let[0] = 0x02;
	w.let[1] = 0x01;
	w.let[2] = 0x01;
	w.let[3] = 0x03; // Initialising a Word "w" with the first column's values of the required Multiplication matrix.
	
	State a;
	for (int i=0; i<4; i++) {
		for (int j=0;j<4;j++) a.col[i].let[j] = w.let[(j-i+4)%4];
		} // Initialising the Multiplication matrix "a" in the required way using the Word "w".		
	
	for (int i=0;i<4;i++) {
		
		for (int j=0;j<4;j++) {
			
			for (int k=0; k<4; k++) {
				
				
				S1.col[i].let[j] ^= Reduction(f_mult(a.col[k].let[j], S.col[i].let[k])); // The (j,i)-th entry of the resultant matrix "S1" is the recurrent XOR of itself and the Reduced product of "a_(j,k)" and "S_(k,i)". 
				
				
				}
			}
		
		} // The Matrix Multiplication operation. [S1 = a x S].

return S1;
} // This function takes as many as (4*4*4=) 64 calls of the functions "f_mult" and "Reduction".


// Essentially, both "MixCol()" and "MixColumn()" perform the same task. But, "MixCol()" causes way less operational overhead than "MixColumn()".

State InvMixColumn(State S) {

	State S1;
	for (int i=0; i<4; i++) {
		for (int j=0;j<4;j++) S1.col[i].let[j] = 0;
		} // Initialising "S1" to be a null matrix.
	
	Word wInv;
	wInv.let[0] = 0x0e;
	wInv.let[1] = 0x09;
	wInv.let[2] = 0x0d;
	wInv.let[3] = 0x0b; // Initialising the Word "wInv" with the first column's values of the required Multiplication matrix for the Inverse operation.
	
	State aInv;
	for (int i=0; i<4; i++) {
		for (int j=0;j<4;j++) aInv.col[i].let[j] = wInv.let[(j-i+4)%4];
		} // Initialising the Multiplication matrix "a" for the Inverse operation in the required way using the Word "w".	
	
	for (int i=0;i<4;i++) {
		
		for (int j=0;j<4;j++) {
			
			for (int k=0; k<4; k++) {
				
			
				S1.col[i].let[j] ^= Reduction(f_mult(aInv.col[k].let[j], S.col[i].let[k])); //The (j,i)-th entry of the resultant matrix "S1" is the recurrent XOR of itself and the Reduced product of "aInv_(j,k)" and "S_(k,i)". 
				
				
				}
			}
		
		} // The Matrix Multiplication operation. [S1 = aInv x S].

return S1;

	} // This function too takes as many as (4*4*4=) 64 calls of the function "f_mult" and "Reduction".

// We can't form an Inverse version of the function "MixCol()" [with less operational overhead] as we anyway have to do 64 many multiplications for the Inverse operation.


void Cipher(unsigned char *m, int rounds, Word key[], unsigned char *c1) {
	
	State c;
	int mes_size_bytes = 16;
	int bl = mes_size_bytes/4;
	
	for (int i = 0; i < bl; i++) {
		for (int j=0; j<4; j++) c.col[i].let[j] = m[(4*i)+j];
		} // Initialisation of the cipher "c" with the message "m".
	
	for (int i=0; i<bl; i++) c.col[i] = XorWords(c.col[i], key[i]); // The AddRoundKey opeartion.
	
	for (int r=1; r<rounds; r++) {
		c = SubBytes(c);
		c = ShiftRows(c);
		c = MixCol(c); // Using MixCol() here because of the fact that it takes only half as many calls to "f_mult" and "Reduction" as compared to MixColumn().  
		for (int i=0; i<bl; i++) c.col[i] = XorWords(c.col[i], key[(r*bl)+i]);  // Again the AddRoundKey operation.
		}
	
	c = SubBytes(c);
	c = ShiftRows(c);
	for (int i=0; i<bl; i++) c.col[i] = XorWords(c.col[i], key[(rounds*bl)+i]); // The last round of operation without the Mix Column operation [The Half-Round].
	
	
	for (int i=0; i<bl; i++) {
		for (int j=0; j<4; j++) c1[(4*i)+j] = c.col[i].let[j];
		} // Transferring the Output State values of the cipher "c" into an unsigned char pointer type variable "c1".
	
	}

void InvCipher (unsigned char *c, int rounds, Word key[], unsigned char *m1) {

	State m;
	int cip_size_bytes = 16;
	int bl = cip_size_bytes/4;
	
	for (int i = 0; i < bl; i++) {
		for (int j=0; j<4; j++) m.col[i].let[j] = c[(4*i)+j];
		} // Initialisation of the message State "m" with the cipher "c".

	for (int i=0; i<bl; i++) m.col[i] = XorWords(m.col[i], key[(rounds*bl)+i]); // The AddRoundKey operation. Note that AddRoundKey is its own Inverse as it's just performing XOR of 2 values.
	
	// Doing the exact operations performed in the "Cipher" function, in Reverse order.
	
	for (int r=(rounds-1); r>0; r--) {
		m = InvShiftRows(m);
		m = InvSubBytes(m); // At this very point, we complete the reverse work for the Half-Round, when running this loop for the first time.
		for (int i=0; i<bl; i++) m.col[i] = XorWords(m.col[i], key[(r*bl)+i]); // From here, when running for the first, we start the reverse work for the rest of the rounds.
		m = InvMixColumn(m);
		}
	
	m = InvShiftRows(m);
	m = InvSubBytes(m); // Continuing from the last "InvMixColumn()" operation, we now finish the reverse of the first full round done in the "Cipher" function.
	
	for (int i=0; i<bl; i++) m.col[i] = XorWords(m.col[i], key[i]); // Now we perform the final AddRoundKey to get back the message "m".
	

	for (int i=0; i<bl; i++) {
		for (int j=0; j<4; j++) m1[(4*i)+j] = m.col[i].let[j];
		} // Again transferring the Output State values of the message "m" into an unsigned char variable "m1".
	
}



void main() {

	unsigned char k[16] = {43,126,21,22,40,174,210,166,171,247,21,136,9,207,79,60};
	// {2b,7e,15,16,28,ae,d2,a6,ab,f7,15,88,09,cf,4f,3c}
	int rounds;
	
	printf("\nHow many rounds do you want it to go? : ");
	scanf("%d", &rounds); // The user can determine how many rounds of KeyExpansion they want to do.
	Word result[4*(rounds+1)];
	
	/*
	printf("\nEnter the initial key :\n");
	for (int i=0;i<16;i++) {
		
		printf("k%d = ",i);
		scanf("%hhu",&k[i]);
		}
	
	*/
	
	KeyExpansion(k, rounds, result);
	
	
	unsigned char m[16] = {0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
	
	unsigned char c[16], m1[16];
	
	Cipher(m, rounds, result, c);
	
	printf("\n\nThe ciphertext is : ");
	PrintData(c, 16);
	
	InvCipher(c, rounds, result, m1);
	
	printf("\n\nThe plaintext is : ");
	PrintData(m1, 16);
	
}			
