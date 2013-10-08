/* hamming.c - written by Bryan Ames, 2013
 *
 * the program takes a 16 bit hexadecimal integer at a prompt, and prints the
 * 21 bit hexadecimal representation of the hamming code that corresponds to
 * it. 
 *
 * compile with:
 * 	gcc -o hamming hamming.c
*/

#include <stdio.h>

int power(int base, int exponent);
int checkforparity(int ham[], int paritybit);
int hamming(int data);

#define GETBIT(num, bit) (((num) >> bit) & 1)
#define BITS 21

/* data_bits: holds the indices of the bits which are data bits in a 21 bit
 * hamming code. */
static int
data_bits[16] = {2, 4, 5, 6, 8, 9, 10, 11, 12, 13, 14, 16, 17, 18, 19, 20};

/* parity_bits: holds the indices of the bits which are parity bits in a 21 bit
 * hamming code. */
static int
parity_bits[5] = {0, 1, 3, 7, 15};

int power(int base, int exponent)
{
	int i;
	int ret = 1;

	/* ret is equal to base to the power of i */
	for(i = 0; i < exponent; i ++)
		ret *= base;

	return ret;
}

/* takes an integer array representing the bits of a hamming code, and finds the
 * parity bit that will be at index parity_bits[paritybit] in the hamming code */
int
checkforparity(int ham[], int paritybit)
{
	int i;
	/* count: the number of bits set bits that are checked by parity bit
	 * 'paritybit' */
	int count = 0;

	/* count is equal to the number of set bits before bit i that are 
	 * checked  by parity bit 'paritybit' */
	for (i = 1; i <= BITS; i++)
		if (GETBIT(i, paritybit) && (ham[i - 1]))
				count++;
	return (count % 2);
}


/* hamming: create a hamming code from a 16 bit integer value
 *
 * data: a 16 bit integer from which the hamming code will be generated
 *
 * returns: a 21 bit integer representing the hamming code.
*/
int
hamming(int data)
{
	/* ham: an integer array of the bits in the hamming code that
	 * corresponds to the integer 'data' */
	int ham[BITS];
	int i, dsize, psize;
	/* ret: the integer representation of the hamming code that corresponds
	 * the the integer 'data' */
	int ret = 0;

	/* index i of ham equals 0 */
	for (i = 0; i < BITS; i++)
		ham[i] = 0;

	dsize = sizeof(data_bits)/sizeof(int);
	psize = sizeof(parity_bits)/sizeof(int);

	/* the bit at index data_bit[i] in ham is equal to the i'th bit in 
	 * the integer data */
	for (i = 0; i < dsize; i++) {
		ham[data_bits[i]] = GETBIT(data, dsize - (i + 1));
	}

	/* the bit at index paritybit[i] in ham is the i'th parity bit of the
	 * ham */
	for (i = 0; i < psize; i++) {
		ham[parity_bits[i]] = checkforparity(ham, i);
	}

	/* the i'th bit of the integer ret is the bit at index i of ham */
	for (i = 0; i < BITS; i++)
		ret += ham[BITS - (i + 1)] * power(2, i); // should have used bitwise operators, I know...


	return ret;
}

int
main()
{
	/* data: a 16 bit integer that contains the data bits of the hamming
	 * code */
	int data;
	/* ham: a 21 bit integer that contains the hamming code of 'data' */
	int ham;

	printf("Enter a four-digit hexadecimal value: ");
	scanf("%x", &data);

	ham = hamming(data);

	printf("The hamming code is %x\n", ham);

	return 0;
}
