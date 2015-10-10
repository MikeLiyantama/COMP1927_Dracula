// dracula.c
// Implementation of your "Fury of Dracula" Dracula AI

#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#include "DracView.h"

char *idToAbbrev(LocationID p);
void LocationCopy (char *from, char *to);

void decideDraculaMove(DracView gameState)
{
	if(giveMeTheRound(gameState) == 1){
		//Initial Round
		registerBestPlay("GE","Greetings");
	}
	else{
		//Subsequent Rounds
		char dest[3]; //Destination var
		 
		//Go to random places
        int size , *reachableLocation;
        int magicNum = giveMeTheRound(gameState);
        reachableLocation = whereCanIgo(gameState,&size,1,0,0);
        while(magicNum > size){
            magicNum = magicNum % size;
        }
        LocationCopy(edges[magicNum],dest);
        registerBestPlay(dest,"Nothing to find here");
		free(dest);
        return;
	}
}

void LocationCopy (char *from, char *to){
    int tempCounter = 0;
    to[0] = from[0];
    to[1] = from[1];
    to[2] = '\0';
    free(tempCounter);
}

char *idToAbbrev(LocationID p)
{
   assert(validPlace(p));
   return places[p].abbrev;
}