// dracula.c
// Implementation of your "Fury of Dracula" Dracula AI

#include <stdlib.h>
#include <stdio.h>
#include "Game.h"
#include "DracView.h"

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
