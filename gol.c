#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define REGSIZE 16
#define WORDSIZE (8*sizeof(unsigned int))
#define MAXFRAMES 64

static inline void setIndexOn(unsigned int *reg, size_t idx); //sets the bit on the index idx to 1

static inline void setIndexOff(unsigned int *reg, size_t idx); //sets the bit on the index idx to 0

static void getFrame(unsigned int *reg, unsigned int *breg); //calculates the permutations of one frame of the game

static int getBit(unsigned int *reg, size_t idx); //returns the bit value in the index position idx

static void printBits(unsigned int *reg); //prints the binary value of the variable introduced

void main(){

	//definition of the two 64b registers

	unsigned int *reg1 = (int *) calloc (REGSIZE/8 + 1, sizeof(unsigned int));
	unsigned int *reg2 = (int *) calloc (REGSIZE/8 + 1, sizeof(unsigned int));

	//initialization of the world

	for(int j = 1; j<33; j++){

		int uneven = j*2-1;
		setIndexOn(reg1, uneven);
	
	}
	/*
	setIndexOn(reg1, 23);
	setIndexOn(reg1, 37);
*/
	printBits(reg1);

	for(int i = 0; i<MAXFRAMES; i++){

		getFrame(reg1, reg2);

	}
}

static inline void setIndexOn (unsigned int *reg, size_t idx){

	reg[idx/WORDSIZE] |= (1 << (idx % WORDSIZE));

}


static inline void setIndexOff (unsigned int *reg, size_t idx){

	reg[idx/WORDSIZE] ^= (1 << (idx % WORDSIZE));

}

static int getBit (unsigned int *reg, size_t idx){
	
	int a = reg[idx/WORDSIZE] & (1 << (idx % WORDSIZE));

	if(a == 0){

		return 0;
	
	}else{

		return 1;

	}
}

static void printBits (unsigned int *reg){

	for(int i = 2*WORDSIZE-1; i>-1; i--){
	
		int n = getBit(reg, (size_t)i);

		printf("%d", n);
	}

	printf("\n");
	
}

static void getFrame (unsigned int *reg, unsigned int *breg){
	
	int counter;
	int regSize = 2*WORDSIZE-1;

	for(int i = regSize; i>-1; i--){
		
		counter = 0;

		//gathers the bit information for the relevant cells in this cycle

		if(i != 0){

			int c1 = getBit(reg, (size_t)(i-1));
			counter += c1;

		}

		int c2 = getBit(reg, (size_t)i);
		counter += c2;

		if(i != regSize){

			int c3 = getBit(reg, (size_t)(i+1));
			counter += c3;

		}

		//implementation of the rules of the game
		
		if (counter == 3){

			setIndexOff(breg, i);

		}
		else if (counter == 1){

			if(c2 == 0){

				setIndexOn(breg, i);

			}else{

				setIndexOff(breg, i);

			}
		}
		
		else if (counter == 2){

			if(c2 == 0){

				setIndexOn(breg, i);

			}
		}
	}

	//update of the state of the world

	reg[0] = breg[0];
	reg[1] = breg[1];
	
	printBits(reg);

}
