#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WORLDHEIGHT 50
#define WORLDWIDTH 100
#define WORLDLENGTH 100000
#define CELL_STATE_DEAD 0  //normal dead state
#define CELL_STATE_LIVE 1  //normal live state
#define CELL_STATE_NEWB 2  //recently born intermediary state
#define CELL_STATE_RDED -1 //recently deceased intermediary state

//cell data structure, keeps information on its live state as well as coordinates

typedef struct _cell{

	int x;
	int y;
	int isAlive;

}Cell;

//world data structure, keeps information on it's size, and holds the matrix of cells that confrom the mortal plain

typedef struct _world{
	
	int width;
	int height;
	Cell *matrix;

}World;

World createNewWorld(); //defines a new world struct with the memory allocation necesary

static void initWorld(World world); //initializes the world with an empty dead plane

static void manifestWorld(World world); //shows the world through the terminal by printing characters that correspond to either living or dead cells

static World setSeeds(World world); //adds the living elements to the start of the world

static int countNeighbors(World world, Cell incel); //returns the number of living neighbors of any given cell

static int isAlive(Cell mycell); //returns a value depending of if the cell given is alive or not, accounting for intermediary states

static void moveForward(World *world); //executes the world and runs consecutive generations of it

static int lifeAndDeath(int neighbors, Cell incel); //returns the state of the cell being evaluated depending on the neighbor count

static void hammerOfTruth(World world); //determines unequivocally if a cell is alive or dead, smashes intermediary states into either alive or dead.


void main(){

	World world;

	world = createNewWorld();

	initWorld(world);

	world = setSeeds(world);

	manifestWorld(world);

	moveForward(&world);

	system("clear");

}


World createNewWorld(){
	
	World world;
	world.width = WORLDWIDTH;
	world.height = WORLDHEIGHT;
	world.matrix = (Cell *)malloc(sizeof(Cell)*(world.width*world.height));
	return world;

}

static void initWorld(World world){

	int worldSize = world.width*world.height;

	for(int i = 0 ; i < worldSize ; i++){
		
		world.matrix[i].x = i%world.width;
		world.matrix[i].y = i/world.width;
		world.matrix[i].isAlive = CELL_STATE_DEAD;
		
	}

}

static World setSeeds(World world){

	int worldSize = world.width*world.height;
	
	//definition of a simple glider

	/*
	world.matrix[570].isAlive = CELL_STATE_LIVE;
	world.matrix[571].isAlive = CELL_STATE_LIVE;
	world.matrix[572].isAlive = CELL_STATE_LIVE;
	world.matrix[472].isAlive = CELL_STATE_LIVE;
	world.matrix[371].isAlive = CELL_STATE_LIVE;
	*/

	//definition of glider generator
	

	world.matrix[720].isAlive = CELL_STATE_LIVE;
	world.matrix[719].isAlive = CELL_STATE_LIVE;
	world.matrix[820].isAlive = CELL_STATE_LIVE;
	world.matrix[819].isAlive = CELL_STATE_LIVE;
	world.matrix[653].isAlive = CELL_STATE_LIVE;
	world.matrix[654].isAlive = CELL_STATE_LIVE;
	world.matrix[553].isAlive = CELL_STATE_LIVE;
	world.matrix[554].isAlive = CELL_STATE_LIVE;
	world.matrix[829].isAlive = CELL_STATE_LIVE;
	world.matrix[729].isAlive = CELL_STATE_LIVE;
	world.matrix[929].isAlive = CELL_STATE_LIVE;
	world.matrix[630].isAlive = CELL_STATE_LIVE;
	world.matrix[531].isAlive = CELL_STATE_LIVE;
	world.matrix[532].isAlive = CELL_STATE_LIVE;
	world.matrix[1030].isAlive = CELL_STATE_LIVE;
	world.matrix[1131].isAlive = CELL_STATE_LIVE;
	world.matrix[1132].isAlive = CELL_STATE_LIVE;
	world.matrix[833].isAlive = CELL_STATE_LIVE;
	world.matrix[835].isAlive = CELL_STATE_LIVE;
	world.matrix[836].isAlive = CELL_STATE_LIVE;
	world.matrix[735].isAlive = CELL_STATE_LIVE;
	world.matrix[935].isAlive = CELL_STATE_LIVE;
	world.matrix[1034].isAlive = CELL_STATE_LIVE;
	world.matrix[634].isAlive = CELL_STATE_LIVE;
	world.matrix[739].isAlive = CELL_STATE_LIVE;
	world.matrix[740].isAlive = CELL_STATE_LIVE;
	world.matrix[841].isAlive = CELL_STATE_LIVE;
	world.matrix[640].isAlive = CELL_STATE_LIVE;
	world.matrix[639].isAlive = CELL_STATE_LIVE;
	world.matrix[540].isAlive = CELL_STATE_LIVE;
	world.matrix[539].isAlive = CELL_STATE_LIVE;
	world.matrix[441].isAlive = CELL_STATE_LIVE;
	world.matrix[443].isAlive = CELL_STATE_LIVE;
	world.matrix[343].isAlive = CELL_STATE_LIVE;
	world.matrix[843].isAlive = CELL_STATE_LIVE;
	world.matrix[943].isAlive = CELL_STATE_LIVE;


	//alternate live and dead cells throughout the entire plain
	
	
	/*
	for(int i = 0 ; i < worldSize ; i++){

		if( (i/WORLDWIDTH)%2 != 0 ){

			if( i%2 != 0){

				world.matrix[i].isAlive = CELL_STATE_LIVE;

			}

		}else{

			if( i%2 != 1){

				world.matrix[i].isAlive = CELL_STATE_LIVE;

			}

		}

	}*/

	return world;

}

static inline int isAlive(Cell mycell){

	if(mycell.isAlive == CELL_STATE_LIVE || mycell.isAlive == CELL_STATE_RDED){

		return CELL_STATE_LIVE;

	}else{

		return CELL_STATE_DEAD;

	}

}

static void moveForward(World *world){

	int neighbors = 0;

	for( int i = 0 ; i < WORLDLENGTH ; i++){

		for( int j = 0 ; j < (world->height)*(world->width) ; j++){

			neighbors = countNeighbors(*world, world->matrix[j]);

			world->matrix[j].isAlive = lifeAndDeath(neighbors, world->matrix[j]);

		}
			
			hammerOfTruth(*world);
			manifestWorld(*world);
			usleep(75000);
			
	}
	
}

static int lifeAndDeath(int neighbors, Cell incel){

	switch(neighbors){

		case 2:

			if(incel.isAlive == CELL_STATE_DEAD){

				return CELL_STATE_DEAD;

			}else{

				return CELL_STATE_LIVE;

			}

		case 3:

			if(incel.isAlive == CELL_STATE_DEAD){

				return CELL_STATE_NEWB;

			}else{

				return CELL_STATE_LIVE;

			}

		default:

			if(incel.isAlive == CELL_STATE_LIVE){
				
				return CELL_STATE_RDED;
 	  
			}else{

				return CELL_STATE_DEAD;

			}
		}
}

static int countNeighbors(World world, Cell incel){

	int x = incel.x;
	int y = incel.y;

	int mm = -1, mn = -1, mp = -1, nm = -1, np = -1, pm = -1, pn = -1, pp = -1;

	int counter = 0;

	if( x > 0 ){

		if( y > 0 ){

			mm = (x-1) + world.width*(y-1);

			counter += isAlive(world.matrix[mm]);

		}

		mn = (x-1) + world.width*(y);

		counter += isAlive(world.matrix[mn]);

		if ( y < world.height-1 ){

			mp = (x-1) + world.width*(y+1);

			counter += isAlive(world.matrix[mp]);
	
		}

	}

	if( y < world.height-1 ){

		np = x + world.width*(y+1);

		counter += isAlive(world.matrix[np]);

	}

	if( y > 0 ){

		nm = x + world.width*(y-1);

		counter += isAlive(world.matrix[nm]);

	}

	if( x < world.width-1 ){

		pn = (x+1) + world.width*(y);

		counter += isAlive(world.matrix[pn]);

		if( y < world.height-1 ){

			pp = (x+1) + world.width*(y+1);

			counter += isAlive(world.matrix[pp]);

		}

		if( y > 0 ){

			pm = (x+1) + world.width*(y-1);

			counter += isAlive(world.matrix[pm]);

		}

	}

	return counter;

}



static void manifestWorld(World world){

	system("clear");

	for(int a = 0; a < world.width+2; a++){
		printf("-");
	}
	printf("\n");

	for(int i = 0 ; i < world.height ; i++){

		printf("|");

		for(int j = 0 ; j < world.width ; j++){

			int index = i*world.width + j;

			if( world.matrix[index].isAlive == 1 ){

				printf("X");

			}else{

				printf(" ");

			}

		}

		printf("|\n");

	}

	for(int a = 0; a < world.width+2; a++){
		printf("-");
	}
	printf("\n");

}

static void hammerOfTruth(World world){

	for(int i = 0; i < world.height*world.width; i++){

		if(world.matrix[i].isAlive == CELL_STATE_NEWB){

			world.matrix[i].isAlive = CELL_STATE_LIVE;

		} else if(world.matrix[i].isAlive == CELL_STATE_RDED){

			world.matrix[i].isAlive = CELL_STATE_DEAD;

		}

	}

}